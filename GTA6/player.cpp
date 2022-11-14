#include "constants.h"
#include "player.h"

Player::Player(int boardData[10][10])
{
    // Set Image
    QPixmap image(Resources::ENTITIES_DIR + "cj.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);

    // Set Position
    row = 1;
    column = 1;
    setPos(50 + column * 50, 50 + row * 50);

    // Set data Array
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            data[i][j] = boardData[i][j];
}

void Player::damage()
{
    if (!isGodMode) {

    }
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
    setPos(50 + column * 50, 50 + row * 50);

    if (data[row][column] == 99) {
        isGodMode = true;

    }

    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        //if (typeid(*items[i]) == typeid(Food))
            //scene()->removeItem(items[i]);
    }
}
