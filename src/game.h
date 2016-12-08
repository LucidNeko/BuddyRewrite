#ifndef GAME_H
#define GAME_H

#include "assets/assets.h"
#include "entitycollection.h"
#include "types.h"
#include "utilities/time/time.h"

class Scene;
class PhysicsSystem;
class SpriteRenderer;

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
    SceneHandle _currentScene;
    SceneHandle _nextScene;

    PhysicsSystem*  _physicsSystem;
    SpriteRenderer* _spriteRenderer;

    Assets _assets;
};

#endif // GAME_H
