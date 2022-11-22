#include "headers/gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Starting game!";
    GameWindow gameWindow("GTA 6");
    gameWindow.start();

    return a.exec();
}
