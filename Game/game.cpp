#include "game.h"
#include "ui_game.h"

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
    _safezone = new Safezone(0, WINDOW_HEIGHT/2 - SAFE_ZONE_HEIGHT/2,
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
    delete _safezone;
    delete[] _obstacles;
}

void Game::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    /* Paint the background */
    painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

    if (_gameActive)
    {
        /* Paint the obstacles */
        for (int i = 0; i < _obstacleSize; i++)
            _obstacles[i].paint(painter);

        /* Paint the victory door */
        painter.fillRect(*_victoryDoor,Qt::green);

        /* Paint the safe zone */
        _safezone->paint(painter);

        /* Paint the player */
        _player->paint(painter);

        /* Paint stage number */
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        QPen pen(Qt::white);
        painter.setPen(pen);
        painter.drawText(WINDOW_WIDTH/2 - 65, 25, QString("Stage: "));
        painter.drawText(WINDOW_WIDTH/2 + 20, 25, QString::number(_stage));

        if (_isPaused)
        {
            painter.setFont(QFont("Arial", 40, QFont::Bold));
            QPen pen(Qt::white);
            painter.setPen(pen);
            painter.drawText(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2, QString("PAUSE"));
        }
    }
    else
    {
        /* Paint Game Over */
        painter.setFont(QFont("Arial", 40, QFont::Bold));
        QPen pen(Qt::white);
        painter.setPen(pen);
        painter.drawText(WINDOW_WIDTH/2 - 170, WINDOW_HEIGHT/2, QString("GAME OVER!"));
    }
}

void Game::keyPressEvent(QKeyEvent* event)
{
    /* Restart */
    if (event->key() == Qt::Key_R)
    {
        _stage = 0;
        _obstacleSize = 0;
        newStage();
        _gameActive = true;
    }

    /* Pause */
    if (event->key() == Qt::Key_P)
    {
        _isPaused = !_isPaused;
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

void Game::keyReleaseEvent(QKeyEvent* event)
{
    /* Check player movement, key release */
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
}

void Game::newStage()
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
void Game::update()
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

            for (int i = 0; i < _obstacleSize; i++)
                _obstacles[i].update();
        }
        repaint();
    }
}
