attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES      
precision mediump float;
varying mediump vec2 v_texCoord1;
#else
varying vec2 v_texCoord1;
#endif

void main(void)
{

   v_texCoord1 = a_texCoord;

   gl_Position = CC_PMatrix * a_position;
}   