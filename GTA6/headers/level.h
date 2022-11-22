#ifndef LEVEL_H
#define LEVEL_H

#include "headers/constants.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/powerpellet.h"
#include "headers/weapon.h"

#include <QGraphicsView>
#include <QObject>

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
};

#endif // LEVEL_H
