    #ifdef GL_ES
	precision mediump float;
    varying mediump vec2 v_texCoord1;
    #else
    varying vec2 v_texCoord1;  
    #endif

void main (void)  
{     

vec4 col = texture2D(CC_Texture0, v_texCoord1);
if(col.r + col.g + col.b >= 2.0){
	col.r = 1.0;
	col.g = 0.0;
	col.b = 0.0;
}

if(col.r + col.g + col.b == 0.0){
	col.a = 0.0;
}

if(col.r > col.g + col.b){
	float red = col.r * abs(sin(CC_Time.x));
	col.r = red;
}

gl_FragColor = col;  
}                                                                                           