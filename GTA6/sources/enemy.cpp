#include "headers/constants.h"
#include "headers/enemy.h"

#include <QPixmap>

Enemy::Enemy(int x, int y)
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "enemy 1.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);

    // Set Position
    setPos(Environment::TILE_SCALE + x * Environment::TILE_SCALE, Environment::TILE_SCALE + y * Environment::TILE_SCALE);

    this->x = x;
    this->y = y;

}

void Enemy::damage()
{
    health--;
    if (health <= 0) {
        die();
    }

    changeAppearanceToDamaged();
}

void Enemy::changeAppearanceToDamaged()
{
    QPixmap image(Resources::ENTITIES_DIR + "enemy 2.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);
}

void Enemy::die()
{
    scene()->removeItem(this);
}
