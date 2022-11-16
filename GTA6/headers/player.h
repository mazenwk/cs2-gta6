#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QObject>
#include <qgraphicsitem.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(int x, int y, int boardData[15][15]);
    int health = 3;
    bool isGodMode = false;
public slots:
    void keyPressEvent(QKeyEvent* event);
private:
    int row, column;
    int data[15][15];
    void damage();
    void die();
    void attack();
};

#endif // PLAYER_H
