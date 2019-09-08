
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <SDL2/SDL_image.h>


static GLuint _pId = 0;



static GLuint _sphere = {0},_cube = 0, _quad = 0, _torus = 0;





void anim2_init(void) {
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
  _torus = gl4dgGenTorusf(300, 30, 0.1f);
}

void anim2_draw(void) {
  static GLfloat a0 = 0.0;
  static GLfloat b = 4.0;
  GLfloat rouge[] = {1, 0, 0, 0.5}, vert[] = {0, 1,0, 0.1}, bleu[] = {0, 0, 1, 0.7};

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.2f, 0.2f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -10.0);

  glUseProgram(_pId);




  gl4duPushMatrix(); {
    gl4duTranslatef(0, b, 0);
    if(b<=0)
      gl4duRotatef(a0, 1, 0, 0);
    gl4duScalef(3.5f, 3, 3);
    gl4duSendMatrices();
  } gl4duPopMatrix();

  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_torus);

  gl4duRotatef(a0, 0, 1, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_sphere);
  
  gl4duRotatef(a0, 1, 1, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, vert);
  gl4dgDraw(_cube);

  gl4duRotatef(-a0, 1, 1, 0);




  gl4duRotatef(-a0, 0, 1, 0);

  gl4duRotatef(a0, 1, 0, 0);
  gl4duRotatef(a0, 0, 1, 0);
  gl4duTranslatef(0, 0, 3);
 
  gl4duPushMatrix(); {
    gl4duScalef(0.5f, 0.5f, 0.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, bleu);
  gl4dgDraw(_sphere);
  
  if(b>0)
    b-=0.01;


  a0 ++;
  //gl4dfBlur(0, 0, 5, 1, 0, GL_FALSE);
  gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
  gl4dfSobel(0, 0, GL_FALSE);
}

