#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <string>
#include <vector>

#include "systemopengl.h"

#include "types.h"
#include "assets/asset.h"

struct TextureDefinition
{
public:
    GLenum target = GL_TEXTURE_2D;
    GLint level = 0;
    GLint internalFormat = GL_RGBA8;
    GLsizei width = 0;
    GLsizei height = 0;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;
    GLint minFilter = GL_NEAREST;
    GLint maxFilter = GL_NEAREST;
    std::vector<GLubyte> data;
};

class Texture : public Asset
{
public:
    static TextureHandle load(const std::string& filepath, AssetsHandle loader);

public:
    Texture(const TextureDefinition& definition);
    ~Texture();

    void bind();
    void unbind();

    GLuint textureId() const;
    GLuint width() const;
    GLuint height() const;

private:
    GLuint _textureId;

    GLenum  _target;
    GLint   _level;
    GLint   _internalFormat;
    GLsizei _width;
    GLsizei _height;
    GLenum  _format;
    GLenum  _type;
    GLint   _minFilter;
    GLint   _maxFilter;

    std::vector<GLubyte> _data;
};

#endif // TEXTURE_H
