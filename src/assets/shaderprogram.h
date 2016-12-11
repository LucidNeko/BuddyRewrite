#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include "systemopengl.h"

#include "types.h"
#include "assets/asset.h"

class ShaderProgram : public Asset
{
public:
    static ShaderProgramHandle load(const std::string& filepath, AssetsHandle loader);

public:
    ~ShaderProgram();

    bool reload();

    void bind();
    void unbind();

    GLuint shaderId() const;

    GLint getUniformLocation(const char* name);

private:
    ShaderProgram();

    std::string loadShaderSource(std::string filepath);
    GLuint compileShader(GLenum type, std::string shaderSource);

private:
    GLuint _programId;

    std::string _vertextPath;
    std::string _fragmentPath;
};

#endif // SHADERPROGRAM_H
