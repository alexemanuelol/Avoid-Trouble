#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game)
{
    ui->setupUi(this);

    /* Set the Game window to a fixed size */
    setFixedWidth(WINDOW_WIDTH);
    setFixedHeight(WINDOW_HEIGHT);

    /* Create the player */
    _player = new Player(100, 290, 10);

    /* Main game timer */
    _gameTimer = new QTimer(this);
    connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
    _gameTimer->start(16);
}

Game::~Game()
{
    delete ui;
}

void Game::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    /* Paint the background */
    painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

    /* Paint the player */
    _player->paint(painter);
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
        _player->setY(_player->getY() - _player->getVel());
        _player->setX(_player->getX() - _player->getVel());
    }
    else if (_keyUp && _keyRight)
    {
        _player->setY(_player->getY() - _player->getVel());
        _player->setX(_player->getX() + _player->getVel());
    }
    else if (_keyDown && _keyLeft)
    {
        _player->setY(_player->getY() + _player->getVel());
        _player->setX(_player->getX() - _player->getVel());
    }
    else if (_keyDown && _keyRight)
    {
        _player->setY(_player->getY() + _player->getVel());
        _player->setX(_player->getX() + _player->getVel());
    }
    else if (_keyUp)
        _player->setY(_player->getY() - _player->getVel());
    else if (_keyLeft)
        _player->setX(_player->getX() - _player->getVel());
    else if (_keyDown)
        _player->setY(_player->getY() + _player->getVel());
    else if (_keyRight)
        _player->setX(_player->getX() + _player->getVel());
}

/* SLOTS FUNCTIONS */
/* Main game updater */
void Game::update()
{
    movePlayer();
    repaint();
}
