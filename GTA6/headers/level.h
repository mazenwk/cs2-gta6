#ifndef LEVEL_H
#define LEVEL_H

#include "headers/constants.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/powerpellet.h"
#include "headers/weapon.h"

#include <QGraphicsView>
#include <QObject>
#include <cstdlib>

/**
 * @brief The Level class
 */
class Level
{
public:
    /**
     * @brief Default parameterized constructor.
     * Creates a new level with its own scene and entities
     * @param levelName
     */
    Level(QString levelName);

    /**
     * @brief The scene for this level
     */
    QGraphicsScene* levelScene;

    /**
     * @brief The level name
     */
    QString name;

    /**
     * @brief True if the player won
     */
    bool playerWon { false };

    /**
     * @brief Watches the game.
     * Moves the enemies and does health checks.
     * Runs separately
     */
    void watch();

    ~Level();

private:
    /**
     * @brief The game board data
     */
    int boardData[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];

    /**
     * @brief The game board items
     */
    //QVector<QVector<QGraphicsPixmapItem>> boardItems;
    QGraphicsPixmapItem boardItems[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];

    /**
     * @brief The currently present powerpellets in the scene
     */
    QList<PowerPellet*> powerPellets;

    /**
     * @brief The currently present enemies in the scene
     */
    QList<Enemy*> enemies;

    /**
     * @brief The bullets present powerpellets in the scene
     */
    QList<Weapon*> bullets;

    /**
     * @brief The current player lives
     */
    QList<QGraphicsPixmapItem*> playerLives;

    /**
     * @brief The main player object
     */
    Player* player;

    /**
     * @brief Loads the board data from the level text file
     */
    void loadLevelData();

    /**
     * @brief Loads the level resources and images
     */
    void loadLevelResources();

    /**
     * @brief Loads the collectibles (powerpellets, bullets, etc.) into the scene
     */
    void loadCollectibles();

    /**
     * @brief Loads the player into the scene at the given x and y positions
     * @param x The x position on the board
     * @param y The y position on the board
     */
    void loadPlayer(int x, int y);

    /**
     * @brief Loads the enemies into the scene
     */
    void loadEnemies();

    /**
     * @brief Hanldes the enemies lives and movmenents
     */
    void handleEnemies();

    /**
     * @brief Handles the player collisions
     */
    void handlePlayerCollisions();

    /**
     * @brief Updates the UI after handlers
     */
    void updateUI();

    /**
     * @brief A* graph
     */
    typedef std::pair<int,int> Pair;

    struct cell {
            // Row and Column index of its parent
            int parent_i,parent_j ;
            // f = g + h
            double f, g, h;
    };

    int ROW = Environment::BOARD_HEIGHT;
    int COL = Environment::BOARD_WIDTH;
    std::stack<Pair> Pathfinal;
    bool isValid(int row, int col);
    bool isUnBlocked (int grid[][Environment::BOARD_WIDTH], int row,int col);
    bool isDestination (int row,int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][Environment::BOARD_WIDTH], Pair dest);
    void astarSearch(int grid[][Environment::BOARD_WIDTH], Pair src, Pair dest);
};

#endif // LEVEL_H
