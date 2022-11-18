#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Default parameterized constructor.
     * Constructs a new Enemy Pixmap on the board at the given position
     * @param x The x position on the board
     * @param y The y position on the board
     */
    Enemy(int x, int y);

    int x;
    int y;
};

#endif // ENEMY_H
