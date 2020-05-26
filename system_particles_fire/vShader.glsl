#version 330 core

layout(location=0) in vec4 vertexAttr;
layout(location=1) in vec3 colorAttr;

uniform mat4 matrix;

out vec3 color;
void main()
{
    gl_Position=matrix * vertexAttr;
    color=colorAttr;
}
