#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <vector>

#include "gametime.h"
#include "types.h"

class ScriptSystem
{
public:
    ScriptSystem();
    ~ScriptSystem();

    void update(GameTime time, const std::vector<EntityHandle>& entities);

private:
    void _update(GameTime time, EntityHandle entity);
    void _updateScript(GameTime time, std::shared_ptr<class Script> script);
};

#endif // SCRIPTSYSTEM_H
