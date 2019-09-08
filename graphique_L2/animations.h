
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void animation_flash(int state);
  extern void animation_vide(int state);
  extern void animation_earth(int state);
  extern void animation_ear(int state);
  extern void animation_base2(int state);
  extern void animation_anim2(int state);
  extern void animation_anim4(int state);
  extern void credits(int state);

  extern void animationsInit(void);

  /* Dans earth.c */
  extern void earth_init(void);
  extern void earth_draw(void);
  /*dans anim.c */
  extern void base2_init(void);
  extern void base2_draw(GLfloat * a);
  /*dans anim2.c */
  extern void anim2_init(void);
  extern void anim2_draw(void);

  /*dans anim4.c */
  extern void anim4_init(void);
  extern void anim4_draw(void);
    
  /*dans text.c */
    extern void initt(void);
    extern void drawt(void);
    /*dans copie.c*/
    extern void earth_ini(void);
    extern void earth_dra(void);



#ifdef __cplusplus
}
#endif

#endif
