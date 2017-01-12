
#include "OpenGLComposite.h"
#include "GLExtensions.h"
#include <iostream>
#include <fstream>
#include "OpenGLDessin.cpp"
#include "carte_bmd.cpp"
#include <string>
#include "loader.cpp"
#include "gui_glwindows.h"
#include <color_data.h>

OpenGLComposite::OpenGLComposite(QWidget *parent, int a, int b) :
        QGLWidget(parent), mParent(parent),
        mGLoutFrame(0),
        mFrameHeight(a),mFrameWidth(b),
        mNb_input(4),
        mMode(1),
        mPgm_value(99),
        mPvw_value(99),
        GLOBAL_HEIGHT(1080),
        GLOBAL_WIDTH(1920),
        mSeuil(0),
        mTolerance(0),
        mCurrent_wipe(0),
        mIris_value(62),
        mTaille_pip(0),
        mPos_x(0),
        mPos_y(0),
        mModepip(0)

{
    for(int i = 0; i<10; i++)
        m_color_data[i] = new COLOR_DATA();
    ResolveGLExtensions(context());
    mTextureTab.resize(10);
    mAlpha=0.0;
    mGLoutFrame = malloc(((mFrameWidth * 16 / 8) * mFrameHeight)*2); // On alloue la taille nécessaire. Un pixel pèse 16 bits donc 2 bytes.


}

void** OpenGLComposite::link_outFrame()
{
    return &mGLoutFrame;
}

void OpenGLComposite::GLC_bindto(void** data, int _identifiant_sender)
{
    makeCurrent();
    glEnable(GL_TEXTURE_2D);
    long textureSize = mFrameWidth * 16 / 8 * mFrameHeight;
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mUnpinnedTextureBuffer);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, textureSize, *data, GL_DYNAMIC_DRAW);
    glBindTexture(GL_TEXTURE_2D,mTextureTab.at(_identifiant_sender));

    // NULL for last arg indicates use current GL_PIXEL_UNPACK_BUFFER target as texture data
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0 , mFrameWidth/2, mFrameHeight, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glDisable(GL_TEXTURE_2D);

}


//
// QGLWidget virtual methods
//
void OpenGLComposite::initializeGL ()
{

    // Initialization is deferred to InitOpenGLState() when the width and height of the DeckLink video frame are known
    if (! InitOpenGLState())
    {
        printf("Problème à l'initiation de l'environnement de travail OpenGL");
        exit(0);
    }
}

void OpenGLComposite::paintGL ()
{
    // The DeckLink API provides IDeckLinkGLScreenPreviewHelper as a convenient way to view the playout video frames
    // in a window.  However, it performs a copy from host memory to the GPU which is wasteful in this case since
    // we already have the rendered frame to be played out sitting in the GPU in the mIdFrameBuf frame buffer.
    // Simply copy the off-screen frame buffer to on-screen frame buffer, scaling to the viewing window size.
    glBindFramebufferEXT(GL_READ_FRAMEBUFFER, mIdFrameBuf);
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, mViewWidth*2, mViewHeight);
    glBlitFramebufferEXT(0, 0, mFrameWidth*2, mFrameHeight, 0, 0, mViewWidth, mViewHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

}

void OpenGLComposite::resizeGL (int _width, int _height)
{
    // We don't set the project or model matrices here since the window data is copied directly from
    // an off-screen FBO in paintGL().  Just save the width and height for use in paintGL().
    mViewWidth = _width;
    mViewHeight = _height;
}

bool OpenGLComposite::CheckOpenGLExtensions()
{
    const GLubyte* strExt;
    GLboolean hasFBO;
    if (! isValid())
    {
        QMessageBox::critical(NULL,"OpenGL initialization error.", "OpenGL context is not valid for specified QGLFormat.");
        return false;
    }

    makeCurrent();
    strExt = glGetString (GL_EXTENSIONS);
    hasFBO = gluCheckExtension ((const GLubyte*)"GL_EXT_framebuffer_object", strExt);


    if (!hasFBO)
    {
        QMessageBox::critical(NULL,"OpenGL initialization error.", "OpenGL extension \"GL_EXT_framebuffer_object\" is not supported.");
        return false;
    }

    return true;
}

