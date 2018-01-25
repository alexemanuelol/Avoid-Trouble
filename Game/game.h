#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include "defines.h"
#include "player.h"

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
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void movePlayer();

private slots:
    void update();

private:
    Ui::Game *ui;

    bool _keyUp = false;
    bool _keyLeft = false;
    bool _keyDown = false;
    bool _keyRight = false;

    QTimer* _gameTimer;

    Player* _player;

    QRect* _victoryDoor;
    QRect* _safeZone;
};

#endif // GAME_H
