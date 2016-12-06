#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include "systemopengl.h"

#include "resources/resource.h"

class ShaderProgram : public Resource
{
public:
    ShaderProgram(std::string name);
    ~ShaderProgram();

    bool load() override;
    void destroy() override;

    void reload();

    void bind();
    void unbind();

    GLuint id() const;

    GLint getUniformLocation(const char* name);

private:
    std::string _loadShaderSource(std::string filepath);
    GLuint _compileShader(GLenum type, std::string shaderSource);

public:
    static Resource::Type type() { return TYPE_SHADER_PROGRAM; }

private:
    GLuint _programId;
};

#endif // SHADERPROGRAM_H
