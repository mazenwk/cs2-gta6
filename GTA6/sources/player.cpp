#include "headers/constants.h"
#include "headers/player.h"
#include "headers/powerpellet.h"
#include "headers/weapon.h"
#include "headers/enemy.h"

#include <QGraphicsScene>
#include <QCoreApplication>
#include <QWidget>

Player::Player(int x, int y, int boardData[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH])
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "noweaponkid.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);

    // Set Position
    row = x;
    column = y;
    setPos(Environment::TILE_SCALE + column * Environment::TILE_SCALE, Environment::TILE_SCALE + row * Environment::TILE_SCALE);

    // Copy data Array
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++)
        for (int j = 0; j < Environment::BOARD_WIDTH; j++)
            data[i][j] = boardData[i][j];
}

void Player::keyPressEvent(QKeyEvent* event)
{
    // Movement
    if ((event->key() == Qt::Key_W|| event->key() == Qt::Key_Up) && data[row - 1][column] >= 0)
    {
        row--;
    }
    else if ((event->key() == Qt::Key_Down|| event->key() == Qt::Key_S) && data[row + 1][column] >= 0)
    {
        row++;
    }
    else if ((event->key() == Qt::Key_Right|| event->key() == Qt::Key_D) && data[row][column + 1] >= 0)
    {
        column++;
    }
    else if ((event->key() == Qt::Key_Left|| event->key() == Qt::Key_A) && data[row][column - 1] >= 0)
    {
        column--;
    }

    // Set new position
    setPos(Environment::TILE_SCALE + column * Environment::TILE_SCALE, Environment::TILE_SCALE + row * Environment::TILE_SCALE);
}

void Player::damage()
{
    if (!isGodMode) {
        health--;
        if (health <= 0) {
            die();
        }
    }
}

void Player::attack()
{
    // Euclidean distance for closest enemy
}

void Player::change_app()
{
    QPixmap image(Resources::ENTITIES_DIR + "with weapons kid.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);
}

void Player::die()
{
    scene()->removeItem(this);
}
