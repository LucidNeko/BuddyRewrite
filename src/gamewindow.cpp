#include "gamewindow.h"

#include <cstdlib>

#include "types.h"
#include "logging.h"
#include "game.h"

#include "services.h"
#include "input.h"

#include "assets/spritesheet2.h"
#include "assets/assets.h"
#include "assets/asset.h"
#include "utilities/io/io.h"

GameWindow::GameWindow(QWidget *parent)
    : QOpenGLWidget(parent),
      _game(new Game())
{
    //TODO: Probably unsafe if installEventFilter is meant to take ownership
//    this->installEventFilter(Services::get<Input>().get());
    this->installEventFilter(Services::get<Input>());
}

GameWindow::~GameWindow()
{
    makeCurrent();

    delete _game;

    doneCurrent();
}

void GameWindow::initializeGL()
{
    LOG_INFO("initializeGL");

    bool success = _game->initialize();
    if(!success)
    {
        LOG_FATAL("Failed to init");
        std::exit(EXIT_FAILURE); //TODO: close window instead so main can exit normally
    }

    Assets& a = *Services::get<Assets>();
    a.setAssetDirectory(IO::assetDirectory());
    a.load<SpriteSheet>("spritesheets/characters.json");
    AssetHandle ass = a.get<SpriteSheet>("spritesheets/characters.json");
    a.freeUnreferencedResources();
}

void GameWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _game->tick();

    update();
}

void GameWindow::resizeGL(int w, int h)
{
    LOG_INFO("resizeGL(%d, %d)", w, h);

    _game->resize((I32)w, (I32)h);
}
