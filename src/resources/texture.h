#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "systemopengl.h"

#include "resources/resource.h"

class Texture : public Resource
{
public:
    Texture(std::string name);
    ~Texture();

    bool load() override;
    void destroy() override;

    void bind();
    void unbind();

    GLuint id() const;
    GLuint width() const;
    GLuint height() const;

public:
    static Resource::Type type() { return TYPE_TEXTURE; }

private:
    GLuint _textureId;
    GLuint _width;
    GLuint _height;

};

#endif // TEXTURE_H