bool OpenGLComposite::InitOpenGLState()
{
    makeCurrent();

    if (! CheckOpenGLExtensions())
        return false;

    // Prepare the shader used to perform colour space conversion on the video texture
    char compilerErrorMessage[1024];
    if (! compileFragmentShader(sizeof(compilerErrorMessage), compilerErrorMessage))
    {
        fprintf(stderr, compilerErrorMessage);
        QMessageBox::critical(NULL, compilerErrorMessage, "OpenGL Shader failed to compile");
        return false;
    }

    // Setup the scene
    glShadeModel( GL_SMOOTH );					// Enable smooth shading
    glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );                         // Black background
    glClearDepth( 1.0f );						// Depth buffer setup
    glEnable( GL_DEPTH_TEST );					// Enable depth testing
    glDepthFunc( GL_LEQUAL );					// Type of depth test to do
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


    glGenBuffers(1, &mUnpinnedTextureBuffer);

    for (int i=0;i<mNb_input;i++)
    {
    // Setup the texture which will hold the captured video frame pixels
    glEnable(GL_TEXTURE_2D);
    glGenTextures(mNb_input, (GLuint*)&mTextureTab.at(i));

    glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(i));

    // Parameters to control how texels are sampled from the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Create texture with empty data, we will update it using glTexSubImage2D each frame.
    // The captured video is YCbCr 4:2:2 packed into a UYVY macropixel.  OpenGL has no YCbCr format
    // so treat it as RGBA 4:4:4:4 by halving the width and using GL_RGBA internal format.

    //L'initialisation se fait avec des variables superglobales. C'est beau, c'est bon, c'est sale. mais ça permet d'intialiser quelle que soit la carte !
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GLOBAL_WIDTH/2, GLOBAL_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

    // Create Frame Buffer Object (FBO) to perform off-screen (rendering) of scene.
    // This allows the render to be done on a framebuffer with width and height exactly matching the video format.
    glGenFramebuffersEXT(1, &mIdFrameBuf);
    glGenRenderbuffersEXT(1, &mIdColorBuf);
    glGenRenderbuffersEXT(1, &mIdDepthBuf);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mIdFrameBuf);

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mIdColorBuf);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8,GLOBAL_WIDTH*2, GLOBAL_HEIGHT);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mIdDepthBuf);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, GLOBAL_WIDTH*2, GLOBAL_HEIGHT);

    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, mIdColorBuf);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mIdDepthBuf);


    // DRAW buffers

    // The texture we're going to render to
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, (GLuint*)&renderedTexture);

    glBindTexture(GL_TEXTURE_2D,  renderedTexture);

    // Parameters to control how texels are sampled from the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Create texture with empty data, we will update it using glTexSubImage2D each frame.
    // The captured video is YCbCr 4:2:2 packed into a UYVY macropixel.  OpenGL has no YCbCr format
    // so treat it as RGBA 4:4:4:4 by halving the width and using GL_RGBA internal format.

    //L'initialisation se fait avec des variables superglobales. C'est beau, c'est bon, c'est sale. mais ça permet d'intialiser quelle que soit la carte !
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, GLOBAL_WIDTH, GLOBAL_HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    m_openGL31Functions.initializeOpenGLFunctions();


    FramebufferName = 0;
    glGenFramebuffersEXT(1, &FramebufferName);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FramebufferName);

    // Set "renderedTexture" as our colour attachement #0
    m_openGL31Functions.glFramebufferTexture2D(GL_FRAMEBUFFER, 1 ,GL_TEXTURE_2D, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum buffers[1] = {1};
    m_openGL31Functions.glDrawBuffers(1, buffers);
    m_openGL31Functions.glBindFragDataLocation(mProgram_cg, 1, "out_c");

    GLenum glStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (glStatus != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
        QMessageBox::critical(NULL, "Cannot initialize framebuffer.", "OpenGL initialization error.");
        return false;
    }

    return true;
}

