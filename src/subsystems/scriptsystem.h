#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <vector>

#include "gametime.h"
#include "types.h"

class Input;

class ScriptSystem
{
public:
    ScriptSystem();
    ~ScriptSystem();

    void update(GameTime time, const Input& input, const std::vector<EntityHandle>& entities);

private:
    void _update(GameTime time, const Input& input, EntityHandle entity);
    void _updateScript(GameTime time, const Input& input, std::shared_ptr<class Script> script);
};

#endif // SCRIPTSYSTEM_H
