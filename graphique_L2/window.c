/*!\file window.c
 *
 * \brief Utilisation de GL4Dummies pour réaliser une démo.
 *
 * Ici est géré l'ouverture de la fenêtre ainsi que l'ordonnancement
 * des animations. Apriori les seuls éléments à modifier ici lors de
 * votre intégration sont le tableau static \ref _animations et le nom
 * du fichier audio à lire.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014 - February 26, 2016
 */
#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"

/* Prototypes des fonctions statiques contenues dans ce fichier C. */
static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

/*!\brief tableau contenant les animations sous la forme de timeline,
 * ce tableau se termine toujours par l'élémént {0, NULL, NULL,
 * NULL} */
static GL4DHanime _animations[] = {
  
    { 5000, animation_vide, animation_base2, transition_fondu },
    { 10000, animation_base2, NULL, NULL },
    { 5000, animation_base2, animation_flash, transition_fondu },
    
    { 8000, animation_flash, NULL, NULL },
    
    { 5000, animation_vide, animation_anim4, transition_fondu },
    { 5000, animation_anim4, NULL, NULL },
    { 5000, animation_anim4, animation_flash, transition_fondu },
    

    { 5000, animation_flash, animation_anim2, transition_fondu },
    { 10000, animation_anim2, NULL, NULL },
    { 5000, animation_anim2, animation_vide, transition_fondu },
    
    { 5000, animation_flash, NULL, NULL },
    
    { 5000, animation_vide, animation_earth, transition_fondu },
    { 10000, animation_earth, NULL, NULL },
    { 5000, animation_earth, animation_flash, transition_fondu },
    { 5000, animation_vide, animation_ear, transition_fondu },
    { 10000, animation_ear, NULL, NULL },
    { 5000, animation_ear, animation_flash, transition_fondu },

    { 5000, animation_vide, credits, transition_fondu },
    { 10000, credits, NULL, NULL },
    { 5000, credits, animation_flash, transition_fondu },





  {    0, NULL, NULL, NULL } /* Toujours laisser à la fin */
};

/*!\brief dimensions initiales de la fenêtre */
static GLfloat _dim[] = {700, 700};

/*!\brief fonction principale : initialise la fenêtre, OpenGL, audio
 * et lance la boucle principale (infinie).
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies DemoHelper", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("ALONE.MOD");
  gl4duwMainLoop();
  return 0;
}

/*!\brief Cette fonction initialise les paramètres et éléments OpenGL
 * ainsi que les divers données et fonctionnalités liées à la gestion
 * des animations.
 */
static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

/*!\brief paramétre la vue (viewPort) OpenGL en fonction des
 * dimensions de la fenêtre.
 * \param w largeur de la fenêtre.
 * \param w hauteur de la fenêtre.
 */
static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

/*!\brief permet de gérer les évènements clavier-down.
 * \param keycode code de la touche pressée.
 */
static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

/*!\brief appelée à la sortie du programme (atexit).
 */
static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}
