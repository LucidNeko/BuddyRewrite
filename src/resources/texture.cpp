#include "texture.h"

#include <string>

#include <QImage>

#include "utilities/io/io.h"
#include "logging.h"

Texture::Texture(std::string name)
    : Resource(name),
      _textureId(0),
      _width(0),
      _height(0)
{
}

Texture::~Texture()
{
}

bool Texture::load()
{
    std::string fullpath(IO::assetDirectory() + "data/textures/" + Resource::name());
    QImage image(fullpath.c_str());

    if(image.isNull())
    {
        LOG_INFO("Loading texture \"%s\" from \"%s\" failed.", Resource::name().c_str(), fullpath.c_str());
        return false;
    }

    image = image.convertToFormat(QImage::Format_RGBA8888);

    _width = image.width();
    _height = image.height();

    glGenTextures(1, &_textureId);

    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 _width,
                 _height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::destroy()
{
    glDeleteTextures(1, &_textureId);
    _textureId = 0;
}

GLuint Texture::id() const
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
void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
