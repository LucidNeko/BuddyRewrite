#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <string>

#include "json.hpp"

class JsonUtil
{
public:
    bool load(const std::string& file, nlohmann::json& json);
    void loadOrThrow(const std::string& file, nlohmann::json& json);
};

#endif // JSONUTIL_H
