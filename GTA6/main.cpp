#include "bullet.h"
#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "powerPellet.h"

#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <qfile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QGraphicsView view;
    QGraphicsScene scene;

    // qDebug() << "here"; // You can use this for tracing

    view.setFixedSize(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
    view.setWindowTitle("Maze Game");
    QBrush brush(Qt::black);
    view.setBackgroundBrush(brush);

    QFile file(Resources::LEVELS_DIR + "123.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int boardData[15][15];
    QString temp;
    for (int i = 0; i < 15; i++)
       for (int j = 0; j < 15; j++)
       {
           stream >> temp;
           boardData[i][j] = temp.toInt();
       }

    QPixmap grassImage(Resources::TILES_DIR + "Grass.png");
    grassImage = grassImage.scaledToWidth(Constants::TILE_SCALE);
    grassImage = grassImage.scaledToHeight(Constants::TILE_SCALE);

    QPixmap bricksImage(Resources::TILES_DIR + "Lava.png");
    bricksImage = bricksImage.scaledToWidth(Constants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(Constants::TILE_SCALE);

    QPixmap PowerPelletImage(Resources::TILES_DIR + "Ice Creams.png");
    bricksImage = bricksImage.scaledToWidth(Constants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(Constants::TILE_SCALE);

    QList<PowerPellet*> powerPellets;
    QList<Enemy*> enemies;
    QList<Bullet*> bullets;

    QGraphicsPixmapItem boardItems[15][15];
    for (int i = 0; i < 15; i++)
       for (int j = 0; j < 15; j++)
       {
           // Set Image
           if (boardData[i][j] < 0)
               boardItems[i][j].setPixmap(bricksImage);
           else {
               boardItems[i][j].setPixmap(grassImage);
               if (boardData[i][j] == 99) { // Power Pallet
                   powerPellets.push_back(new PowerPellet(j, i));
               } else if (boardData[i][j] == 98) { // Enemy
                    enemies.push_back(new Enemy(j, i));
               } else if (boardData[i][j] == 97) {
                    bullets.push_back(new Bullet(j, i));
               }
             }

           // Set Position
           boardItems[i][j].setPos(Constants::TILE_SCALE + j * Constants::TILE_SCALE, Constants::TILE_SCALE + i * Constants::TILE_SCALE);

           // Add to the Scene
           scene.addItem(&boardItems[i][j]);
           for (int i = 0; i < powerPellets.size(); i++) {
               scene.addItem(powerPellets[i]);
           }
           for (int i = 0; i < enemies.size(); i++) {
               scene.addItem(enemies[i]);
           }
           for (int i = 0; i < bullets.size(); i++) {
               scene.addItem(bullets[i]);
           }

       }

    Player player(boardData);
    scene.addItem(&player);

    player.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    player.setFocus();

    view.setScene(&scene);
    view.show();

    return a.exec();
}
