
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <SDL2/SDL_image.h>


static GLuint _pId = 0;

static GLfloat _lumPos0[4] = {1500.0, 20.0, 30.0, 1.0};

static GLuint _tId[7] = {0};

static GLuint _sphere = {0},_cube = 0, _quad = 0, _torus = 0;





void earth_init(void) {
  int i;
  SDL_Surface * t;
  int vp[4], w, h;
  static char * files[] = {"images/sphere.png", "images/sphere1.jpg", "images/sphere2.jpg","images/sphere3.jpg","images/gold.jpg","images/silver.jpg","images/bronze.jpg" };
  _pId  = gl4duCreateProgram("<vs>shaders/earth.vs", "<fs>shaders/earth.fs", NULL);
  glGetIntegerv(GL_VIEWPORT, vp);
  w = vp[2] - vp[0];
  h = vp[3] - vp[1];
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  glGenTextures(7, _tId);
  for(i = 0; i < 7; i++) {
    glBindTexture(GL_TEXTURE_2D, _tId[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t = IMG_Load(files[i])) != NULL ) {



      int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
      
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
      SDL_FreeSurface(t);
    } else {
      fprintf(stderr, "can't open file %s : %s\n", files[i], SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
  }
  _sphere = gl4dgGenSpheref(30, 30);
  _cube = gl4dgGenCubef();
  _quad = gl4dgGenQuadf();
  _torus = gl4dgGenTorusf(300, 30, 0.1f);
}

void earth_draw(void) {
  static GLfloat a0 = 0.0;
  static Uint32 t0 = 0, t;
  GLfloat dt = 0.0, lumPos[4], *mat;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2f, 0.2f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -10.0);
  mat = gl4duGetMatrixData();
  MMAT4XVEC4(lumPos, mat, _lumPos0);

  glUseProgram(_pId);



  glUniform4fv(glGetUniformLocation(_pId, "lumPos"), 1, lumPos);
  glUniform1i(glGetUniformLocation(_pId, "specular"), 1);
  /* envoi de toutes les matrices stockées par GL4D */


  gl4duPushMatrix(); {
    gl4duRotatef(a0, 1, 0, 0);
    gl4duScalef(3.5f, 3, 3);
    gl4duSendMatrices();
  } gl4duPopMatrix();

  glBindTexture(GL_TEXTURE_2D, _tId[5]);
  gl4dgDraw(_torus);

    gl4duPushMatrix(); {
    gl4duRotatef(90, 1, 0, 0);
    gl4duRotatef(a0, 1, 0, 0);
    gl4duScalef(3.5f, 3, 3);
    gl4duSendMatrices();
  } gl4duPopMatrix();

  glBindTexture(GL_TEXTURE_2D, _tId[4]);
  gl4dgDraw(_torus);
  
  gl4duPushMatrix(); {
    gl4duRotatef(45, 1, 0, 0);
    gl4duRotatef(a0, 1, 0, 0);
    gl4duScalef(3.5f, 3, 3);
    gl4duSendMatrices();
  } gl4duPopMatrix();

  glBindTexture(GL_TEXTURE_2D, _tId[6]);
  gl4dgDraw(_torus);
/*
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[2]);
  */
  gl4duRotatef(a0, 0, 1, 0);
  gl4duSendMatrices();
  glBindTexture(GL_TEXTURE_2D, _tId[0]);
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_sphere);

  gl4duRotatef(-a0, 0, 1, 0);

  gl4duRotatef(a0, 1, 0, 0);
  gl4duRotatef(a0, 0, 0, 1);
  gl4duTranslatef(0, 3, 0);
 
  gl4duPushMatrix(); {
    gl4duScalef(0.5f, 0.5f, 0.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glBindTexture(GL_TEXTURE_2D, _tId[1]);
  gl4dgDraw(_sphere);

  gl4duRotatef(3 * a0, 1, 0, 0);
  gl4duSendMatrices();
  glBindTexture(GL_TEXTURE_2D, _tId[4]);
  gl4dgDraw(_torus);


    gl4duRotatef(3 * -a0, 1, 0, 0);
  gl4duTranslatef(0, -3, 0);
  gl4duRotatef(-a0, 0, 0, 1);
  gl4duRotatef(-a0, 1, 0, 0);





  gl4duRotatef(a0, 1, 0, 0);
  gl4duRotatef(a0, 0, 1, 0);
  gl4duTranslatef(0, 0, 3);
  //gl4duRotatef(3 * a0, 1, 0, 0);

  gl4duPushMatrix(); {
    gl4duScalef(0.5f, 0.5f, 0.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glBindTexture(GL_TEXTURE_2D, _tId[2]);
  gl4dgDraw(_sphere);
  
  gl4duRotatef(3 * a0, 1, 0, 0);
  gl4duSendMatrices();
  glBindTexture(GL_TEXTURE_2D, _tId[5]);
  gl4dgDraw(_torus);

  gl4duRotatef(3 * -a0, 1, 0, 0);
  gl4duTranslatef(0, 0,-3);
  gl4duRotatef(-a0, 0, 1, 0);
  gl4duRotatef(-a0, 1, 0, 0);
 


   
  gl4duRotatef(a0, 1, 0, 0);
  gl4duRotatef(a0, 0, 1, 1);
  
  gl4duTranslatef(3,0, 0);
  

  gl4duPushMatrix(); {
    gl4duScalef(0.5f, 0.5f, 0.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glBindTexture(GL_TEXTURE_2D, _tId[3]);
    gl4dgDraw(_sphere);

  
  gl4duRotatef(3 * a0, 1, 0, 0);
  gl4duSendMatrices();
  glBindTexture(GL_TEXTURE_2D, _tId[6]);
  gl4dgDraw(_torus);

  a0 += 360.0 * dt / (6.0);
  //gl4dfBlur(0, 0, 5, 1, 0, GL_FALSE);
  gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
  gl4dfSobel(0, 0, GL_FALSE);
}

