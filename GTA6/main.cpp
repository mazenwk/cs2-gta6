#include "headers/bullet.h"
#include "headers/constants.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/powerpellet.h"

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

    view.setFixedSize(EnvironmentConstants::SCREEN_WIDTH, EnvironmentConstants::SCREEN_HEIGHT);
    view.setWindowTitle("Maze Game");
    QBrush brush(Qt::black);
    view.setBackgroundBrush(brush);

    QFile file(Resources::LEVELS_DIR + "123.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int boardData[EnvironmentConstants::BOARD_SIZE][EnvironmentConstants::BOARD_SIZE];
    QString temp;
    for (int i = 0; i < EnvironmentConstants::BOARD_SIZE; i++)
       for (int j = 0; j < EnvironmentConstants::BOARD_SIZE; j++)
       {
           stream >> temp;
           boardData[i][j] = temp.toInt();
       }

    QPixmap grassImage(Resources::TILES_DIR + "Grass.png");
    grassImage = grassImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    grassImage = grassImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    QPixmap bricksImage(Resources::TILES_DIR + "Lava.png");
    bricksImage = bricksImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    QPixmap PowerPelletImage(Resources::TILES_DIR + "Ice Creams.png");
    bricksImage = bricksImage.scaledToWidth(EnvironmentConstants::TILE_SCALE);
    bricksImage = bricksImage.scaledToHeight(EnvironmentConstants::TILE_SCALE);

    QList<PowerPellet*> powerPellets;
    QList<Enemy*> enemies;
    QList<Bullet*> bullets;

    QGraphicsPixmapItem boardItems[EnvironmentConstants::BOARD_SIZE][EnvironmentConstants::BOARD_SIZE];
    for (int i = 0; i < EnvironmentConstants::BOARD_SIZE; i++)
       for (int j = 0; j < EnvironmentConstants::BOARD_SIZE; j++)
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
           boardItems[i][j].setPos(EnvironmentConstants::TILE_SCALE + j * EnvironmentConstants::TILE_SCALE, EnvironmentConstants::TILE_SCALE + i * EnvironmentConstants::TILE_SCALE);

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
