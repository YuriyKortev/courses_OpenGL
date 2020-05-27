#version 330 core

layout(location=0) in vec4 vertexAttr;
layout(location=2) in vec3 normAttr;
layout(location=3) in vec2 texCoord;




uniform mat4 matrix;
uniform mat4 modelview;
uniform mat4 model;

out vec3 tnorm;
out vec3 eyecoord;
out vec2 v_texCoord;
out vec3 FragPos;

vec4 plane=vec4(0,-1,0,0.5);

void main()
{



    FragPos=vec3(model*vec4(vertexAttr));

    tnorm=mat3(transpose(inverse(model))) * normAttr;

    eyecoord=vec3(modelview*vertexAttr);

    gl_Position=matrix * vertexAttr;
    v_texCoord=texCoord;
}
