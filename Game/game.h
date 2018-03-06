#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include "defines.h"
#include "player.h"
#include "safezone.h"
#include "obstacle.h"

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void movePlayer();
    void newStage();

private slots:
    void update();

private:
    Ui::Game *ui;
    QTimer* _gameTimer;

    Player*             _player;
    Obstacle*           _obstacles;
    Safezone*           _safezone;
    QRect*              _victoryDoor;

    bool _gameActive    = true;
    bool _isSafe        = true;
    bool _isPaused      = false;

    int _stage          = 1;
    int _obstacleSize   = 1;

    bool _keyUp         = false;
    bool _keyLeft       = false;
    bool _keyDown       = false;
    bool _keyRight      = false;
};

#endif // GAME_H
