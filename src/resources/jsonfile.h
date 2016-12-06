#ifndef JSONFILE_H
#define JSONFILE_H

#include <string>

#include "json.hpp"

#include "types.h"
#include "resources/resource.h"

class JsonFile : public Resource
{
public:
    JsonFile(std::string name);
    ~JsonFile();

    bool load() override;
    void destroy() override;

    const nlohmann::json& json() { return _json; }

public:
    static Resource::Type type() { return TYPE_JSON_FILE; }

private:
    nlohmann::json _json;
};

#endif // JSONFILE_H
