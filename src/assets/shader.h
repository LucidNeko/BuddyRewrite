#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "systemopengl.h"

#include "types.h"
#include "assets/asset.h"

class Shader : public Asset
{
public:
    static ShaderHandle load(const std::string& filepath, class Assets* loader);

public:
    ~Shader();

    bool reload();

    void bind();
    void unbind();

    GLuint shaderId() const;

    GLint getUniformLocation(const char* name);

private:
    Shader();

    std::string loadShaderSource(std::string filepath);
    GLuint compileShader(GLenum type, std::string shaderSource);

private:
    GLuint _programId;

    std::string _vertextPath;
    std::string _fragmentPath;
};

#endif // SHADER_H
