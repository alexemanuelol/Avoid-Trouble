/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#include "avoidtrouble.h"
#include "ui_avoidtrouble.h"
#include <time.h>

AvoidTrouble::AvoidTrouble(QWidget *parent) : QMainWindow(parent), ui(new Ui::AvoidTrouble)
{
    ui->setupUi(this);

    srand(time(NULL));

    /* Window initial settings */
    setWindowTitle("Avoid Trouble");
    setFixedWidth(WINDOW_WIDTH);
    setFixedHeight(WINDOW_HEIGHT);

    /* Create the safe zone */
    _safezone = new Safezone(0, WINDOW_HEIGHT/2 - SAFE_ZONE_HEIGHT/2,
                             SAFE_ZONE_WIDTH, SAFE_ZONE_HEIGHT);

    /* Create the player */
    _player = new Player(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2,
                         WINDOW_HEIGHT/2-PLAYER_HEIGHT/2, PLAYER_VELOCITY);

    /* Create the victory door */
    _victoryDoor = new QRect(WINDOW_WIDTH - VICTORY_DOOR_WIDTH,
                             WINDOW_HEIGHT/2 - VICTORY_DOOR_HEIGHT/2,
                             VICTORY_DOOR_WIDTH,
                             VICTORY_DOOR_HEIGHT);

    /* Create the obstacle array */
    _obstacles = new Obstacle[_obstacleSize];

    /* Main game timer */
    _gameTimer = new QTimer(this);
    connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
    _gameTimer->start(16);
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

    /* Paint the background */
    painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

    if (_gameActive)
    {
        /* Paint the victory door */
        painter.fillRect(*_victoryDoor,Qt::green);

        /* Paint the obstacles */
        for (int i = 0; i < _obstacleSize; i++)
            _obstacles[i].paint(painter);

        /* Paint the safe zone */
        _safezone->paint(painter);

        /* Paint the player */
        _player->paint(painter);

        /* Paint stage number */
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(WINDOW_WIDTH/2 - 45, 25, QString("Stage: ") + QString::number(_stage));

        if (_isPaused)
        {
            painter.setFont(QFont("Arial", 40, QFont::Bold));
            painter.drawText(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2, QString("PAUSE"));
        }
    }
    else
    {
        /* Paint Game Over */
        painter.setFont(QFont("Arial", 40, QFont::Bold));
        painter.drawText(WINDOW_WIDTH/2 - 170, WINDOW_HEIGHT/2, QString("GAME OVER!"));
        painter.setFont(QFont("Arial", 25, QFont::Bold));
        painter.drawText(WINDOW_WIDTH/2 - 140, WINDOW_HEIGHT/2 + 50, QString("You got to stage ") + QString::number(_stage));
    }
}

void AvoidTrouble::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_P)              /* Pause */
    {
        _isPaused = !_isPaused;
    }
    else if (event->key() == Qt::Key_R)         /* Restart */
    {
        _stage = 0;
        _obstacleSize = 0;
        newStage();
        _gameActive = true;
        _isPaused = false;
    }
    else if (event->key() == Qt::Key_Escape)    /* Exit game */
    {
        this->close();
    }

    /* Check player movement, key press */
    switch (event->key())
    {
    case Qt::Key_W:
        _keyUp = true;
        break;

    case Qt::Key_A:
        _keyLeft = true;
        break;

    case Qt::Key_S:
        _keyDown = true;
        break;

    case Qt::Key_D:
        _keyRight = true;
        break;

    default:
        break;
    }
}

void AvoidTrouble::keyReleaseEvent(QKeyEvent* event)
{
    /* Check player movement, key release */
    switch (event->key())
    {
    case Qt::Key_W:
        _keyUp = false;
        break;

    case Qt::Key_A:
        _keyLeft = false;
        break;

    case Qt::Key_S:
        _keyDown = false;
        break;

    case Qt::Key_D:
        _keyRight = false;
        break;
    }
}

void AvoidTrouble::movePlayer()
{
    if (!_player->getSafeStuck())
    {
        if (_keyUp && _keyLeft)
        {
            if (_player->y() > 0)
                _player->moveTop(_player->y() - _player->getVel());
            if (_player->x() > 0)
                _player->moveLeft(_player->x() - _player->getVel());
        }
        else if (_keyUp && _keyRight)
        {
            if (_player->y() > 0)
                _player->moveTop(_player->y() - _player->getVel());
            if (_player->x() < (WINDOW_WIDTH - PLAYER_WIDTH))
                _player->moveLeft(_player->x() + _player->getVel());
        }
        else if (_keyDown && _keyLeft)
        {
            if (_player->y() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
                _player->moveTop(_player->y() + _player->getVel());
            if (_player->x() > 0)
                _player->moveLeft(_player->x() - _player->getVel());
        }
        else if (_keyDown && _keyRight)
        {
            if (_player->y() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
                _player->moveTop(_player->y() + _player->getVel());
            if (_player->x() < (WINDOW_WIDTH - PLAYER_WIDTH))
                _player->moveLeft(_player->x() + _player->getVel());
        }
        else if (_keyUp && _player->y() > 0)
            _player->moveTop(_player->y() - _player->getVel());
        else if (_keyLeft && _player->x() > 0)
            _player->moveLeft(_player->x() - _player->getVel());
        else if (_keyDown && _player->y() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
            _player->moveTop(_player->y() + _player->getVel());
        else if (_keyRight && _player->x() < (WINDOW_WIDTH - PLAYER_WIDTH))
            _player->moveLeft(_player->x() + _player->getVel());
    }
}

void AvoidTrouble::newStage()
{
    _player->moveLeft(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2);
    _player->moveTop(WINDOW_HEIGHT/2-PLAYER_HEIGHT/2);
    _stage++;
    _obstacleSize = _obstacleSize + 1;
    delete[] _obstacles;
    _obstacles = new Obstacle[_obstacleSize];
}

/* SLOTS FUNCTIONS */
/* Main game updater */
void AvoidTrouble::update()
{
    if (_gameActive)
    {
        if (!_isPaused)
        {
            _player->checkSafe(_safezone);
            _gameActive = _player->checkCollision(_obstacles, _obstacleSize);
            movePlayer();
            if (_player->checkVictoryDoor(_victoryDoor))
                newStage();
            _safezone->checkCollision(_obstacles, _obstacleSize);
            _safezone->setSafeStuckDelayTime(60);
            _safezone->updateSafeStuck(_player);

            for (int i = 0; i < _obstacleSize; i++)
                _obstacles[i].update();
        }
        repaint();
    }
}
