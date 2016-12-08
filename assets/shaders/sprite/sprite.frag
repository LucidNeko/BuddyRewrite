#version 330 core

in vec2 TexCoords;
in vec3 Color;

uniform sampler2D spritesheet;

out vec4 fragColor;

void main()
{
    fragColor = vec4(Color, 1.0) * texture(spritesheet, TexCoords);
}
