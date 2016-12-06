#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

 // Must be included before QOpenGLWidget
#include "systemopengl.h"

#include <QObject>
#include <QEvent>
#include <QOpenGLWidget>

class GameWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    class Game* _game;
};

#endif // GAMEWINDOW_H
