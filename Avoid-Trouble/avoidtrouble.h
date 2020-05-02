/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#ifndef AVOIDTROUBLE_H
#define AVOIDTROUBLE_H

#include <QMainWindow>
#include <QTimer>
#include <QRect>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>

#include "defines.h"
#include "player.h"
#include "safezone.h"
#include "obstacle.h"

namespace Ui {
class AvoidTrouble;
}

class AvoidTrouble : public QMainWindow
{
    Q_OBJECT

public:
    explicit AvoidTrouble(QWidget *parent = 0);
    ~AvoidTrouble();

    void    paintEvent(QPaintEvent * event);
    void    keyPressEvent(QKeyEvent* event);
    void    keyReleaseEvent(QKeyEvent* event);

    void    movePlayer();
    void    newStage();

private slots:
    void    update();

private:
    Ui::AvoidTrouble*   ui;
    Safezone*           _safezone;
    Player*             _player;
    QRect*              _victoryDoor;
    Obstacle*           _obstacles;
    QTimer*             _gameTimer;

    bool _gameActive    = true;
    bool _isSafe        = true;
    bool _isPaused      = false;

    int _stage          = 1;
    int _obstacleSize   = INITIAL_OBSTACLES_AMOUNT;

    bool _keyUp         = false;
    bool _keyLeft       = false;
    bool _keyDown       = false;
    bool _keyRight      = false;
};

#endif // AVOIDTROUBLE_H
