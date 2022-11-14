#include "constants.h"
#include "bullet.h"

Bullet::Bullet(int x, int y)
{
    // Set Image
    QPixmap image(Resources::TILES_DIR + "shuriken.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);

    // Set Position
    setPos(50 + x * 50, 50 + y * 50);
}
