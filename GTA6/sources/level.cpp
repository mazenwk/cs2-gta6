#include "headers/level.h"

Level::Level(QString levelName)
{
    name = levelName;

    levelScene = new QGraphicsScene();
    levelScene->setSceneRect(0 , 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);

    loadLevelData();
    loadLevelResources();
}

void Level::loadLevelData()
{
    QFile file(Resources::LEVELS_DIR + name);
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

void Level::loadLevelResources()
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
                else if (boardData[i][j] == Environment::BULLET_CODE) {
                    bullets.push_back(new Bullet(j, i));
                }
            }

            // Set Position
            boardItems[i][j].setPos(Environment::TILE_SCALE + j * Environment::TILE_SCALE, Environment::TILE_SCALE + i * Environment::TILE_SCALE);

            levelScene->addItem(&boardItems[i][j]);
        }
    }

    loadCollectibles();
    loadPlayer(7, 2);
    loadEnemies();
    player->setFocus();
}

void Level::loadCollectibles()
{
    for (int i = 0; i < powerPellets.size(); i++) {
        levelScene->addItem(powerPellets[i]);
    }
    for (int i = 0; i < bullets.size(); i++) {
        levelScene->addItem(bullets[i]);
    }
}

void Level::loadPlayer(int x, int y)
{
    player = new Player(y, x, boardData);
    levelScene->addItem(player);

    player->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
}

void Level::loadEnemies()
{
    for (int i = 0; i < enemies.size(); i++) {
        levelScene->addItem(enemies[i]);
    }
}

void Level::watch()
{
    while(player->health != 0) {
           // TODO: shorter duration
           UI::delay(500);

           for (int i = 0; i < enemies.size(); i++) {
               int row = enemies[i]->y;
               int column = enemies[i]->x;

               srand((unsigned) time(NULL));
               int randmov;

               randmov = (1+(rand() * i)%4);
               switch(randmov)
               {
                   case 1: //move to the right
                   if (boardData[row + 1][column] >= 0) {
                       enemies[i]->y++;
                   }
                   break;

                   case 2: //move to the left
                   if (boardData[row - 1][column] >= 0) {
                       enemies[i]->y--;
                   }
                   break;

                   case 3: //move up
                   if (boardData[row][column + 1] >= 0) {
                       enemies[i]->x++;
                   }
                   break;

                   case 4: //move down
                   if (boardData[row][column - 1] >= 0) {
                       enemies[i]->x--;
                   }
                   break;
               }

               enemies[i]->setPos(Environment::TILE_SCALE + enemies[i]->x * Environment::TILE_SCALE, Environment::TILE_SCALE + enemies[i]->y * Environment::TILE_SCALE);
           }
       }
   }

Level::~Level()
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
