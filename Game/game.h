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

    void paintEvent(QPaintEvent * e);
    void mouseMoveEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);

private slots:
    void update();

private:
    Ui::Game *ui;

    QTimer* _gameTimer;

    Player* _player;
};

#endif // GAME_H
