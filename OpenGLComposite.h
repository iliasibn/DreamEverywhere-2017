#ifndef __OPENGL_COMPOSITE_H__
#define __OPENGL_COMPOSITE_H__

// OpenGL includes - Included here and hence shared by all the files that need OpenGL headers.
#if QT_VERSION >= 0x040000
# include <QGLWidget>
#else
# include <qgl.h>
#endif

// GLU was removed from Qt in version 4.8
#ifdef Q_OS_MAC
# include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif
#include <color_data.h>

#include <QOpenGLFunctions_3_1>
/////////////////////////////////////////////////////////////
// Classe représentant le contexte et le composite OpenGL
/////////////////////////////////////////////////////////////

class OpenGLComposite : public QGLWidget
{
    Q_OBJECT

public:

    /*
     * Crée un OpenGLComposite et initialise les variables,
     */
    OpenGLComposite(QWidget *parent = NULL, int = 0, int = 0);

    /*
    * Détruit l'objet
    */
    ~OpenGLComposite();

    /*
     * Rend les effets et met à jour le buffer de sortie OpenGL
     */
    void GLC_rendering();

    /*
     * @return : Renvoie une référence vers le pointeur GLoutFrame
     */
    void** link_outFrame();

private:

    /* Vérifie la compatibilité d'OpenGL pour l'utilisation du FBO
     * @return : vrai si tout s'est bien passé
     */
    bool CheckOpenGLExtensions();
    // QGLWidget virtual methods
    virtual void initializeGL();                    // Initialise l'environnement de travail OpenGL
    virtual void paintGL();                         // Affiche le buffer
    virtual void resizeGL(int width, int height);   // MAJ de la fenêtre de sortie (callback)

    /*
     * On traite la fenêtre programme ou preview selon les paramètres d'effet
     */
    void traitement_pgm(int,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint, GLint, GLint, GLint, GLint, GLint);
    void traitement_pvw(int,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint, GLint, GLint, GLint,GLint, GLint);
    void traitement_grading(int,GLint);

    /*
     * Initialisation OpenGL
     */
    bool   InitOpenGLState();
    QOpenGLFunctions_3_1 m_openGL31Functions;
    /*
     * On compile le code GLSL, utilisé pour le fragment shader
     * @param int : Taille du message d'erreur, char* : Message d'erreur
     */
    bool                            compileFragmentShader(int errorMessageSize, char* errorMessage);

    /*
     * Traitement successif du preview et program
     */
    void                            traitement_texture();


    //Qt
    QWidget*						mParent;

    // GLSL
    int                             mMode;
    int                             mCurrent_wipe;
    int                             mModepip;
    float                           mAlpha;
    float                           mTaille_pip;
    float                           mPos_x;
    float                           mPos_y;
    int                             mSeuil;                          // Seuil de l'incrustation
    int                             mTolerance;                      // Tolérance de l'incrusation
    QColor                          mKeyer_color;                    // Couleur de l'incrusation
    bool                            mKeyer_mode;                     // Mode de l'incrusation (chrominance ou luminance)
    int                             mIris_value;                     // Valeur de l'iris virtuel

    // OpenGL data
    COLOR_DATA *m_color_data[10];
    int                                 mFrameWidth;
    int                                 mFrameHeight;
    void*                               mGLoutFrame;                 // Buffer utilisé pour stocker les données renvoyées à la carte de sortie
    int                                 mNb_input;
    QVector<GLuint>                     mTextureTab;
    GLuint								mUnpinnedTextureBuffer;
    GLuint								mIdFrameBuf;
    GLuint								mIdColorBuf;
    GLuint								mIdDepthBuf;
    GLuint								mProgram_e;
    GLuint                              mProgram_cg;
    GLuint								mFragmentShader[2];
    GLuint								mFragmentShadermix;
    GLuint								mProgrammix;
    int									mViewWidth;
    int									mViewHeight;
    int                                 mPgm_value;
    int                                 mPvw_value;
    int GLOBAL_HEIGHT;
    int GLOBAL_WIDTH ;

    GLuint renderPGM;
    GLuint renderPVW;
    GLuint FBO_cg_pgm;
    GLuint FBO_cg_pvw;


private slots:

    /* Modifie la valeur de l'alpha
     * @param: Valeur de l'alpha
     */
    void alphaChanged(int _alpha);

    /* Modifie le mode d'incrustation
     * @param: 0 ou 1
     */
    void LumaChanged(bool);

    /* Modifie les paramètres d'incrusation
     * @param: int : , bool: , int: , int: , QColor: Couleur d'incrustation
     */
    void set_luma_param(int, bool, int, int, QColor);

    /* Modifie les paramètres de PIP
     * @param: int : ON AIR ou pas, int: Paramètre de taille, int: Paramètre de position verticale, int: Paramètre de position horizontale
     */
    void set_pip_param(int, int, int, int);

    /* Modifie l'effet utilisé dans GLSL
     * @param: Indice du mode ( = indice de l'effet)
     */
    void modeChanged(int);

    /* Modifie le preview
     * @param: Indice de la texture OpenGL
     */
    void set_pvw_value(int);

    /* Modifie le program
     * @param: Indice de la texture OpenGL
     */
    void set_pgm_value(int);

    /* Modifie le wipe
     * @param: Niveau d'avancement du wipe
     */
    void slot_set_wipe(int _wipe);

    /* Change la valeur de l'exposition virtuelle
     * @param: Iris virtuel
     */
    void irisChanged(int _nv_iris);

    void get_vision_balance(QColor, int, int);
    void get_vision_levels(int, int, int);

public slots:
    /*
     * Met à jour les textures en entrée de GLSL, à partir des données pointeur GLinFrame;
     */
    void GLC_bindto(void**, int);

};

#endif	// __OPENGL_COMPOSITE_H__
