#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game)
{
    ui->setupUi(this);

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

    /* Paint the background */
    painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

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
    painter.drawText(WINDOW_WIDTH/2 + 20, 25, QString::number(stage));
}

void Game::mouseMoveEvent(QMouseEvent* event)
{

}

void Game::keyPressEvent(QKeyEvent* event)
{
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
        if (_player->getY() > 0)
            _player->setY(_player->getY() - _player->getVel());
        if (_player->getX() > 0)
            _player->setX(_player->getX() - _player->getVel());
    }
    else if (_keyUp && _keyRight)
    {
        if (_player->getY() > 0)
            _player->setY(_player->getY() - _player->getVel());
        if (_player->getX() < (WINDOW_WIDTH - PLAYER_WIDTH))
            _player->setX(_player->getX() + _player->getVel());
    }
    else if (_keyDown && _keyLeft)
    {
        if (_player->getY() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
            _player->setY(_player->getY() + _player->getVel());
        if (_player->getX() > 0)
            _player->setX(_player->getX() - _player->getVel());
    }
    else if (_keyDown && _keyRight)
    {
        if (_player->getY() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
            _player->setY(_player->getY() + _player->getVel());
        if (_player->getX() < (WINDOW_WIDTH - PLAYER_WIDTH))
            _player->setX(_player->getX() + _player->getVel());
    }
    else if (_keyUp && _player->getY() > 0)
        _player->setY(_player->getY() - _player->getVel());
    else if (_keyLeft && _player->getX() > 0)
        _player->setX(_player->getX() - _player->getVel());
    else if (_keyDown && _player->getY() < (WINDOW_HEIGHT - PLAYER_HEIGHT))
        _player->setY(_player->getY() + _player->getVel());
    else if (_keyRight && _player->getX() < (WINDOW_WIDTH - PLAYER_WIDTH))
        _player->setX(_player->getX() + _player->getVel());

    if (_victoryDoor->contains(QPoint(_player->getX() + PLAYER_WIDTH/2, _player->getY() + PLAYER_HEIGHT/2)))
    {
        _player->setX(SAFE_ZONE_WIDTH/2-PLAYER_WIDTH/2);
        _player->setY(WINDOW_HEIGHT/2-PLAYER_HEIGHT/2);
        stage++;
    }
}

/* SLOTS FUNCTIONS */
/* Main game updater */
void Game::update()
{
    movePlayer();
    repaint();
}
