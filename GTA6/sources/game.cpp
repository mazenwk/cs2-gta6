#include "headers/game.h"
#include "headers/bullet.h"
#include "headers/constants.h"
#include "headers/enemy.h"

#include "headers/player.h"
#include "headers/powerpellet.h"

#include <QString>

Game::Game(QString gameTitle)
{
    view.setFixedSize(Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);
    view.setWindowTitle(gameTitle);
    QBrush brush(Qt::black);
    view.setBackgroundBrush(brush);
}

void Game::loadLevel(QString levelFileName)
{
    QFile file(Resources::LEVELS_DIR + levelFileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++) {
        for (int j = 0; j < Environment::BOARD_WIDTH; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }
    }
}

void Game::loadResources()
{
    // TODO: Convert to separate function
    QPixmap grassImage(Resources::TILES_DIR + "Grass.png");
    grassImage = grassImage.scaledToWidth(Environment::TILE_SCALE);
    grassImage = grassImage.scaledToHeight(Environment::TILE_SCALE);

    QPixmap bricksImage(Resources::TILES_DIR + "Lava.png");
    bricksImage = bricksImage.scaledToWidth(Environment::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(Environment::TILE_SCALE);

    QPixmap PowerPelletImage(Resources::TILES_DIR + "Ice Creams.png");
    bricksImage = bricksImage.scaledToWidth(Environment::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(Environment::TILE_SCALE);

    // Add to the board
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++) {
        for (int j = 0; j < Environment::BOARD_WIDTH; j++)
        {
            // Set Image
            if (boardData[i][j] < 0) {
                boardItems[i][j].setPixmap(bricksImage);
            }
            else {
                boardItems[i][j].setPixmap(grassImage);
                if (boardData[i][j] == Environment::POWERPELLET_CODE) {
                    powerPellets.push_back(new PowerPellet(j, i));
                }
                else if (boardData[i][j] == Environment::ENEMY_CODE) {
                    enemies.push_back(new Enemy(j, i));
                }
                else if (boardData[i][j] == Environment::BULLET_CODE) {
                    bullets.push_back(new Bullet(j, i));
                }
            }

            // Set Position
            boardItems[i][j].setPos(Environment::TILE_SCALE + j * Environment::TILE_SCALE, Environment::TILE_SCALE + i * Environment::TILE_SCALE);

            scene.addItem(&boardItems[i][j]);
        }
    }

    loadCollectibles();
    loadPlayer(1, 1);
    loadEnemies();
}

void Game::show()
{
    view.setScene(&scene);
    view.show();
}

Game::~Game()
{
    delete player;
    for (int i = 0; i < powerPellets.size(); i++) {
        delete powerPellets[i];
    }
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    for (int i = 0; i < bullets.size(); i++) {
        delete bullets[i];
    }
}

void Game::loadCollectibles()
{
    for (int i = 0; i < powerPellets.size(); i++) {
        scene.addItem(powerPellets[i]);
    }
    for (int i = 0; i < bullets.size(); i++) {
        scene.addItem(bullets[i]);
    }
}

void Game::loadPlayer(int x, int y)
{
    player = new Player(y, x, boardData);
    scene.addItem(player);

    player->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    player->setFocus();
}

void Game::loadEnemies()
{
    for (int i = 0; i < enemies.size(); i++) {
        scene.addItem(enemies[i]);
    }
}
