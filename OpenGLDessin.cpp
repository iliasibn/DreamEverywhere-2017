
#include "OpenGLComposite.h"

#include <QTime>
//#include <opencv2/imgproc/imgproc.hpp>
#include "conversion.cpp"
#include "stdio.h"


using namespace std;

void OpenGLComposite::GLC_rendering()
{

    // On lit les pixels dans un buffer utile pour la lecture sur carte de sortie
   glReadPixels(GLOBAL_WIDTH, 0, mFrameWidth, mFrameHeight, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, mGLoutFrame);

    makeCurrent();

    // Activation du FBO
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, idFBO);
    glViewport(0, 0, 1920, 1080);

    // Changement de la couleur de background
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    // Rafraichissement des buffers (reset)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint locId = glGetUniformLocation(mProgram_cg,"id");
    GLint locTexture = glGetUniformLocation(mProgram_cg,"texture");
    traitement_grading(locId, locTexture);

    // Dessiner la scene OpenGL sur le buffer off-screen
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mIdFrameBuf);
    // Configurer la vue et la projection
    GLfloat aspectRatio = (GLfloat)mFrameWidth / (GLfloat)(mFrameHeight);
    glViewport (0, 0, mFrameWidth*2, mFrameHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0f, aspectRatio, 0.1f, 100.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(1.0,1.0,1.0,1.0);
    glScalef( aspectRatio, 1.0f, 1.0f );			// Scale x for correct aspect ratio
    glTranslatef( 0.0f, 0.0f, -3.4f );				// Move into screen
    glFinish();


    // On rend la texture et on met à jour la fenêtre
    traitement_texture();
    updateGL();


}

void OpenGLComposite::traitement_grading(GLint locId, GLint locTexture)
{
    int id = 0;

 glUseProgram(mProgram_cg);

 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    // Bind texture unit 0
    glUniform1i(locTexture, 0);
    glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(id));
    glUniform1f(locId, id);

    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(  1.0f,  1.0f,  1.0f );		// Top right of front side
    glVertex3f( -1.0f,  1.0f,  1.0f );		// Top left of front side
    glVertex3f( -1.0f, -1.0f,  1.0f );		// Bottom left of front side
    glVertex3f(  1.0f, -1.0f,  1.0f );		// Bottom right of front side
    glEnd();
    glPopMatrix();

    glUseProgram(1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}

void OpenGLComposite::traitement_pgm(int mode_de_traitement_pgm, GLint locMode, GLint locAlpha,GLint locBeta,GLint locR,GLint locG,GLint locB,GLint locTextureA, GLint locTextureB, GLint locTextureC, GLint locIris, GLint locTaillePip, GLint locPosX, GLint locPosY, GLint locModepip)
{
    int i = 0;
    /* *********************************************************

       TRAITEMENT DU PGM

       **********************************************************/
    // On passe les textures et les paramètres au shader comme des variables uniformes

    glUseProgram(mProgram_e);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glUniform1i(locTextureA, 0);		// Bind texture unit 0

    if (mPgm_value == 99 || mPgm_value == 98)
        glBindTexture(GL_TEXTURE_2D, 0);
    else if(mPgm_value == 1)
 glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);

    glUniform1i(locTextureB,1);		// Bind texture unit 0
    if (mPvw_value == 99|| mPvw_value == 98)
        glBindTexture(GL_TEXTURE_2D, 0);
    else
        glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(mPvw_value));


    glActiveTexture(GL_TEXTURE2);
    glEnable(GL_TEXTURE_2D);

    glUniform1i(locTextureC, 2);		// Bind texture unit 0
    if (mPgm_value == 99|| mPgm_value == 98)
        glBindTexture(GL_TEXTURE_2D, 0);
    else
        glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(mPgm_value));

    //0 rien 1mix 2 luma 3 chroma 4 volet
    glUniform1f(locMode,mode_de_traitement_pgm);

    if (mode_de_traitement_pgm == 2 || mode_de_traitement_pgm == 3)//Keyer
    {
        glUniform1f(locAlpha,1-(float)mSeuil/100);
        glUniform1f(locBeta,(float)mTolerance/100);
    }else if (mode_de_traitement_pgm == 4) // volets
    {
        glUniform1f(locIris,mIris_value);
        glUniform1f(locAlpha,mAlpha);
        glUniform1f(locBeta,mCurrent_wipe);
    }else if (mode_de_traitement_pgm == 9)

    {
        glUniform1f(locTaillePip, mTaille_pip);
        glUniform1f(locPosX, mPos_x);
        glUniform1f(locPosY, mPos_y);
        glUniform1f(locModepip, mModepip);
    }else
    {
        glUniform1f(locAlpha,mAlpha);
        glUniform1f(locBeta,1);
        glUniform1f(locIris,mIris_value);
    }
    glUniform1i(locR, mKeyer_color.red());
    glUniform1i(locG,  mKeyer_color.green());
    glUniform1i(locB,  mKeyer_color.blue());

    // PROGRAM
    glPushMatrix();
    glTranslatef(1.0f,0.0f,0.00001f);
    glBegin(GL_QUADS);
    glTexCoord2f(2.0f, 0.0f);	glVertex3f(  1.0f,  1.0f,  1.0f );		// Top right of front side
    glTexCoord2f(0.0f, 0.0f);	glVertex3f( -1.0f,  1.0f,  1.0f );		// Top left of front side
    glTexCoord2f(0.0f, 1.0f);	glVertex3f( -1.0f, -1.0f,  1.0f );		// Bottom left of front side
    glTexCoord2f(2.0f, 1.0f);	glVertex3f(  1.0f, -1.0f,  1.0f );		// Bottom right of front side
    glEnd();
    glPopMatrix();

    glUseProgram(1);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


}

