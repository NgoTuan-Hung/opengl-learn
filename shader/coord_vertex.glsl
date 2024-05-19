#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textCoords;

out vec2 TexCoords;

uniform mat4 rotate;

void main()
{
    TexCoords = textCoords;
    gl_Position = rotate * vec4(aPos , 1.0);
}