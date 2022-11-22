#include "headers/game.h"
#include "headers/weapon.h"
#include "headers/constants.h"
#include "headers/enemy.h"

#include "headers/player.h"
#include "headers/powerpellet.h"
#include "headers/button.h"

#include <QString>
#include <QCoreApplication>

#include <stdlib.h>
#include <time.h>

/**********************************************************************************************************************************/
/********************************************* OBSOLETE - REPALCED WITH GAMEWINDOW ************************************************/
/***************************************************** LEFT TEMPORARILY ***********************************************************/
/**********************************************************************************************************************************/

Game::Game(QString gameTitle)
{
    view.setFixedSize(Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);
    view.setWindowTitle(gameTitle);
    QBrush brush(Qt::black);
    view.setBackgroundBrush(brush);
}

void Game::loadLevel(QString levelFileName)
{
    QFile file(Resources::LEVELS_DIR + levelFileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++) {
        for (int j = 0; j < Environment::BOARD_WIDTH; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }
    }
}

void Game::loadResources()
{
    // TODO: Convert to separate function
    QPixmap exteriorImage(Resources::TILES_DIR + "wall.jpg"); //interior
    exteriorImage = exteriorImage.scaledToWidth(Environment::TILE_SCALE);
    exteriorImage = exteriorImage.scaledToHeight(Environment::TILE_SCALE);

    QPixmap bricksImage2(Resources::TILES_DIR + "bricks.png");
    bricksImage2 = bricksImage2.scaledToWidth(Environment::TILE_SCALE);
    bricksImage2 = bricksImage2.scaledToHeight(Environment::TILE_SCALE);

    QPixmap interiorImage(Resources::TILES_DIR + "interior.jpg");
    interiorImage = interiorImage.scaledToWidth(Environment::TILE_SCALE);   //exterior
    interiorImage = interiorImage.scaledToHeight(Environment::TILE_SCALE);

    //--------------------------interior extras----------------------------------
    QPixmap bookshelfImage(Resources::TILES_DIR + "bookshelf.jpg");
    bookshelfImage = bookshelfImage.scaledToWidth(Environment::TILE_SCALE);
    bookshelfImage = bookshelfImage.scaledToHeight(Environment::TILE_SCALE);

    QPixmap boxImage(Resources::TILES_DIR + "box.jpg");
    boxImage = boxImage.scaledToWidth(Environment::TILE_SCALE);
    boxImage = boxImage.scaledToHeight(Environment::TILE_SCALE);

    QPixmap roomImage(Resources::TILES_DIR + "room.png");
    roomImage = roomImage.scaledToWidth(Environment::TILE_SCALE);
    roomImage = roomImage.scaledToHeight(Environment::TILE_SCALE);
    //---------------------------------------------------------------------------

    QPixmap PowerPelletImage(Resources::TILES_DIR + "Ice Creams.png");  //powerpellet
    interiorImage = interiorImage.scaledToWidth(Environment::TILE_SCALE);
    interiorImage = interiorImage.scaledToHeight(Environment::TILE_SCALE);

    // Add to the board
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++) {
        for (int j = 0; j < Environment::BOARD_WIDTH; j++) {
            // Set Image
            if (boardData[i][j] == -1)
                boardItems[i][j].setPixmap(exteriorImage);
                else if (boardData[i][j] == -2)
                    boardItems[i][j].setPixmap(bookshelfImage);
            else if (boardData[i][j] == -3)
                boardItems[i][j].setPixmap(bookshelfImage);
            else if (boardData[i][j] == -4)
                boardItems[i][j].setPixmap(boxImage);
            else if (boardData[i][j] == -5)
                boardItems[i][j].setPixmap(bricksImage2);
            else if (boardData[i][j] == 04)
                boardItems[i][j].setPixmap(roomImage);

            else {
                boardItems[i][j].setPixmap(interiorImage);
                if (boardData[i][j] == Environment::POWERPELLET_CODE) {
                    powerPellets.push_back(new PowerPellet(j, i));
                }
                else if (boardData[i][j] == Environment::ENEMY_CODE) {
                    enemies.push_back(new Enemy(j, i));
                }
                else if (boardData[i][j] == Environment::WEAPON_CODE) {
                    bullets.push_back(new Weapon(j, i));
                }
            }

            // Set Position
            boardItems[i][j].setPos(Environment::TILE_SCALE + j * Environment::TILE_SCALE, Environment::TILE_SCALE + i * Environment::TILE_SCALE);

            scene.addItem(&boardItems[i][j]);
        }
    }

    loadCollectibles();
    loadPlayer(7, 2);
    loadEnemies();
    player->setFocus();
}

