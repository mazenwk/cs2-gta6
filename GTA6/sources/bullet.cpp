#include "headers/constants.h"
#include "headers/bullet.h"

Bullet::Bullet(int x, int y)
{
    // Set Image
    QPixmap image(Resources::TILES_DIR + "weapon.png");
    image = image.scaledToWidth(Environment::TILE_SCALE);
    image = image.scaledToHeight(Environment::TILE_SCALE);
    setPixmap(image);

    // Set Position
    setPos(Environment::TILE_SCALE + x * Environment::TILE_SCALE, Environment::TILE_SCALE + y * Environment::TILE_SCALE);
}
