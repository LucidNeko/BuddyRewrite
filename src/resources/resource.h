#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource
{
public:
    enum Type
    {
        TYPE_NULL,
        TYPE_TEXTURE,
        TYPE_SHADER_PROGRAM,
        TYPE_SPRITE_SHEET,
        TYPE_JSON_FILE
    };

public:
    Resource(std::string name);
    virtual ~Resource();

    /* Subclasses must implement: static Resource::Type type(); */

    std::string name() const;

    virtual bool load() = 0;
    virtual void destroy() = 0;

private:
    std::string _name;
};

#endif // RESOURCE_H
