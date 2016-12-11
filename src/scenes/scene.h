#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "assets/asset.h"
#include "types.h"
#include "uuid.h"

class Scene : public Asset
{
public:
    static SceneHandle load(const std::string& filepath, AssetsHandle loader);

public:
    Scene(AssetsHandle assets);
    virtual ~Scene();

    void add(EntityHandle entity);

    bool remove(EntityHandle entity);
    bool remove(Uuid entityId);
    void removeAll();

    EntityHandle get(Uuid entityId);

    std::vector<EntityHandle> getAll();

public:
    virtual void onEnter();
    virtual void onExit();

protected:
    AssetsHandle _assets;
    std::unordered_map<Uuid, EntityHandle> _entities;
};

#endif // SCENE_H
