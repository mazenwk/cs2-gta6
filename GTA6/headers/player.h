#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QObject>
#include <qgraphicsitem.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Default parameterized constructor.
     * Constructs a new Player Pixmap on the board at the given position
     * @param x The x position on the board
     * @param y The y position on the board
     * @param boardData A copy of the current board data
     */
    Player(int x, int y, int boardData[15][15]);

    /**
     * @brief The player health
     */
    int health{ 3 };

    /**
     * @brief Whether the player is currently in god mode or not.
     * Player does not receive damage when true
     */
    bool isGodMode{ false };
public slots:
    /**
     * @brief Controls the player movement by responding to user input and calls handleCollisions()
     * @param event The keypress event
     */
    void keyPressEvent(QKeyEvent* event);
private:
    /**
     * @brief The current row value of the player
     */
    int row {};

    /**
     * @brief The current column value of the player
     */
    int column {};

    /**
     * @brief A copy of the current board data
     */
    int data[15][15];

    /**
     * @brief Hanldes the current collisions with the player
     */
    void handleCollisions();

    /**
     * @brief Damages the player by one heart if not in god mode
     */
    void damage();

    /**
     * @brief Kills the player
     */
    void die();

    /**
     * @brief Attacks the nearest enemy
     */
    void attack();

    void change_app();


    void delay(int n);
};

#endif // PLAYER_H
