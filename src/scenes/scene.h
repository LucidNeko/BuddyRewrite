#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <vector>

#include "types.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();

    void add(EntityHandle entity);

    bool remove(EntityHandle entity);
    bool remove(U64 entityId);
    void removeAll();

    EntityHandle get(U64 entityId);

    std::vector<EntityHandle> getAll();

public:
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

protected:
    std::unordered_map<U64, EntityHandle> _entities;
};

#endif // SCENE_H
