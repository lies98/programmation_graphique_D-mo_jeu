
#include <stdio.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>

/*!\brief identifiant du programme GLSL */
static GLuint _pId = 0;
/*!\brief quelques objets géométriques */
static GLuint _sphere = 0, _cube = 0, _quad = 0;
/*!\brief tableau des identifiants de texture à charger */
static GLuint _tId[3] = {0};

void base2_init(void) {
    int vp[4], w, h;
    glGetIntegerv(GL_VIEWPORT, vp);
    w = vp[2] - vp[0];
    h = vp[3] - vp[1];
    _pId  = gl4duCreateProgram("<vs>shaders/base.vs", "<fs>shaders/base.fs", NULL);
    gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
    gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
    gl4duBindMatrix("projectionMatrix");
    gl4duLoadIdentityf();
    gl4duFrustumf(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 1.0, 1000.0);
    gl4duBindMatrix("modelViewMatrix");
    _sphere = gl4dgGenSpheref(30, 30);
    _cube = gl4dgGenCubef();
    _quad = gl4dgGenQuadf();
}

void base2_draw(GLfloat * a0) {
    static GLfloat a = 0;
    static GLfloat haut = 6;
    static GLfloat bas = -6;
    static GLfloat gauche = -6;
    static GLfloat droite = 6;
    GLfloat rouge[] = {1, 0, 0, 0.5}, vert[] = {0, 1, 0, 0.5}, bleu[] = {0, 0, 1, 1.0};
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl4duBindMatrix("modelViewMatrix");
    gl4duLoadIdentityf();
    glUseProgram(_pId);
    gl4duTranslatef(0, 0, -15.0);
    gl4duRotatef(a++, 0, 0, 1);
    if(a>=360)
        gl4duRotatef(a++, 0, 0, -1);
    
    gl4duPushMatrix(); {
        gl4duTranslatef(0, -0.0, -8.0);
        gl4duTranslatef(0,haut, 0);
        if(a>=365 && haut >0){
            haut -= 0.05;
        }
        gl4duScalef(3, 3, 3);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
    gl4dgDraw(_sphere);
    
    gl4duPushMatrix(); {
        gl4duTranslatef(0, -0.0, -8.0);
        gl4duTranslatef(droite, 0, 0);
        if(a>=365 && droite > 0){
            droite -= 0.05;
        }
        for(int i = 0; i <1024 ; i++)
            gl4duRotatef(a0[i], 0, 1, 1);
        gl4duScalef(3, 3, 3);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, vert);
    gl4dgDraw(_cube);
    
    if(a>=365 && bas <0){
        bas += 0.05;
    }
    gl4duTranslatef(0, bas, 0);
    gl4duSendMatrices();
    glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, bleu);
    gl4dgDraw(_sphere);
    if(a>=365 && gauche < 0){
        gauche += 0.05;
    }
    gl4duTranslatef(gauche, -bas, 0);
    
    for(int i = 0; i <1024 ; i++)
        gl4duRotatef(a0[i], 0, 1, 1);
    gl4duSendMatrices();
    glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
    gl4dgDraw(_cube);
    //gl4dfBlur(0, 0, 5, 1, 0, GL_FALSE);
    gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
    gl4dfSobel(0, 0, GL_FALSE);
}
