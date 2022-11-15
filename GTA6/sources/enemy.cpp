#include "headers/constants.h"
#include "headers/enemy.h"

#include <QPixmap>

Enemy::Enemy(int x, int y)
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "ETweety.png");
    image = image.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    image = image.scaledToHeight(EnvironmentConstants::TILE_SCALE);
    setPixmap(image);

    // Set Position
    setPos(EnvironmentConstants::TILE_SCALE + x * EnvironmentConstants::TILE_SCALE, EnvironmentConstants::TILE_SCALE + y * EnvironmentConstants::TILE_SCALE);
}
