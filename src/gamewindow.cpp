#include "gamewindow.h"

#include <cstdlib>

#include "types.h"
#include "logging.h"
#include "game.h"

#include "assets/spritesheet.h"
#include "assets/assets.h"
#include "assets/asset.h"

GameWindow::GameWindow(QWidget *parent)
    : QOpenGLWidget(parent),
      _game(new Game())
{
    this->setMouseTracking(true);

    // TODO: This is a hack to make floating in i3-wm
    Qt::WindowFlags flags = this->windowFlags();
    flags |= Qt::Dialog;
    this->setWindowFlags(flags);
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
