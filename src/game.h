#ifndef GAME_H
#define GAME_H

#include "entitycollection.h"
#include "types.h"
#include "utilities/time/time.h"

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
    void _processSubSystems(Time time);
    void _processNextScene();

private:
    AssetsHandle _assets;

    SceneHandle _currentScene;
    SceneHandle _nextScene;

    class PhysicsSystem* _physicsSystem;
    class AnimationSystem* _animationSystem;
    class SpriteRenderer* _spriteRenderer;
};

#endif // GAME_H
