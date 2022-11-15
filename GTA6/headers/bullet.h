#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QGraphicsPixmapItem
{
public:
    Bullet(int x, int y);
};

#endif // BULLET_H
