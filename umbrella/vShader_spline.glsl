#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


attribute vec4 vertexAttr;
uniform mat4 matrix;
in vec3 colorAttr;

varying vec3 color;


uniform float time;
//Параметры волны
uniform float K;
uniform float velocity;
uniform float amp;


void main()
{


    float u=K*(vertexAttr[0]-velocity*time);
    vertexAttr[1]=amp*sin(u);



    gl_Position=matrix * vertexAttr;
    color=vec4(0.5f,0.6f,0.1f,1);
}
