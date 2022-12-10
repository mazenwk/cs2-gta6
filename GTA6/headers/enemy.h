#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <stack>
#include "headers/constants.h"


/**
 * @brief The Enemy class
 */
class Enemy : public QGraphicsPixmapItem, public QObject
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
     * @brief The enemy health
     */
    int health { 2 };

    /**
     * @brief The x position of the enemy
     */
    int x;

    /**
     * @brief The y position of the enemy
     */
    int y;

    /**
     * @brief Damages the enemy and changes its appearance
     */
    void damage();

private:
    /**
     * @brief Changes the enemy appearance to damaged
     */
    void changeAppearanceToDamaged();

    /**
     * @brief Kills the enemy
     */
    void die();
    /**
     * @brief A* movement
     */
    /*//int boardData[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];
    typedef std::pair<int,int> Pair;
    std::stack<Pair> Path;
    bool isValid(const Pair& point);
    bool isUnBlocked(const int grid [ROW][COL],const Pair& point);
    bool isDestination(const Pair& position, const Pair& dest);
    double calculateHValue(const Pair& src, const Pair& dest);
    //void tracePath(const array<array<cell, COL>, ROW>& cellDetails,const Pair& dest);
   // void aStarSearch(const int grid[ROW][COL],const Pair& src, const Pair& dest);
   */
};

#endif // ENEMY_H
