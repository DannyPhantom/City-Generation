#version 410 core

layout (location = 0) in vec3 position_attr;
layout (location = 1) in vec4 colour_attr;
layout (location = 2) in vec3 normal_attr;
layout (location = 3) in vec2 texcoords_attr;

out vec3 TexCoords;

uniform highp mat4 ModelViewMatrix;
uniform highp mat3 NormalMatrix;
uniform highp mat4 ProjectionMatrix;


void main()
{
    gl_Position =   ProjectionMatrix * ModelViewMatrix * vec4(position_attr, 1.0);  
    TexCoords = position_attr;
}  
