#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Default parameterized constructor.
     * Constructs a new Bullet Pixmap on the board at the given position
     * @param x The x position on the board
     * @param y The y position on the board
     */
    Bullet(int x, int y);
};

#endif // BULLET_H
