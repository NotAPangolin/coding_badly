precision highp float;#define GLSLIFY 1
varying vec3 vPosition;
uniform vec3 ucolor;
uniform float uopacity;
void main(void) {
      float opacity = (96.0 - length(vPosition)) / 256.0 * 0.6;
 gl_FragColor = vec4(ucolor, opacity*uopacity);
}
