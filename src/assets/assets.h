#ifndef ASSETS_H
#define ASSETS_H

#include <functional>
#include <memory>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

#include "types.h"

class Assets : public std::enable_shared_from_this<Assets>
{
public:
    static std::string assetDirPath();

private:
    typedef std::function<AssetHandle(const std::string&, AssetsHandle)> LoaderFunction;
    typedef std::unordered_map<std::string, AssetHandle> AssetCollection;

public:
    Assets();
    ~Assets();

    void setAssetDirectory(const std::string& directory);
    const std::string& assetDirectory() const;

    template<typename T>
    void setLoader(LoaderFunction loader)
    {
        setLoader(std::type_index(typeid(T)), loader);
    }

    template<typename T>
    bool load(const std::string& name)
    {
        return load(std::type_index(typeid(T)), name);
    }

    template<typename T>
    bool isLoaded(const std::string& name)
    {
        return isLoaded(std::type_index(typeid(T)), name);
    }

    template<typename T>
    std::shared_ptr<T> get(const std::string& name)
    {
        return std::dynamic_pointer_cast<T>(get(std::type_index(typeid(T)), name));
    }

    void freeUnreferencedResources();

private:
    void setLoader(std::type_index type, LoaderFunction loader);
    bool load(std::type_index type, const std::string& name);
    bool isLoaded(std::type_index type, const std::string& name);
    AssetHandle get(std::type_index type, const std::string& name);

private:
    std::string _assetDirectory;
    std::unordered_map<std::type_index, LoaderFunction> _loaders;
    std::unordered_map<std::type_index, AssetCollection> _assets;
    std::unordered_set<std::type_index> _doNotCache;
};

#endif // ASSETS_H
