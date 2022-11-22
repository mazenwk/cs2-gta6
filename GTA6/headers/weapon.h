#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>

/**
 * @brief The Weapon class
 */
class Weapon : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Default parameterized constructor.
     * Constructs a new Weapon Pixmap on the board at the given coordinates
     * @param x The x position on the board
     * @param y The y position on the board
     */
    Weapon(int x, int y);
};

#endif // WEAPON_H