void OpenGLComposite::traitement_pvw(int mode_de_traitement_pvw, GLint locMode, GLint locAlpha,GLint locBeta,GLint locR,GLint locG,GLint locB,GLint locTextureA, GLint locTextureB, GLint locTextureC, GLint locIris, GLint locTaillePip, GLint locPosX, GLint locPosY, GLint locModePip)
{
    /* *********************************************************

       TRAITEMENT DU PVW

       **********************************************************/
// On passe les textures et les paramètres au shader comme des variables uniformes

    glUseProgram(mProgram_e);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glUniform1i(locTextureA, 0);		// Bind texture unit 0

    if (mPvw_value == 99|| mPvw_value == 98)
        glBindTexture(GL_TEXTURE_2D, 0);
    else
        glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(mPvw_value));

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glUniform1i(locTextureB, 1);		// Bind texture unit 0
    if (mPgm_value == 99 || mPgm_value == 98 )
        glBindTexture(GL_TEXTURE_2D, 0);
    else
        glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(mPgm_value));

    glActiveTexture(GL_TEXTURE2);
    glEnable(GL_TEXTURE_2D);
    glUniform1i(locTextureC, 2);		// Bind texture unit 0
    if (mPgm_value == 99|| mPgm_value == 98)
        glBindTexture(GL_TEXTURE_2D, 0);
    else
        glBindTexture(GL_TEXTURE_2D,  mTextureTab.at(mPgm_value));

    //0 mix 1 luma 2 chroma
    glUniform1f(locMode,mode_de_traitement_pvw);

    if (mode_de_traitement_pvw == 9)//Pip
    {
        glUniform1f(locTaillePip, mTaille_pip);
        glUniform1f(locPosX, mPos_x);
        glUniform1f(locPosY, mPos_y);
        glUniform1f(locModePip, mModepip);
    }

    glUniform1f(locAlpha,mAlpha);
    glUniform1f(locBeta,0);
    glUniform1i(locR, 0);
    glUniform1i(locG, 0);
    glUniform1i(locB, 1);
    glUniform1f(locIris,mIris_value);

    // PREVIEW
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(2.0f, 0.0f);	glVertex3f(  1.0f,  1.0f,  1.0f );		// Top right of front side
    glTexCoord2f(0.0f, 0.0f);	glVertex3f( -1.0f,  1.0f,  1.0f );		// Top left of front side
    glTexCoord2f(0.0f, 1.0f);	glVertex3f( -1.0f, -1.0f,  1.0f );		// Bottom left of front side
    glTexCoord2f(2.0f, 1.0f);	glVertex3f(  1.0f, -1.0f,  1.0f );		// Bottom right of front side
    glEnd();
    glPopMatrix();


    glUseProgram(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


}
void OpenGLComposite::traitement_texture()
{


    //0 mix 1 luma 2 chroma 3 volets
    int mode_de_traitement_pgm;
    int mode_de_traitement_pvw;

    if (mMode == 2 ) // si on est en keyer
        if (mKeyer_mode)//si on est en chroma
            mMode = 3;

    if (mMode == 9)
    { if (mModepip == 0)
        {
    mode_de_traitement_pgm = 8; //On sort du Wipe ou Mix pour le pgm
    mode_de_traitement_pvw = 9;
        }
        else
        {
            mode_de_traitement_pgm = 9;
            mode_de_traitement_pvw = 0;

        }
}
    else
    {
        mode_de_traitement_pgm = mMode;
        mode_de_traitement_pvw = 0;
    }

    if (mPgm_value == 99)
        mode_de_traitement_pgm = 6;
    if (mPvw_value == 99)
        mode_de_traitement_pvw = 6;
    if (mPgm_value == 98)
        mode_de_traitement_pgm = 7;
    if (mPvw_value == 98)
        mode_de_traitement_pvw = 7;


    GLint locMode = glGetUniformLocation(mProgram_e,"mode");
    GLint locAlpha = glGetUniformLocation(mProgram_e,"alpha")   ;
    GLint locIris = glGetUniformLocation(mProgram_e,"iris")   ;
    GLint  locBeta  = glGetUniformLocation(mProgram_e,"beta")   ;
    GLint      locR  = glGetUniformLocation(mProgram_e,"ch_r")    ;
    GLint      locG  = glGetUniformLocation(mProgram_e,"ch_g")    ;
    GLint      locB  = glGetUniformLocation(mProgram_e,"ch_b")    ;
    GLint locTextureA = glGetUniformLocation(mProgram_e,"textureA"); 	 // Première texture
    GLint locTextureB = glGetUniformLocation(mProgram_e,"textureB"); 	 // Seconde
    GLint locTextureC = glGetUniformLocation(mProgram_e,"textureC"); 	 // Seconde
    GLint locTaillePip = glGetUniformLocation(mProgram_e,"taille_pip");
    GLint locPosX = glGetUniformLocation(mProgram_e,"pos_x");
    GLint locPosY = glGetUniformLocation(mProgram_e,"pos_y");
    GLint locModepip = glGetUniformLocation(mProgram_e,"modepip");


    traitement_pgm(mode_de_traitement_pgm, locMode, locAlpha, locBeta, locR, locG, locB, locTextureA, locTextureB, locTextureC, locIris, locTaillePip, locPosX, locPosY, locModepip);
    traitement_pvw(mode_de_traitement_pvw, locMode, locAlpha, locBeta, locR, locG, locB, locTextureA, locTextureB, locTextureC, locIris, locTaillePip, locPosX, locPosY, locModepip);



}
