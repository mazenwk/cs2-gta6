#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "headers/bullet.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/powerpellet.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QString>

class Game {
public:
    /**
     * @brief Default parameterized constructor.
     * Creates a new view with sizes from the confguration and with the title given
     * @param gameTitle The game view window title
     */
    Game(QString gameTitle);

    /**
     * @brief Reads and loads the given level text file into the view by updating board data
     * @param levelFileName The level text file name
     */
    void loadLevel(QString levelFileName);

    /**
     * @brief Loads the game view resources and adds them to the game scene
     */
    void loadResources();

    /**
     * @brief Shows the game view and its scene as a window
     */
    void show();

    void watch();

    ~Game();
private:
    /**
     * @brief The game view
     */
    QGraphicsView view;

    /**
     * @brief The game scene
     */
    QGraphicsScene scene;

    /**
     * @brief The game board data
     */
    int boardData[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];

    /**
     * @brief The game board items
     */
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
    QList<Bullet*> bullets;

    /**
     * @brief The main player object
     */
    Player* player;

    /**
     * @brief Loads the collectibles (powerpellets, bullets, etc.) into the scene
     */
    void loadCollectibles();

    /**
     * @brief Loads the player into the scene
     */
    void loadPlayer(int x, int y);

    /**
     * @brief Loads the enemies into the scene
     */
    void loadEnemies();

    // TODO: Only one delay function
    void delay(int n);

    void displayGameOverWindow(QString textToDisplay);
};

#endif // GAME_H
