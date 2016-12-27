#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <string>
#include <vector>

#include "json.hpp"

#include "types.h"

class JsonUtil
{
public:
    bool load(const std::string& file, nlohmann::json& json);
    void loadOrThrow(const std::string& file, nlohmann::json& json);

    nlohmann::json get(const nlohmann::json& json, const std::vector<std::string>& keys);

    template<typename T>
    T get(const nlohmann::json& json, const std::vector<std::string>& keys, T defaultValue = T())
    {
        nlohmann::json object = get(json, keys);

        if(!object.is_null())
        {
            return object;
        }
        return defaultValue;
    }
};

#endif // JSONUTIL_H
