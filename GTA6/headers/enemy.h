#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

/**
 * @brief The Enemy class
 */
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

    /**
     * @brief The x position of the enemy
     */
    int x;

    /**
     * @brief The y position of the enemy
     */
    int y;
    //change apperence
    void change_app();
};

#endif // ENEMY_H
