#include "resources/shaderprogram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "utilities/io/io.h"
#include "logging.h"

ShaderProgram::ShaderProgram(std::string name)
    : Resource(name),
      _programId(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::load()
{
    std::string fullpath(IO::assetDirectory() + "data/shaders/" + Resource::name());

    std::string vertPath(fullpath + ".vert");
    std::string fragPath(fullpath + ".frag");

    std::string vertSource = _loadShaderSource(vertPath);
    std::string fragSource = _loadShaderSource(fragPath);

    GLuint vertShader = _compileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fragShader = _compileShader(GL_FRAGMENT_SHADER, fragSource);

    if(vertShader == 0 || fragShader == 0)
    {
        LOG_ERROR("Failed to load shader program \"%s\"", Resource::name().c_str());
        return false;
    }

    _programId = glCreateProgram();

    glAttachShader(_programId, vertShader);
    glAttachShader(_programId, fragShader);

    glLinkProgram(_programId);

    GLint isLinked = 0;
    glGetProgramiv(_programId, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_programId, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(_programId);
        _programId = 0;

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        LOG_ERROR("Failed to link shader program \"%s\"", &infoLog[0]);

        return false;
    }

    glDetachShader(_programId, vertShader);
    glDetachShader(_programId, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return true;
}

void ShaderProgram::destroy()
{
    glDeleteProgram(_programId);
    _programId = 0;
}

void ShaderProgram::reload()
{
    destroy();
    load();
}

void ShaderProgram::bind()
{
    glUseProgram(_programId);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

GLuint ShaderProgram::id() const
{
    return _programId;
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(_programId, name);
}

std::string ShaderProgram::_loadShaderSource(std::string filepath)
{
    std::string line;
    std::ifstream file(filepath);

    std::ostringstream shaderSource;

    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            shaderSource << line << '\n';
        }
        file.close();

        return shaderSource.str();
    }
    else
    {
        LOG_ERROR("Failed opening file \"%s\"", filepath.c_str());
        return "";
    }
}

GLuint ShaderProgram::_compileShader(GLenum type, std::string shaderSource)
{
    GLuint shader = glCreateShader(type);

    const GLchar* source = (const GLchar*)shaderSource.c_str();
    glShaderSource(shader, 1, &source, 0);

    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        LOG_ERROR("Failed to compile %d shader: %s", type, &infoLog[0]);

        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}
