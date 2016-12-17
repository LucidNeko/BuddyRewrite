#ifndef GAME_H
#define GAME_H

#include <memory>

#include "entitycollection.h"
#include "types.h"
#include "gametime.h"

class Game
{
public:
    Game();
    ~Game();

    bool initialize();
    void tick();
    void resize(I32 width, I32 height);

    void queueScene(SceneHandle scene);

private:
    void _processSubSystems(GameTime time, const class Input& input);
    void _processNextScene();

private:
    AssetsHandle _assets;

    SceneHandle _currentScene;
    SceneHandle _nextScene;

    std::shared_ptr<class InputSystem>   _inputSystem;

    std::shared_ptr<class PhysicsSystem>   _physicsSystem;
    std::shared_ptr<class AnimationSystem> _animationSystem;
    std::shared_ptr<class ScriptSystem>    _scriptSystem;
    std::shared_ptr<class SpriteRenderer>  _spriteRenderer;
};

#endif // GAME_H
