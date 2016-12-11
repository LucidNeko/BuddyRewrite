#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "assets/asset.h"
#include "types.h"

class Scene : public Asset
{
public:
    static SceneHandle load(const std::string& filepath, AssetsHandle loader);

public:
    Scene(AssetsHandle assets);
    virtual ~Scene();

    void add(EntityHandle entity);

    bool remove(EntityHandle entity);
    bool remove(U64 entityId);
    void removeAll();

    EntityHandle get(U64 entityId);

    std::vector<EntityHandle> getAll();

public:
    virtual void onEnter();
    virtual void onExit();

protected:
    AssetsHandle _assets;
    std::unordered_map<U64, EntityHandle> _entities;
};

#endif // SCENE_H