// Setup fragment shader to take YCbCr 4:2:2 video texture in UYVY macropixel format
// and perform colour space conversion to RGBA in the GPU.
bool OpenGLComposite::compileFragmentShader(int _errorMessageSize, char* _errorMessage)
{
    GLsizei		errorBufferSize;
    GLint		compileResult, linkResult;

    char* fragmentSource[50000];
    char* fragmentSource_2[50000];

    // 1er
     FILE * pFile;
     pFile = fopen ("/home/isis/Documents/DreamEverywhere-2017/frag.txt","r");
     float sizefile = getFileSize(pFile);
     fprintf(stderr, "size %f \n", sizefile);
     string str_prct="%";
     string str_c="c";
     string str_size = float_to_string(sizefile);
     string str_size_file;
     str_size_file = str_prct + str_size + str_c;
     fscanf (pFile, str_size_file.c_str(), &fragmentSource);

     fclose (pFile);

     // 2ème
     pFile = fopen ("/home/isis/Documents/DreamEverywhere-2017/frag_2.txt","r");
     sizefile = getFileSize(pFile);
     fprintf(stderr, "size %f \n", sizefile);
     str_prct="%";
     str_c="c";
     str_size = float_to_string(sizefile);
     str_size_file;
     str_size_file = str_prct + str_size + str_c;
     fscanf (pFile, str_size_file.c_str(), &fragmentSource_2);

     fclose (pFile);

const GLchar* shaderSource;
const GLchar* shaderSource_2;
shaderSource= (GLchar*)fragmentSource;
shaderSource_2= (GLchar*)fragmentSource_2;

   mFragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(mFragmentShader[0], 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(mFragmentShader[0]);

    glGetShaderiv(mFragmentShader[0], GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE)
    {
        glGetShaderInfoLog(mFragmentShader[0], _errorMessageSize, &errorBufferSize, _errorMessage);
        return false;
    }

    mProgram_e = glCreateProgram();

    glAttachShader( mProgram_e, mFragmentShader[0]);
    glLinkProgram( mProgram_e);

    glGetProgramiv( mProgram_e, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE)
    {
        glGetProgramInfoLog( mProgram_e, _errorMessageSize, &errorBufferSize, _errorMessage);
        return false;
    }

    mFragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);

     glShaderSource(mFragmentShader[1], 1, (const GLchar**)&shaderSource_2, NULL);
     glCompileShader(mFragmentShader[1]);

     glGetShaderiv(mFragmentShader[1], GL_COMPILE_STATUS, &compileResult);
     if (compileResult == GL_FALSE)
     {
         glGetShaderInfoLog(mFragmentShader[1], _errorMessageSize, &errorBufferSize, _errorMessage);
         return false;
     }

    mProgram_cg = glCreateProgram();

    glAttachShader( mProgram_cg, mFragmentShader[1]);
    glLinkProgram( mProgram_cg);

    glGetProgramiv( mProgram_cg, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE)
    {
        glGetProgramInfoLog( mProgram_cg, _errorMessageSize, &errorBufferSize, _errorMessage);
        return false;
    }

    return true;
}

void OpenGLComposite::slot_set_wipe(int _wipe)
{
    mCurrent_wipe = _wipe;
}

void OpenGLComposite::irisChanged(int _nv_iris)
{
    mIris_value = _nv_iris;

}

void OpenGLComposite::set_luma_param(int _nvid, bool _nvmode, int _nvseuil, int _nvtolerance, QColor _nvclr)
{

   mSeuil = _nvseuil;
   mTolerance = _nvtolerance;
   mKeyer_color = _nvclr;
   mKeyer_mode = _nvmode;

}

void OpenGLComposite::set_pip_param(int _taille, int _x, int _y, int _modeencour)
{
mTaille_pip = (float)_taille/100;
mPos_x= (float)_x/100;
mPos_y=(float)_y/100;
mModepip = _modeencour;

}

void OpenGLComposite::modeChanged(int _nvmode)
{

    mMode = _nvmode;

}

void OpenGLComposite::LumaChanged(bool)
{

}

void OpenGLComposite::alphaChanged(int _a)
{

    mAlpha = (float)_a/100;
}


void OpenGLComposite::set_pgm_value(int _pgm)
{
     //vrai si l'identifiant de la comboBox est le même que celui du bouton actuellement enclenché ...
    mPgm_value = _pgm;
}


void OpenGLComposite::set_pvw_value(int _pvw)
{
    mPvw_value = _pvw;
}

OpenGLComposite::~OpenGLComposite()
{
    for (int i = 0; i <10; i++)
        glDeleteTextures(mNb_input, (GLuint*)&mTextureTab.at(i)) ;

}

void OpenGLComposite::get_vision_balance(QColor color, int id, int mIDsource)
{
if (id == 0)
    m_color_data[mIDsource]->lift = color;
else if (id == 1)
    m_color_data[mIDsource]->gamma = color;
else if (id == 2)
    m_color_data[mIDsource]->gain = color;

}


void OpenGLComposite::get_vision_levels(int value, int id, int mIDsource)
{
    if (id == 0)
        m_color_data[mIDsource]->l_gamma = value;
    else if (id == 1)
        m_color_data[mIDsource]->bl = value;
    else if (id == 2)
        m_color_data[mIDsource]->wl = value;
    else if (id == 3)
        m_color_data[mIDsource]->wc_k = value;
    else if (id == 4)
        m_color_data[mIDsource]->wc_r = value;

}
