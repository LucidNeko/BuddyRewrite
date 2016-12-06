#include "assets/texture2.h"

#include "logging.h"

Texture2::Texture2()
    : _textureId(0),
      _target(GL_TEXTURE_2D),
      _level(0),
      _internalFormat(GL_RGBA8),
      _width(0),
      _height(0),
      _border(0),
      _format(GL_RGBA),
      _type(GL_UNSIGNED_BYTE),
      _data(0),
      _minFilter(GL_NEAREST),
      _maxFilter(GL_NEAREST)
{
}

Texture2::~Texture2()
{
    LOG_INFO("Texture2 Destroyed");
    glDeleteTextures(1, &_textureId);
    _textureId = 0;
}

bool Texture2::isCreated()
{
    return _textureId != 0;
}

void Texture2::create()
{
    //TODO: Check that _data contains _width * _height bytes taking into account _format

    if(isCreated())
    {
        LOG_INFO("Recreating Texture");
        glDeleteTextures(1, &_textureId);
        _textureId = 0;
    }

    glGenTextures(1, &_textureId);
    glBindTexture(_target, _textureId);

    glTexImage2D(_target,
                 _level,
                 _internalFormat,
                 _width,
                 _height,
                 _border,
                 _format,
                 _type,
                 &_data[0]);

    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _maxFilter);

    glBindTexture(_target, 0);
}

void Texture2::bind()
{
    glBindTexture(_target, _textureId);
}

void Texture2::unbind()
{
    glBindTexture(_target, 0);
}

GLuint Texture2::textureId() const
{
    return _textureId;
}

GLuint Texture2::width() const
{
    return _width;
}

GLuint Texture2::height() const
{
    return _height;
}
