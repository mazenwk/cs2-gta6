#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy : public QGraphicsPixmapItem
{
public:
    Enemy(int x, int y);
};

#endif // ENEMY_H
