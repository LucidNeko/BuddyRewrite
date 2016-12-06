#include "resources/jsonfile.h"

#include <fstream>
#include <sstream>

#include "utilities/io/io.h"


JsonFile::JsonFile(std::string name)
    : Resource(IO::assetDirectory() + name)
{
}

JsonFile::~JsonFile()
{
}

bool JsonFile::load()
{
    std::ifstream ifs(Resource::name(), std::ifstream::in);
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    if(ifs.good())
    {
        //TODO: noexcept
        _json = nlohmann::json::parse(buffer.str().c_str());
        return true;
    }

    return false;
}

void JsonFile::destroy()
{

}
