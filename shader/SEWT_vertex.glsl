#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 textCoords;

out vec3 ourColor;
out vec2 TexCoords;

uniform float time;

void main()
{
    mat4 rotateAroundY = mat4
    (
        cos(time), 0.0, sin(time), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(time), 0.0, cos(time), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    vec4 newPos = rotateAroundY * vec4(aPos, 1.0);

    ourColor = aColor;
    TexCoords = textCoords;
    gl_Position = vec4(newPos.xyz, 1.0);

}