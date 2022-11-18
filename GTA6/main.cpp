#include "headers/game.h"
//#include "headers/constants.h"

#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <qfile.h>

// qDebug() << "here"; // You can use this for tracing

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game("Maze Game");
    game.loadLevel("123.txt");
    game.loadResources();
    game.show();
    game.watch();

    return a.exec();
}
