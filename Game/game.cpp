#include "game.h"
#include "ui_game.h"

#include <iostream>

Game::Game(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game)
{
    ui->setupUi(this);

    srand(time(NULL));

    /* Set the Game window to a fixed size */
    setFixedWidth(WINDOW_WIDTH);
    setFixedHeight(WINDOW_HEIGHT);

    /* Create the victory door */
    _victoryDoor = new QRect(WINDOW_WIDTH - VICTORY_DOOR_WIDTH,
                             WINDOW_HEIGHT/2 - VICTORY_DOOR_HEIGHT/2,
                             VICTORY_DOOR_WIDTH,
                             VICTORY_DOOR_HEIGHT);

    /* Create the safe zone */
    _safeZone = new QRect(0, WINDOW_HEIGHT/2 - SAFE_ZONE_HEIGHT/2,
                          SAFE_ZONE_WIDTH, SAFE_ZONE_HEIGHT);

    /* Create the obstacle array */
    _obstacles = new Obstacle[_obstacleSize];

    /* Create the player */
    _player = new Player(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2,
                         WINDOW_HEIGHT/2-PLAYER_HEIGHT/2, PLAYER_VELOCITY);

    /* Main game timer */
    _gameTimer = new QTimer(this);
    connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
    _gameTimer->start(16);
}

Game::~Game()
{
    delete ui;
    delete _player;
    delete _gameTimer;
}

void Game::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (_gameActive)
    {
        /* Paint the background */
        painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

        /* Paint the obstacles */
        for (int i = 0; i < _obstacleSize; i++)
            _obstacles[i].paint(painter);

        /* Paint the victory door */
        painter.fillRect(*_victoryDoor,Qt::green);

        /* Paint the safe zone */
        painter.fillRect(*_safeZone, Qt::gray);

        /* Paint the player */
        _player->paint(painter);

        /* Paint stage number */
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        QPen pen(Qt::white);
        painter.setPen(pen);
        painter.drawText(WINDOW_WIDTH/2 - 65, 25, QString("Stage: "));
        painter.drawText(WINDOW_WIDTH/2 + 20, 25, QString::number(_stage));
    }
    else
    {
        /* Paint the background */
        painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

        /* Paint Game Over */
        painter.setFont(QFont("Arial", 40, QFont::Bold));
        QPen pen(Qt::white);
        painter.setPen(pen);
        painter.drawText(WINDOW_WIDTH/2 - 170, WINDOW_HEIGHT/2, QString("GAME OVER!"));
    }
}

void Game::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_R)
    {
        // Restart
        _stage = 1;
        _obstacleSize = 0;
        newStage();
        _player->moveLeft(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2);
        _player->moveTop(WINDOW_HEIGHT/2-PLAYER_HEIGHT/2);
        _gameActive = true;
    }

    if (event->key() == Qt::Key_P)
    {
        // Pause
    }

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
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat())
    {
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
}

void Game::movePlayer()
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

    if (_victoryDoor->contains(QPoint(_player->x() + PLAYER_WIDTH/2, _player->y() + PLAYER_HEIGHT/2)))
    {
        _player->moveLeft(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2);
        _player->moveTop(WINDOW_HEIGHT/2-PLAYER_HEIGHT/2);
        _stage++;
        newStage();
    }
}

void Game::hitCheck()
{
    /* Player collision detection */
    for (int i = 0; i < _obstacleSize; i++)
    {
        if (_player->contains(_obstacles[i].topLeft()) ||
            _player->contains(_obstacles[i].topRight()) ||
            _player->contains(_obstacles[i].bottomLeft()) ||
            _player->contains(_obstacles[i].bottomRight()) ||
            _player->contains(_obstacles[i].center()))
            _gameActive = false;
    }
}

void Game::newStage()
{
    _obstacleSize = _obstacleSize + 1;
    delete[] _obstacles;
    _obstacles = new Obstacle[_obstacleSize];
}

/* SLOTS FUNCTIONS */
/* Main game updater */
void Game::update()
{
    if (_gameActive)
    {
        hitCheck();
        movePlayer();

        for (int i = 0; i < _obstacleSize; i++)
            _obstacles[i].update();

        repaint();
    }
}
