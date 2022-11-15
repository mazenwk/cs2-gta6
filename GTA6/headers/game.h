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

class Game
{
public:
    Game(QString gameTitle);
    void loadLevel(QString levelFileName);
    void loadResources();
    void show();
    ~Game();
private:
    QGraphicsView view;
    QGraphicsScene scene;

    int boardData[EnvironmentConstants::BOARD_SIZE][EnvironmentConstants::BOARD_SIZE];
    QGraphicsPixmapItem boardItems[EnvironmentConstants::BOARD_SIZE][EnvironmentConstants::BOARD_SIZE];

    QList<PowerPellet*> powerPellets;
    QList<Enemy*> enemies;
    QList<Bullet*> bullets;

    Player* player;

    void loadCollectibles();
    void loadPlayer();
    void loadEnemies();
};

#endif // GAME_H
