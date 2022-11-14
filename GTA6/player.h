#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QObject>
#include <qgraphicsitem.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row, column;
    int data[10][10];
public:
    Player(int boardData[10][10]);
    int pHealth = 3;
    bool isGodMode = false;

   void damage();
public slots:
    void keyPressEvent(QKeyEvent* event);
};

#endif // PLAYER_H
