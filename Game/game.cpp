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

void Game::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    /* Paint the background */
    painter.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Qt::black);

    /* Paint the player */
    _player->paint(painter);
}

void Game::mouseMoveEvent(QMouseEvent* e)
{

}

void Game::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_W)
    {
        _player->setY(_player->getY() - _player->getVel());
    }
    else if (e->key() == Qt::Key_A)
    {
        _player->setX(_player->getX() - _player->getVel());
    }
    else if (e->key() == Qt::Key_S)
    {
        _player->setY(_player->getY() + _player->getVel());
    }
    else if (e->key() == Qt::Key_D)
    {
        _player->setX(_player->getX() + _player->getVel());
    }
}

/* SLOTS FUNCTIONS */
void Game::update()
{
    repaint();
}
