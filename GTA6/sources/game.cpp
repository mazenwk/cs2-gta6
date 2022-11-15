#include "headers/game.h"
#include "headers/bullet.h"
#include "headers/constants.h"
#include "headers/enemy.h"

#include "headers/player.h"
#include "headers/powerpellet.h"

#include <QString>

Game::Game(QString gameTitle)
{
    view.setFixedSize(EnvironmentConstants::SCREEN_WIDTH, EnvironmentConstants::SCREEN_HEIGHT);
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
    for (int i = 0; i < EnvironmentConstants::BOARD_SIZE; i++) {
        for (int j = 0; j < EnvironmentConstants::BOARD_SIZE; j++)
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
    grassImage = grassImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    grassImage = grassImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    QPixmap bricksImage(Resources::TILES_DIR + "Lava.png");
    bricksImage = bricksImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    QPixmap PowerPelletImage(Resources::TILES_DIR + "Ice Creams.png");
    bricksImage = bricksImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    // Add to the board
    for (int i = 0; i < EnvironmentConstants::BOARD_SIZE; i++) {
        for (int j = 0; j < EnvironmentConstants::BOARD_SIZE; j++)
        {
            // Set Image
            if (boardData[i][j] < 0) {
                boardItems[i][j].setPixmap(bricksImage);
            }
            else {
                boardItems[i][j].setPixmap(grassImage);
                if (boardData[i][j] == 99) { // Power Pallet
                    powerPellets.push_back(new PowerPellet(j, i));
                }
                else if (boardData[i][j] == 98) { // Enemy
                    enemies.push_back(new Enemy(j, i));
                }
                else if (boardData[i][j] == 97) {
                    bullets.push_back(new Bullet(j, i));
                }
            }

            // Set Position
            boardItems[i][j].setPos(EnvironmentConstants::TILE_SCALE + j * EnvironmentConstants::TILE_SCALE, EnvironmentConstants::TILE_SCALE + i * EnvironmentConstants::TILE_SCALE);

            scene.addItem(&boardItems[i][j]);
        }
    }

    loadCollectibles();
    loadPlayer();
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

void Game::loadPlayer()
{
    player = new Player(boardData);
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
