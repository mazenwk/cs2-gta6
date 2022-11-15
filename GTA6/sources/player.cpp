#include "headers/constants.h"
#include "headers/player.h"
#include <headers/powerpellet.h>

#include <QGraphicsScene>

#include <headers/bullet.h>
#include <headers/enemy.h>

Player::Player(int boardData[EnvironmentConstants::BOARD_SIZE][EnvironmentConstants::BOARD_SIZE])
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "cj.png");
    image = image.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    image = image.scaledToHeight(EnvironmentConstants::TILE_SCALE);
    setPixmap(image);

    // Set Position
    row = 1;
    column = 1;
    setPos(EnvironmentConstants::TILE_SCALE + column * EnvironmentConstants::TILE_SCALE, EnvironmentConstants::TILE_SCALE + row * EnvironmentConstants::TILE_SCALE);

    // Set data Array
    for (int i = 0; i < EnvironmentConstants::BOARD_SIZE; i++)
        for (int j = 0; j < EnvironmentConstants::BOARD_SIZE; j++)
            data[i][j] = boardData[i][j];
}

void Player::keyPressEvent(QKeyEvent* event)
{
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
    setPos(EnvironmentConstants::TILE_SCALE + column * EnvironmentConstants::TILE_SCALE, EnvironmentConstants::TILE_SCALE + row * EnvironmentConstants::TILE_SCALE);

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
    if (!isGodMode) {
        // Get damaged
    }
}

void Player::attack() {
    // Ecledian Distance
}
