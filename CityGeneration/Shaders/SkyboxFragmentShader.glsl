#version 410 core

in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

void main()
{    
    color = clamp(texture(skybox, TexCoords) * 2.0f, 0.0f, 1.0f);
}