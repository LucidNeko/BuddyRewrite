#version 330 core

in vec2 TexCoords;
in vec3 Color;
in vec3 OutlineColor;

uniform sampler2D textTexture;

out vec4 fragColor;

#define SQUARE_TEXT
//#define GLOW_GAP

vec4 squareText(vec4 pixel)
{
#ifdef GLOW_GAP
           vec4 a = pixel.r * pixel.b * vec4(Color, 1.0);
#else
           vec4 a = pixel.r * vec4(Color, 1.0);
#endif

        vec4 b = pixel.g * vec4(OutlineColor, 1.0);

        vec4 color = a + b;
        color.a = color.a*color.a;
        return color;
}

vec4 smoothText(vec4 pixel)
{
    float r = pixel.r;
    float g = pixel.g * 1.5;

    vec4 a = sign(r) * vec4(Color, 1.0);
    vec4 b = g * vec4(OutlineColor, 1.0);
    b.a = b.a*b.a;

    return a + b;
}

void main()
{
#ifdef SQUARE_TEXT
        fragColor = squareText(texture(textTexture, TexCoords));
#else
        fragColor = smoothText(texture(textTexture, TexCoords));
#endif

//        fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
