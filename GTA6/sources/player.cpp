#include "headers/constants.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/powerpellet.h"

#include <thread>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QtMath>
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

    handleCollisions();
}

void Player::handleCollisions()
{
    QList<QGraphicsItem*> playerCollisions = collidingItems();

    for (int i = 0; i < playerCollisions.size(); i++)
    {
        if (str_type(*playerCollisions[i]) == typeid(Enemy).name()) {
            damage();
            // TODO: Reset player & enemy positions
        } else if (str_type(*playerCollisions[i]) == typeid(PowerPellet).name()) {
            if (!isGodMode) {
                scene()->removeItem(playerCollisions[i]);

                std::thread godModeThread(&Player::godMode, this);
                godModeThread.detach();
            }
        }
    }
}

void Player::godMode()
{
    isGodMode = true;
    for (int i = 0; i < 5; ++i) {
        UI::delay(1000);
        //timer--;
        //timerText->setPlainText(QString::number(timer));
    }
    isGodMode = false;
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

void Player::attack(QList<Enemy*> enemies)
{
    int closestEnemyIndex = 0;
    int minDistance = INT_MAX;

    for (int i = 0; i < enemies.size(); ++i) {
        int distance = qSqrt( qPow((row - enemies[i]->y), 2) + qPow((column - enemies[i]->x), 2));

        if (distance < minDistance) {
            minDistance = distance;
            closestEnemyIndex = i;
        }
    }

    enemies[closestEnemyIndex]->damage();

}

void Player::changeAppearance()
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

void Player::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
int Player::getrow()
{
    return row;
}
int Player::getcol()
{
    return column;
}
