#include "assets/texture.h"

#include "logging.h"

Texture::Texture(const TextureDefinition& definition)
    : _textureId(0),
      _target(definition.target),
      _level(definition.level),
      _internalFormat(definition.internalFormat),
      _width(definition.width),
      _height(definition.height),
      _format(definition.format),
      _type(definition.type),
      _minFilter(definition.minFilter),
      _maxFilter(definition.maxFilter),
      _data(definition.data)
{
    //TODO: Check that _data contains _width * _height bytes taking into account _format

    glGenTextures(1, &_textureId);
    glBindTexture(_target, _textureId);

    glTexImage2D(_target,
                 _level,
                 _internalFormat,
                 _width,
                 _height,
                 0,
                 _format,
                 _type,
                 &_data[0]);

    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _maxFilter);

    glBindTexture(_target, 0);

    LOG_INFO("Texture Created from definition");
}

Texture::~Texture()
{
    LOG_INFO("Texture Destroyed");
    glDeleteTextures(1, &_textureId);
    _textureId = 0;
}

void Texture::bind()
{
    glBindTexture(_target, _textureId);
}

void Texture::unbind()
{
    glBindTexture(_target, 0);
}

GLuint Texture::textureId() const
{
    return _textureId;
}

GLuint Texture::width() const
{
    return _width;
}

GLuint Texture::height() const
{
    return _height;
}
