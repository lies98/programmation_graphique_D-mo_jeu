/*!\file basic.fs
 *
 * \brief fragment shader basique qui applique une couleur à chaque
 * fragment de l'image.
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date March 11, 2018
 */
/* Version GLSL 3.30 */
#version 330
/* sortie du frament shader : une couleur */
out vec4 fragColor;

void main(void) {
  vec2 p = gl_FragCoord.xy - vec2(400,300);
  fragColor = vec4(0)  ;
}
