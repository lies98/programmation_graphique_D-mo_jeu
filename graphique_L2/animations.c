

#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include "animations.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL2/SDL_image.h>

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLuint _quadId = 0;

void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}
void animation_flash(int state) {
  /* INITIALISEZ VOS VARIABLES */
int l,i;
Uint16 * s;
static GLuint _quad = 0;
int vp[4];
/*!\brief identifiant du (futur) GLSL program */
static GLuint _pId = 0;
static GLfloat c = 0;
static GLfloat co[4]={0,0,0,0};
  switch(state) {
  case GL4DH_INIT:
  
  glGetIntegerv(GL_VIEWPORT, vp);
  _pId = gl4duCreateProgram("<vs>shaders/basic2.vs", "<fs>shaders/basic2.fs", NULL);
  /* Set de la couleur (RGBA) d'effacement OpenGL */
  glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
  /* dans quelle partie de l'écran on effectue le rendu */
  /* génération de la géométrie du quadrilatère */
  _quad = gl4dgGenQuadf();
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
//printf("%f\n", c[i]);
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    c = s[0];
    if(l >= 8)
      for(i = 0; i < 4; i++){
        co[i] = s[i] / ((1 << 16) - 1.0);
//printf("%f\n", c[i]);
      }
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
  
  /* effacement du buffer de couleur */
  glClear(GL_COLOR_BUFFER_BIT);
  /* activation du programme de rendu _pId */
  glUseProgram(_pId);
  /* envoi de la valeur de la variable c dans la variable uniform
   * count du côté shader (GPU). Puis c incrémente de 1 pour l'appel
   * suivant. */
  glUniform1i(glGetUniformLocation(_pId, "count"),c);
  /* dessin de la géométrie du quadrilatère */
  glClearColor(co[0], co[1], co[2],co[3]);
  gl4dgDraw(_quad);
  /* désactiver le programme shader */
  glUseProgram(0);
    return;
  }
}

void animation_vide(int state) {
  switch(state) {
  case GL4DH_DRAW:
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return;
  default:
    return;
  }
}

void animation_base2(int state) {
  int l;
  Uint16 * s;

  static GLfloat c[1024] ;
  static GLfloat d=90;
  switch(state) {
  case GL4DH_INIT:
    base2_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if(l>= 4095)
    for(int i = 0; i < 10; i++)
      c[i] = 256 / 2 + (256 / 2) * s[i] / ((1 << 15) - 1.0);
    return;
  default: /* GL4DH_DRAW */

    base2_draw(c);
    return;
  }
}

void animation_earth(int state) {
  switch(state) {
  case GL4DH_INIT:
    earth_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    earth_draw();
    return;
  }
}

void animation_anim2(int state) {
  switch(state) {
  case GL4DH_INIT:
    anim2_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    anim2_draw();
    return;
  }
}



void animation_anim4(int state) {
  switch(state) {
  case GL4DH_INIT:
    anim4_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    anim4_draw();
    return;
  }
}

void credits(int state) {
    switch(state) {
        case GL4DH_INIT:
            initt();
            return;
        case GL4DH_FREE:
            return;
        case GL4DH_UPDATE_WITH_AUDIO:
            return;
        default: /* GL4DH_DRAW */
            drawt();
            return;
    }
}



void animation_ear(int state) {
    switch(state) {
        case GL4DH_INIT:
            earth_ini();
            return;
        case GL4DH_FREE:
            return;
        case GL4DH_UPDATE_WITH_AUDIO:
            return;
        default: /* GL4DH_DRAW */
            earth_dra();
            return;
    }
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}
