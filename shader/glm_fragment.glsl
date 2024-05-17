#version 330 core
in vec3 ourColor;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float time;

void main()
{
    FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), abs(sin(time)));
}
