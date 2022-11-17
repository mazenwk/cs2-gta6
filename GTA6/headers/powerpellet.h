#ifndef POWERPELLET_H
#define POWERPELLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class PowerPellet : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Default parameterized constructor.
     * Constructs a new Powerpellet Pixmap on the board at the given position
     * @param x The x position on the board
     * @param y The y position on the board
     */
    PowerPellet(int x, int y);
};

#endif // POWERPELLET_H
