/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
