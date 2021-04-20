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

#include "avoidtrouble.h"
#include "ui_avoidtrouble.h"
#include <time.h>
#include <QString>

AvoidTrouble::AvoidTrouble(QWidget *parent) : QMainWindow(parent), ui(new Ui::AvoidTrouble)
{
    ui->setupUi(this);

    srand(time(NULL));

    /* Window initial settings */
    setWindowTitle(APP_NAME);
    setFixedWidth(APP_WIDTH);
    setFixedHeight(APP_HEIGHT);

    /* Initialize Safezone */
    //_safezone = new Safezone(0, (APP_HEIGHT/2) - (SAFE_ZONE_HEIGHT/2), SAFE_ZONE_WIDTH, SAFE_ZONE_HEIGHT);
    _safezone = new QRect(0, (APP_HEIGHT/2) - (SAFE_ZONE_HEIGHT/2), SAFE_ZONE_WIDTH, SAFE_ZONE_HEIGHT);

    /* Initialize Player */
    _player = new Player((SAFE_ZONE_WIDTH/2) - (PLAYER_WIDTH/2), (APP_HEIGHT/2) - (PLAYER_HEIGHT/2), PLAYER_SPEED);

    /* Initialize Victory door */
    _victoryDoor = new QRect(APP_WIDTH - VICTORY_DOOR_WIDTH, (APP_HEIGHT/2) - (VICTORY_DOOR_HEIGHT/2), VICTORY_DOOR_WIDTH, VICTORY_DOOR_HEIGHT);

    /* Initialize Obstacle array */
    _obstacles = new Obstacle[_obstacleSize];

    /* Main game timer */
    _gameTimer = new QTimer(this);
    connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
    _gameTimer->start(UPD_FREQ_MS);

    /* Stuck timer */
    _stuckTimer = new QTimer(this);
    connect(_stuckTimer, SIGNAL(timeout()), this, SLOT(resetStuckTimer()));
    _stuckTimer->setSingleShot(true);

    increaseStage();
}

AvoidTrouble::~AvoidTrouble()
{
    delete   ui;
    delete   _safezone;
    delete   _player;
    delete   _victoryDoor;
    delete[] _obstacles;
    delete   _gameTimer;
}

void AvoidTrouble::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::white));

    painter.fillRect(0, 0, APP_WIDTH, APP_HEIGHT, Qt::black);   /* Paint the background */

    if (_gameActive)
    {
        if (_player->getStuck())                                /* Paint the safe zone */
        {
            painter.fillRect(*_safezone, Qt::darkRed);
        }
        else
        {
            painter.fillRect(*_safezone, Qt::red);
        }

        painter.fillRect(*_victoryDoor,Qt::green);              /* Paint the victory door */
        _player->paint(painter);                                /* Paint the player */
        for (int i = 0; i < _obstacleSize; i++)                 /* Paint the obstacles */
            _obstacles[i].paint(painter);

        /* Paint stage number */
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(APP_WIDTH/2 - 45, 25, QString("Stage: ") + QString::number(_stage));

        if (_isPaused)
        {
            painter.setFont(QFont("Arial", 40, QFont::Bold));
            painter.drawText(APP_WIDTH/2 - 80, APP_HEIGHT/2, QString("PAUSE"));
        }
    }
    else
    {
        /* Paint Game Over */
        painter.setFont(QFont("Arial", 40, QFont::Bold));
        painter.drawText(APP_WIDTH/2 - 170, APP_HEIGHT/2, QString("GAME OVER!"));
        painter.setFont(QFont("Arial", 25, QFont::Bold));
        painter.drawText(APP_WIDTH/2 - 140,
                         APP_HEIGHT/2 + 50,
                         QString("You got to stage ") + QString::number(_stage));
    }
}

void AvoidTrouble::keyPressEvent(QKeyEvent* event)
{
    /* Update player key movement (key pressed) */
    _player->updateKeyStates(event->key(), true);

    /* Check key press */
    switch (event->key())
    {
    case Qt::Key_P:                     /* Pause */
        _isPaused = !_isPaused;
        break;
    case Qt::Key_R:                     /* Restart */
        _stage = _obstacleSize = 0;
        increaseStage();
        _gameActive = true;
        _isPaused = false;
        break;
    case Qt::Key_Escape:                /* Exit */
        close();
        break;
    default:
        break;
    }
}

void AvoidTrouble::keyReleaseEvent(QKeyEvent* event)
{
    /* Update player key movement (key released) */
    _player->updateKeyStates(event->key(), false);
}

void AvoidTrouble::increaseStage()
{
    _player->moveLeft(PLAYER_START_POS_X);
    _player->moveTop(PLAYER_START_POS_Y);
    _stage++;
    _obstacleSize++;
    delete[] _obstacles;
    _obstacles = new Obstacle[_obstacleSize];
    startStuckTimer();
}

void AvoidTrouble::startStuckTimer()
{
    _player->setStuck(true);
    _stuckTimer->start(PLAYER_STUCK);
}

void AvoidTrouble::update()
{
    if (_gameActive)
    {
        if (!_isPaused)
        {
            _gameActive = _player->update(_safezone, _obstacles, _obstacleSize);

            if (_player->checkInsideVictoryDoor(_victoryDoor))
                increaseStage();

            for (int i = 0; i < _obstacleSize; i++)
                _obstacles[i].update();
        }
        repaint();
    }
}

void AvoidTrouble::resetStuckTimer()
{
    _player->setStuck(false);
}
