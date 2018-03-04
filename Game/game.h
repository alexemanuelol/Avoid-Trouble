#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include "defines.h"
#include "player.h"
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
    void hitCheck();
    void newStage();

private slots:
    void update();

private:
    Ui::Game *ui;

    int _stage = 1;
    bool _gameActive = true;
    int _obstacleSize = 1;

    bool _keyUp = false;
    bool _keyLeft = false;
    bool _keyDown = false;
    bool _keyRight = false;

    QTimer* _gameTimer;

    Player* _player;

    Obstacle* _obstacles;

    QRect* _victoryDoor;
    QRect* _safeZone;
};

#endif // GAME_H
