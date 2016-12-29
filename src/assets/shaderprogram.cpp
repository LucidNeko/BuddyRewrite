#include "assets/shaderprogram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "logging.h"

ShaderProgram::ShaderProgram(const ShaderProgramDefinition& definition)
    : Asset(),
      _programId(0),
      _vertextPath(definition.vertextPath),
      _fragmentPath(definition.fragmentPath)
{
    reload();
    LOG_INFO("ShaderProgram Created");
}

ShaderProgram::~ShaderProgram()
{
    LOG_INFO("ShaderProgram Destroyed");
    glDeleteProgram(_programId);
    _programId = 0;
}

bool ShaderProgram::isValid()
{
    return _programId != 0;
}

bool ShaderProgram::reload()
{
    if(_programId != 0)
    {
        glDeleteProgram(_programId);
        _programId = 0;
    }

    std::string vertSource = loadShaderSource(_vertextPath);
    std::string fragSource = loadShaderSource(_fragmentPath);

    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragSource);

    if(vertShader == 0 || fragShader == 0)
    {
        LOG_ERROR("Failed to load shader program \"%s\" \"%s\"", _vertextPath.c_str(), _fragmentPath.c_str());
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

void ShaderProgram::bind()
{
    glUseProgram(_programId);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

GLuint ShaderProgram::shaderId() const
{
    return _programId;
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(_programId, name);
}

std::string ShaderProgram::loadShaderSource(std::string filepath)
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

GLuint ShaderProgram::compileShader(GLenum type, std::string shaderSource)
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
