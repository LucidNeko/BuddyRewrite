#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 position;
layout(location = 2) in vec2 size;
layout(location = 3) in vec4 texInfo;
layout(location = 4) in vec3 color;
layout(location = 5) in float rotation;

out vec2 TexCoords;
out vec3 Color;

uniform mat4 projection;

mat4 translate(vec2 v)
{
    mat4 m = mat4(1.0);
    m[3][0] = v.x;
    m[3][1] = v.y;
    return m;
}

mat4 scale(vec2 v)
{
    mat4 m = mat4(1.0);
    m[0][0] = v.x;
    m[1][1] = v.y;
    return m;
}

mat4 rotate(float theta)
{
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    mat4 m = mat4(1.0);
    m[0][0] = cosTheta;
    m[0][1] = sinTheta;
    m[1][0] = -sinTheta;
    m[1][1] = cosTheta;
    return m;
}

void main()
{
    mat4 model = translate(position) *
                 translate(0.5f * size) *
                 rotate(rotation) *
                 translate(-0.5f * size) *
                 scale(size);

    TexCoords = mix(texInfo.xy, texInfo.zw, vertexPosition);
    Color = color;
    gl_Position = projection * model * vec4(vertexPosition, 0.0, 1.0);
}
