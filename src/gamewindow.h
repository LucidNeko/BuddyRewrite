#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

 // Must be included before QOpenGLWidget
#include "systemopengl.h"

#include <QObject>
#include <QEvent>
#include <QOpenGLWidget>
#include <QCloseEvent>

#include "types.h"

class GameWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();

    I32 exec();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void closeEvent(QCloseEvent* event) override;

private:
    class Game* _game;
    bool _closing;
};

#endif // GAMEWINDOW_H
