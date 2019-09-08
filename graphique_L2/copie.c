
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <SDL2/SDL_image.h>


static GLuint _pId = 0;

static GLfloat _lumPos0[4] = {1500.0, 20.0, 30.0, 1.0};

static GLuint _tId[11] = {0};

static GLuint _sphere = {0},_cube = 0, _quad = 0, _torus = 0,_torus1=0;





void earth_ini(void) {
  int i;
  SDL_Surface * t;
  int vp[4], w, h;
  static char * files[] = {"images/sun.jpg", "images/sphere.jpg", "images/Mercure.jpg","images/Venus.jpg","images/Lune.jpg","images/Mars.jpg","images/Jupiter.jpg","images/Saturne.jpg","images/Uranus.jpg","images/Neptune.jpg","images/silver.jpg" };
  _pId  = gl4duCreateProgram("<vs>shaders/earth1.vs", "<fs>shaders/earth1.fs", NULL);
  glGetIntegerv(GL_VIEWPORT, vp);
  w = vp[2] - vp[0];
  h = vp[3] - vp[1];
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  glGenTextures(11, _tId);
  for(i = 0; i < 11; i++) {
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
  _torus = gl4dgGenTorusf(300, 30, 0.01f);
  _torus1 = gl4dgGenTorusf(300, 30, 0.1f);
}

void earth_dra(void) {
  static GLfloat a0 = 0.0;
  static Uint32 t0 = 0, t;
  GLfloat dt = 0.0, lumPos[4], *mat;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, -6, -50.0);
  mat = gl4duGetMatrixData();
  MMAT4XVEC4(lumPos, mat, _lumPos0);

  glUseProgram(_pId);



  glUniform4fv(glGetUniformLocation(_pId, "lumPos"), 1, lumPos);
  glUniform1i(glGetUniformLocation(_pId, "specular"), 1);
  /* envoi de toutes les matrices stockées par GL4D */

 //mercure
  gl4duPushMatrix(); {
    //gl4duRotatef(a0, 1, 0, 0);
    gl4duScalef(3.5f, 3.5f, 3.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();

  glBindTexture(GL_TEXTURE_2D, _tId[10]);
  gl4dgDraw(_torus);
    //venus
  gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(5.6f, 5.5f, 5.6f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    //terre
  gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(7.8f,7.8f, 7.8f);
        gl4duSendMatrices();
   } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
 
    //mars
    gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(9.4f, 9.4f, 9.4f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    //jupiter
    
    gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(13.0f, 13.0f, 13.0f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    //saturn
    gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(16.5f, 16.5f, 16.5f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    //uranus
    gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(21.0f, 21.0f, 21.0f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    //neptun
    
    gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(24.0f,24.0f,24.0f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    
    
  gl4duPushMatrix(); {
        //gl4duRotatef(a0, 1, 0, 0);
        gl4duScalef(5.7f, 5.7f, 5.7f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    
    //LE SOLEIL
  gl4duRotatef(a0, 0, 1, 0);
  gl4duSendMatrices();
  glBindTexture(GL_TEXTURE_2D, _tId[0]);
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
    gl4duPushMatrix(); {
    gl4duRotatef(a0, 0, 1, 0);
    gl4duScalef(3.3f, 3.3f, 3.3f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4dgDraw(_sphere);

  gl4duRotatef(a0, 0, -1, 0);
    
    
//les planetes
    
  
    
    
//mercure
  gl4duRotatef(4*a0, 0, 1, 0);
  gl4duTranslatef(3.5, 0, 0);
 
  gl4duPushMatrix(); {

    gl4duRotatef(6*a0, 0, 1, 0);
    gl4duRotatef(10, 1, 0, 0);
    gl4duScalef(0.3f, 0.3f, 0.3f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glBindTexture(GL_TEXTURE_2D, _tId[2]);
  gl4dgDraw(_sphere);
    
   gl4duTranslatef(-3.5, 0, 0); 
   gl4duRotatef(-4*a0, 0, 1, 0);
   
//venus


   gl4duRotatef(1.6*a0, 0, 1, 0);


  gl4duTranslatef(5.7, 0, 0);
  
  gl4duPushMatrix(); {
    gl4duRotatef(1.5*a0, 0, 1, 0);
    gl4duRotatef(30, 1, 0, 0);
    gl4duScalef(0.5f, 0.5f, 0.5f);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glBindTexture(GL_TEXTURE_2D, _tId[3]);
  gl4dgDraw(_sphere);
  gl4duTranslatef(-5.7, 0, 0);
  gl4duRotatef(-1.6*a0, 0, 1, 0);
    
//terre
  gl4duRotatef(a0, 0, 1, 0);
  gl4duTranslatef(7.4, 0, 0);
    gl4duPushMatrix(); {
        gl4duRotatef(10*a0, 0, 1, 0);
        gl4duRotatef(230.5, 0, 1, 0);
        gl4duScalef(0.7f, 0.7f, 0.7f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[1]);
    gl4dgDraw(_sphere);
    
  
//la lune
   
    gl4duRotatef(20*a0, 0, 1, 0);
  
    gl4duTranslatef(1.0, 0, 0);
 
    gl4duPushMatrix(); {
         gl4duRotatef(10*a0, 0, 1, 0);
        gl4duScalef(0.2f, 0.2f, 0.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4duTranslatef(-1.0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, _tId[4]);
    gl4dgDraw(_sphere);
    gl4duRotatef(20*a0, 0, -1, 0);
   
    gl4duTranslatef(-7.4, 0, 0);
     gl4duRotatef(a0, 0, -1, 0);

   
//mars
    
    gl4duRotatef(0.5*a0, 0, 1, 0);

    gl4duTranslatef(9.5, 0, 0);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10.05*a0, 0, 1, 0);
        gl4duRotatef(250, 0, 1, 0);
        gl4duScalef(0.45f, 0.45f, 0.45f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[5]);
    gl4dgDraw(_sphere);

    gl4duTranslatef(-9.5, 0, 0);
    gl4duRotatef(-0.5*a0, 0, 1, 0);
    
//jupiter

     gl4duRotatef(0.08*a0, 0, 1, 0);
    gl4duTranslatef(12.3, 0, 0);
    
    gl4duPushMatrix(); {
        gl4duRotatef(22*a0, 0, 1, 0);
        gl4duRotatef(30.5, 0, 1, 0);
        gl4duScalef(1.5f, 1.5f, 1.5f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[6]);
    gl4dgDraw(_sphere);

    //IO

    gl4duRotatef(2*a0, 1, 1, 0);
    gl4duTranslatef(1.8, 0, 0);
 
    gl4duPushMatrix(); {
         gl4duRotatef(22*a0, 0, 1, 0);
        gl4duScalef(0.2f, 0.2f, 0.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4duTranslatef(-1.8, 0, 0);
    glBindTexture(GL_TEXTURE_2D, _tId[4]);
    gl4dgDraw(_sphere);
    gl4duRotatef(-2*a0, 1, 1, 0);
  //europe

    gl4duRotatef(2*a0, 0, 1, 1);
    gl4duTranslatef(2.1, 1, 0);
 
    gl4duPushMatrix(); {
         gl4duRotatef(22*a0, 0, 1, 0);
        gl4duScalef(0.2f, 0.2f, 0.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4duTranslatef(-2.1, -1, 0);
    glBindTexture(GL_TEXTURE_2D, _tId[4]);
    gl4dgDraw(_sphere);
    gl4duRotatef(-2*a0, 0, 1, 1);

      //Ganymède

    gl4duRotatef(2*a0, 1, 0, 1);
    gl4duTranslatef(-2.1, -1, 0);
 
    gl4duPushMatrix(); {
         gl4duRotatef(22*a0, 0, 1, 0);
        gl4duScalef(0.2f, 0.2f, 0.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4duTranslatef(2.1, 1, 0);
    glBindTexture(GL_TEXTURE_2D, _tId[4]);
    gl4dgDraw(_sphere);
    gl4duRotatef(-2*a0, 1, 0, 1);

   //callisto
    gl4duRotatef(2*a0, 1, 1, 1);
    gl4duTranslatef(-1.8, 1, 0);
 
    gl4duPushMatrix(); {
         gl4duRotatef(22*a0, 0, 1, 0);
        gl4duScalef(0.2f, 0.2f, 0.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4duTranslatef(1.8, -1, 0);
    glBindTexture(GL_TEXTURE_2D, _tId[4]);
    gl4dgDraw(_sphere);
        gl4duRotatef(-2*a0, 1, 1, 1);


    gl4duTranslatef(-12.3, 0, 0);
  gl4duRotatef(-0.08*a0, 0, 1, 0);
  
    
//saturn

    gl4duRotatef(0.03*a0, 0, 1, 0);
    gl4duTranslatef(16.8, 0, 0);
    
    gl4duPushMatrix(); {

        gl4duRotatef(21*a0, 0, 1, 0);
        gl4duRotatef(270, 0, 1, 0);
        gl4duScalef(1.2f, 1.2f, 1.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[7]);
    gl4dgDraw(_sphere);
    
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(1.5f,1.5f,1.5f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(1.6f,1.6f,1.6f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(1.7f,1.7f,1.7f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(1.8f,1.8f,1.8f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(1.9f,1.9f,1.9f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.0f,2.0f,2.0f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.1f,2.1f,2.1f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.2f,2.2f,2.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.3f,2.3f,2.3f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.3f,2.3f,2.3f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.3f,2.3f,2.3f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);
    
    gl4duPushMatrix(); {
        gl4duRotatef(10, 1, 0, 0);
        gl4duScalef(2.2f,2.2f,2.2f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, _tId[10]);
    gl4dgDraw(_torus);

    gl4duTranslatef(-16.8, 0, 0);
    gl4duRotatef(-0.03*a0, 0, 1, 0);
   
    



    
//uranus

    gl4duRotatef(0.01*a0, 0, 1, 0);
    gl4duTranslatef(20.8, 0.5, 0);
    
    gl4duPushMatrix(); {
        gl4duRotatef(15*a0, 0, 1, 0);
        gl4duRotatef(980, 0, 1, 0);
        gl4duScalef(0.5f, 0.5f, 0.5f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[8]);
    gl4dgDraw(_sphere);


    gl4duTranslatef(-20.8, 0.5, 0);
    gl4duRotatef(-0.01*a0, 0, 1, 0);
    
//neptun

    gl4duRotatef(0.006*a0, 0, 1, 0);
    gl4duTranslatef(23.8, -0.2, 0);
    
    gl4duPushMatrix(); {
        gl4duRotatef(17*a0, 0, 1, 0);
        gl4duRotatef(300, 0, 1, 0);
        gl4duScalef(0.5f, 0.5f, 0.5f);
        gl4duSendMatrices();
    } gl4duPopMatrix();
    glBindTexture(GL_TEXTURE_2D, _tId[9]);
    gl4dgDraw(_sphere);
    


    
    

  a0 +=3.0;
  //gl4dfBlur(0, 0, 5, 1, 0, GL_FALSE);
  gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
  gl4dfSobel(0, 0, GL_FALSE);
}

