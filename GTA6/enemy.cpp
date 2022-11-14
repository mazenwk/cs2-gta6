#include "constants.h"
#include "enemy.h"

#include <QPixmap>

Enemy::Enemy(int x, int y)
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "ETweety.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);

    // Set Position
    setPos(50 + x * 50, 50 + y * 50);
}
