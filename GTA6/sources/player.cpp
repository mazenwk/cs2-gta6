#include "headers/constants.h"
#include "headers/player.h"
#include <headers/powerpellet.h>

#include <QGraphicsScene>

#include <headers/bullet.h>
#include <headers/enemy.h>

Player::Player(int x, int y, int boardData[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH])
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "cj.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);

    // Set Position
    row = x;
    column = y;
    setPos(Environment::TILE_SCALE + column * Environment::TILE_SCALE, Environment::TILE_SCALE + row * Environment::TILE_SCALE);

    // Set data Array
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++)
        for (int j = 0; j < Environment::BOARD_WIDTH; j++)
            data[i][j] = boardData[i][j];
}

void Player::keyPressEvent(QKeyEvent* event)
{
    // Movement
    if ((event->key() == Qt::Key_W||event->key() == Qt::Key_Up) && data[row - 1][column] >= 0)
    {
        row--;
    }
    else if ((event->key() == Qt::Key_Down||event->key() == Qt::Key_S) && data[row + 1][column] >= 0)
    {
        row++;
    }
    else if ((event->key() == Qt::Key_Right||event->key() == Qt::Key_D) && data[row][column + 1] >= 0)
    {
        column++;
    }
    else if ((event->key() == Qt::Key_Left||event->key() == Qt::Key_A) && data[row][column - 1] >= 0)
    {
        column--;
    }

    // Set new position
    setPos(Environment::TILE_SCALE + column * Environment::TILE_SCALE, Environment::TILE_SCALE + row * Environment::TILE_SCALE);

    // Handle current collisions
    handleCollisions();
}

void Player::handleCollisions()
{
    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        if (str_type(*items[i]) == typeid(PowerPellet).name()) {
            isGodMode = true;
            scene()->removeItem(items[i]);
        } else if (str_type(*items[i]) == typeid(Enemy).name()) {
            damage();
        } else if (str_type(*items[i]) == typeid(Bullet).name()) {
            attack();
            scene()->removeItem(items[i]);
        }
    }
}

void Player::damage()
{
    // TODO: turn off god mode
    if (!isGodMode) {
        health--;
        if (health <= 0) {
            die();
        }
    }
}

void Player::die()
{
    // Game over screen
    scene()->removeItem(this);
}

void Player::attack()
{
   // Euclidean distance for closest enemy
}
