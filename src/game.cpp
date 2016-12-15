#include "game.h"

#include "systemopengl.h"

#include <QGamepad>

#include "assets/assets.h"
#include "assets/scene.h"
#include "assets/shaderprogram.h"
#include "assets/entity.h"
#include "subsystems/physicssystem.h"
#include "subsystems/animationsystem.h"
#include "subsystems/scriptsystem.h"
#include "subsystems/spriterenderer.h"
#include "subsystems/inputsystem.h"

#include "logging.h"

Game::Game()
    : _inputSystem(new InputSystem())
{
}

Game::~Game()
{
    if(_currentScene)
    {
        _currentScene->onExit();
    }
}

bool Game::initialize()
{
    if (!gladLoadGL()) {
        LOG_FATAL("Failed to initialize OpenGL context");
        return false;
    }

    _assets = std::make_shared<Assets>();

    glClearColor(0.0, 0.0, 0.0, 1.0);

    _physicsSystem.reset(new PhysicsSystem());
    _animationSystem.reset(new AnimationSystem());
    _scriptSystem.reset(new ScriptSystem());
    _spriteRenderer.reset(new SpriteRenderer(_assets->get<ShaderProgram>("shaders/sprite")));

    queueScene(_assets->get<Scene>("scenes/test_scene"));
    _processNextScene();

    return true;
}

void Game::tick()
{
    GameTime time(16666667);

    _processSubSystems(time, _inputSystem->state());
    _processNextScene();
}

void Game::resize(I32 width, I32 height)
{
    LOG_INFO("%d, %d", width, height);
    glViewport(0, 0, width, height);
}

void Game::queueScene(SceneHandle scene)
{
    _nextScene = scene;
}

InputSystem* Game::inputSystem() const
{
    return _inputSystem.get();
}

void Game::_processSubSystems(GameTime time, const Input& input)
{
    std::vector<EntityHandle> entities = _currentScene->getAll();

    _physicsSystem->update(time, entities);

    _animationSystem->update(time, entities);

    _scriptSystem->update(time, input, entities);

    _spriteRenderer->render(entities);
    _spriteRenderer->flush();
}

void Game::_processNextScene()
{
//  queueScene(_assets->get<Scene>("scenes/test_scene"));

    if(!_nextScene) { return; }

    if(_currentScene)
    {
        _currentScene->onExit();
    }

    _currentScene = _nextScene;
    _nextScene.reset();

    if(_currentScene)
    {
        _currentScene->onEnter();
    }

    LOG_INFO("Free Unreferenced Resources");
    _assets->freeUnreferencedResources();
}
