#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <string>
#include <vector>

#include "systemopengl.h"

#include "types.h"
#include "assets/asset.h"

class Texture2 : public Asset
{
public:
    static Texture2Handle load(const std::string& filepath, class Assets* loader);

public:
    ~Texture2();

    void bind();
    void unbind();

    GLuint textureId() const;
    GLuint width() const;
    GLuint height() const;

private:
    Texture2();

    bool isCreated();
    void create();

private:
    GLuint _textureId;

    GLenum  _target;
    GLint   _level;
    GLint   _internalFormat;
    GLsizei _width;
    GLsizei _height;
    GLint   _border;
    GLenum  _format;
    GLenum  _type;

    std::vector<GLubyte> _data;

    GLint _minFilter;
    GLint _maxFilter;
};

#endif // TEXTURE_H