void Game::show()
{
    view.setScene(&scene);
    view.show();
}

void Game::watch()
{
    while(player->health != 0) {
        delay(1);

        for (int i = 0; i < enemies.size(); i++) {
            int row = enemies[i]->x;
            int column = enemies[i]->y;

            srand((unsigned) time(NULL));
            int randmov;

            randmov = (1+(rand() * i)%4);
            switch(randmov)
            {
                case 1: //move to the right
                if (boardData[row + 1][column] >= 0) {
                    enemies[i]->x++;
                }
                break;

                case 2: //move to the left
                if (boardData[row - 1][column] >= 0) {
                    enemies[i]->x--;
                }
                break;

                case 3: //move up
                if (boardData[row][column + 1] >= 0) {
                    enemies[i]->y++;
                }
                break;

                case 4: //move down
                if (boardData[row][column - 1] >= 0) {
                    enemies[i]->y--;
                }
                break;
            }

            enemies[i]->setPos(Environment::TILE_SCALE + enemies[i]->x * Environment::TILE_SCALE, Environment::TILE_SCALE + enemies[i]->y * Environment::TILE_SCALE);
        }
    }

    if (player->health <= 0) {
        displayGameOverWindow("GAME OVER!");
    }

}

Game::~Game()
{
    delete player;
    for (int i = 0; i < powerPellets.size(); i++) {
        delete powerPellets[i];
    }
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    for (int i = 0; i < bullets.size(); i++) {
        delete bullets[i];
    }
}

void Game::loadCollectibles()
{
    for (int i = 0; i < powerPellets.size(); i++) {
        scene.addItem(powerPellets[i]);
    }
    for (int i = 0; i < bullets.size(); i++) {
        scene.addItem(bullets[i]);
    }
}

void Game::loadPlayer(int x, int y)
{
    player = new Player(y, x, boardData);
    scene.addItem(player);

    player->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
}

void Game::loadEnemies()
{
    for (int i = 0; i < enemies.size(); i++) {
        scene.addItem(enemies[i]);
    }
}

void Game::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Game::displayGameOverWindow(QString textToDisplay)
{
    // Disable all scene items
    for (size_t i = 0, n = scene.items().size(); i < n; i++){
        scene.items()[i]->setEnabled(false);
    }

    // Pop up semi transparent panel
    UI::drawPanel(&scene, 0, 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT, Qt::black, 0.65);

    // Draw panel
    UI::drawPanel(&scene, 312, 184, 400, 550, Qt::lightGray, 0.75);

    // Create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410, 300);
    scene.addItem(playAgain);
    Button::connect(playAgain, SIGNAL(clicked()), &view, SLOT(Game::restartGame()));

    // Create quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(410, 375);
    scene.addItem(quit);
    Button::connect(quit, SIGNAL(clicked()), &view, SLOT(close()));

    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    QFont* font = new QFont;
    overText->setPos(380, 210);
    font->setPointSize(32);
    font->setBold(true);
    overText->setFont(*font);
    overText->setDefaultTextColor(Qt::white);

    scene.addItem(overText);
}

void Game::restartGame()
{
    delete player;
    for (int i = 0; i < powerPellets.size(); i++) {
        delete powerPellets[i];
    }
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    for (int i = 0; i < bullets.size(); i++) {
        delete bullets[i];
    }

    enemies.clear();
    powerPellets.clear();
    bullets.clear();

    //scene.clear();

    loadLevel("123.txt");
    loadResources();
}

void Game::close()
{
    view.close();
}


