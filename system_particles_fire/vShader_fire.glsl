#version 330 core

layout(location=0) in vec4 vertexAttr;
layout(location=1) in vec3 veloc;
layout(location=2) in float w;
layout(location=3) in float direc;

uniform mat4 matrix;

out vec3 color;
out float phase;
out float vRot;

uniform float time;
uniform float heightOfNearPlane;
const float period=350.0f;


void main()
{

    vec3 pos = vertexAttr.xyz;

    phase = fract( w + time / period );
     gl_Position = matrix * vec4 ( pos + phase * veloc, 1.0 );
     float point_size =0.09 + 0.3 * (phase);
     gl_PointSize=(heightOfNearPlane * point_size) / gl_Position.w;

     vRot=direc*time/20.0f;

    color=vec3(1.0f,0.4f,0.0f);
}
