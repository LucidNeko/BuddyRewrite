#include "jsonutil.h"

#include <fstream>
#include <stdexcept>


bool JsonUtil::load(const std::string& file, nlohmann::json& json)
{
    std::ifstream ifs(file);

    if(ifs.good())
    {
        ifs >> json;
        return true;
    }

    return false;
}

void JsonUtil::loadOrThrow(const std::string& file, nlohmann::json& json)
{
    if(!load(file, json))
    {
        std::string message("Failed to load: " + file);
        throw std::invalid_argument(message);
    }
}

nlohmann::json JsonUtil::get(const nlohmann::json& json, const std::vector<std::string>& keys)
{
    if(keys.empty()) { return nlohmann::json(); }

    nlohmann::json object = json;
    for(size_t i = 0; i < keys.size(); i++)
    {
        auto it = object.find(keys.at(i));
        if(it == object.end())
        {
            return nlohmann::json();
        }
        object = *it;
    }
    return object;
}
