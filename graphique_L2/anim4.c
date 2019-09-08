
#include <stdio.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>

/*!\brief identifiant du programme GLSL */
static GLuint _pId = 0;
/*!\brief quelques objets géométriques */
static GLuint _sphere = 0, _cube = 0, _quad = 0;

void anim4_init(void) {
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

void anim4_draw(void) {
  static GLfloat a = 0;
  static GLfloat b = -10;
  static GLfloat c = -1;
  GLfloat rouge[] = {1, 1, 1, 1}, vert[] = {1, 1, 1, 1}, bleu[] = {1, 1, 1, 1};

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  glUseProgram(_pId);
  gl4duTranslatef(0, 0, b);
  gl4duPushMatrix(); {
    gl4duTranslatef(0, c, 0.0);
    gl4duRotatef(a ,0, 1, 0);
    if (c > 2)
    gl4duRotatef(a ,1,1,1);
    gl4duScalef(2, 2, 2);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, vert);
  gl4dgDraw(_cube);

  gl4duTranslatef(0, 2*c, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_sphere);

  gl4duTranslatef(0, -2*c, 0);




  gl4duTranslatef(0, -1, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_sphere);


  gl4duTranslatef(0, 1, 0);

  gl4duRotatef(a ,0, 1, 0);

  if (c > 2)
    gl4duRotatef(a ,1,1,1);
  


  //gl4duRotatef(-90, 1, 0, 0);
  gl4duScalef(2, 2, 2);
  gl4duTranslatef(0,-c,0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, bleu);
  gl4dgDraw(_cube);



  gl4duTranslatef(0, -c, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_sphere);
  
  b = b - 0.05;
  c = c + 0.01;

  a++;

  //gl4dfBlur(0, 0, 5, 1, 0, GL_FALSE);
  gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
  gl4dfSobel(0, 0, GL_FALSE);

}
