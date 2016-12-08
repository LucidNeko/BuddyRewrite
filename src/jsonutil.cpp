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
