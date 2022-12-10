#include "headers/level.h"

#include <thread>

Level::Level(QString levelName, QList<Enemy*> enemies)
{
    // Create a new level
    name = levelName;

    // Create level scene
    levelScene = new QGraphicsScene();
    levelScene->setSceneRect(0 , 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);

    // Load scene
    loadLevelData();
    loadLevelResources();
    for(int i = 0; i < enemies.size(); i++){
    QTimer * enemytimer = new QTimer();
        connect(enemytimer,SIGNAL(timeout()),enemies[i],SLOT(move()));
        enemytimer->start(500);
    }
}
Level::Level(QString levelName)
{
    // Create a new level
    name = levelName;

    // Create level scene
    levelScene = new QGraphicsScene();
    levelScene->setSceneRect(0 , 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);

    // Load scene
    loadLevelData();
    loadLevelResources();
}

void Level::loadLevelData()
{
    // Loads the board data from the file
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

    // Loads the level textures and resources
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

    // Adds the resources to the board items
    for (int i = 0; i < Environment::BOARD_HEIGHT; i++) {
        for (int j = 0; j < Environment::BOARD_WIDTH; j++) {

            if (boardData[i][j] == Environment::EXTERIOR_CODE)
                boardItems[i][j].setPixmap(exteriorImage);
            else if (boardData[i][j] == Environment::BOOKSHELF_CODE)
                    boardItems[i][j].setPixmap(bookshelfImage);
            else if (boardData[i][j] == -3)
                boardItems[i][j].setPixmap(bookshelfImage);
            else if (boardData[i][j] == Environment::BOX_CODE)
                boardItems[i][j].setPixmap(boxImage);
            else if (boardData[i][j] == Environment::BRICKS2_CODE)
                boardItems[i][j].setPixmap(bricksImage2);
            else if (boardData[i][j] == Environment::ROOM_CODE)
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

            // Add to scene
            levelScene->addItem(&boardItems[i][j]);
        }
    }

    // Load into the scene
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

    godModeText = new QGraphicsTextItem("GOD MODE ON");
    QFont* font = new QFont;
    godModeText->setPos(1100, 210);
    font->setPointSize(32);
    font->setBold(true);
    godModeText->setFont(*font);
    godModeText->setDefaultTextColor(Qt::white);

    levelScene->addItem(godModeText);
    godModeText->setVisible(false);
}

void Level::loadPlayer(int x, int y)
{
    player = new Player(y, x, boardData);
    levelScene->addItem(player);

    for (int i = 0; i < player->health; ++i) {
        QPixmap heart(Resources::UI_DIR + "heart.png");
        heart = heart.scaledToWidth(Environment::TILE_SCALE);
        heart = heart.scaledToHeight(Environment::TILE_SCALE);

        playerLives.append(new QGraphicsPixmapItem());
        playerLives[i]->setPixmap(heart);
        playerLives[i]->setPos(Environment::TILE_SCALE + (Environment::BOARD_WIDTH + 1 + i) * Environment::TILE_SCALE, Environment::TILE_SCALE + 0 * Environment::TILE_SCALE);
        levelScene->addItem(playerLives[i]);
    }

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
        UI::delay(100);
        //handleEnemies();
        if (player->moved) {
            move();
            player->moved = false;
        }
        handlePlayerCollisions();
        updateUI();

        if (enemies.size() == 0) {
            playerWon = true;
            break;
        }
    }
}

void Level::handleEnemies()
{
    for (int i = 0; i < enemies.size(); i++) {
        // --------------------------------------------------------------------- Move enemies ----------------------------------------------------------------------
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
        //  ---------------------------------------------------------------------------------------------------------------------------------------------------------

        // Remove dead enemies
        if (enemies[i]->health <= 0) {
            enemies.removeAt(i);
        }
    }
}

void Level::handlePlayerCollisions()
{
    QList<QGraphicsItem*> playerCollisions = player->collidingItems();
    for (int i = 0; i < playerCollisions.size(); i++)
    {
        if (str_type(*playerCollisions[i]) == typeid(Weapon).name()) {
            player->attack(enemies);
            levelScene->removeItem(playerCollisions[i]);
            // change apperence
                player->changeAppearance();
                UI::delay(400);
                QPixmap image(Resources::ENTITIES_DIR + "noweaponkid.png");
                image = image.scaledToWidth(Environment::TILE_SCALE);
                image = image.scaledToHeight(Environment::TILE_SCALE);
                player->setPixmap(image);
        } else  if (str_type(*playerCollisions[i]) == typeid(Enemy).name()) {
                    if (!player->damaged) {
                        player->damage();
                        player->damaged = true;
                    }
        }
    }
}

void Level::updateUI()
{
    // Remove player hearts
    if (player->health != playerLives.count()) {
        levelScene->removeItem(playerLives[playerLives.count() - 1]);
        playerLives.removeAt(playerLives.count() - 1);
    }

    if (player->isGodMode) {
        godModeText->setVisible(true);
    } else if (godModeText->isVisible()) {
        godModeText->setVisible(false);
    }
}


//int ROW = Environment::BOARD_HEIGHT;
//int COL = Environment::BOARD_WIDTH;

bool Level::isValid(int row, int col)
{
    // Returns true if row number and column number is in range
         return (row >= 0) && (row < Environment::BOARD_HEIGHT) && (col >= 0) && (col < Environment::BOARD_WIDTH);
}

// A Function to check whether the given cell is blocked or not
bool Level::isUnBlocked(int grid[][Environment::BOARD_WIDTH], int row,int col)
{
    //Retur true if cell is not blocked
    if(grid[row][col] >= 0)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}


bool Level::isDestination (int row,int col, Pair dest)
{
    if(row == dest.first && col == dest.second)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

double Level::calculateHValue(int row, int col, Pair dest)
{
    //Return using the distance formula
    return((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

void Level::tracePath(cell cellDetails[][Environment::BOARD_WIDTH], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;
    while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(std::make_pair(row, col));
    Pathfinal = Path;
    qDebug()<<Pathfinal.size()<<"before";
    while(!Path.empty())
    {
        std::pair<int, int>p = Path.top();
        Path.pop();
        qDebug() <<"("<<p.first<< p.second<<")";
    }
    return;
}

void Level::astarSearch(int grid[][Environment::BOARD_WIDTH], Pair src, Pair dest)
{
        if (isValid(src.first, src.second) == false)
        {
            qDebug() << "Source is invalid\n";
            return;
        }

        if (isValid(dest.first, dest.second) == false)
        {
            qDebug() << "Destination is invalid\n";
            return;
        }

        if (isUnBlocked(grid, src.first, src.second) == false|| isUnBlocked(grid, dest.first, dest.second) == false)
        {
            qDebug() << "Source or the destination is blocked\n";
            return;
        }

        if (isDestination(src.first, src.second, dest) == true)
        {
            qDebug() << "We are already at the destination\n";
            return;
        }

        bool closedList[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];
        memset(closedList, false, sizeof(closedList));

        cell cellDetails[Environment::BOARD_HEIGHT][Environment::BOARD_WIDTH];

        int i, j;

        for (i = 0; i < Environment::BOARD_HEIGHT; i++) {
            for (j = 0; j < Environment::BOARD_WIDTH; j++) {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;

        std::set <pPair> openList;


        openList.insert(make_pair(0.0, std::make_pair(i, j)));


        bool foundDest = false;

        while (!openList.empty()) {
            pPair p = *openList.begin();


            openList.erase(openList.begin());

            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            double gNew, hNew, fNew;

            //----------- 1st Successor (North) ------------


            if (isValid(i - 1, j) == true) {

                if (isDestination(i - 1, j, dest) == true)
                {
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i - 1, j, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i - 1, j)));

                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].h = hNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }

            //----------- 2nd Successor (South) ------------

            if (isValid(i + 1, j) == true)
            {

                if (isDestination(i + 1, j, dest) == true)
                {
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }
                else if (closedList[i + 1][j] == false && isUnBlocked(grid, i + 1, j) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i + 1, j, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i + 1, j)));

                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].h = hNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }

            //----------- 3rd Successor (East) ------------

            if (isValid(i, j + 1) == true)
            {
                if (isDestination(i, j + 1, dest) == true)
                {
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i][j + 1] == false && isUnBlocked(grid, i, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j + 1, dest);
                    fNew = gNew + hNew;


                    if (cellDetails[i][j + 1].f == FLT_MAX|| cellDetails[i][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i, j + 1)));

                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].h = hNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 4th Successor (West) ------------

            if (isValid(i, j - 1) == true) {

                if (isDestination(i, j - 1, dest) == true)
                {
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i][j - 1] == false && isUnBlocked(grid, i, j - 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j - 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i, j - 1)));

                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].h = hNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 5th Successor (North-East)------------

            if (isValid(i - 1, j + 1) == true) {

                if (isDestination(i - 1, j + 1, dest) == true)
                {
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i - 1][j + 1] == false && isUnBlocked(grid, i - 1, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j + 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i - 1][j + 1].f == FLT_MAX || cellDetails[i - 1][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i - 1, j + 1)));

                        cellDetails[i - 1][j + 1].f = fNew;
                        cellDetails[i - 1][j + 1].g = gNew;
                        cellDetails[i - 1][j + 1].h = hNew;
                        cellDetails[i - 1][j + 1].parent_i = i;
                        cellDetails[i - 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 6th Successor (North-West)------------

            if (isValid(i - 1, j - 1) == true) {

                if (isDestination(i - 1, j - 1, dest) == true) {

                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i - 1][j - 1] == false && isUnBlocked(grid, i - 1, j - 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j - 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i - 1][j - 1].f == FLT_MAX || cellDetails[i - 1][j - 1].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i - 1, j - 1)));
                        cellDetails[i - 1][j - 1].f = fNew;
                        cellDetails[i - 1][j - 1].g = gNew;
                        cellDetails[i - 1][j - 1].h = hNew;
                        cellDetails[i - 1][j - 1].parent_i = i;
                        cellDetails[i - 1][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 7th Successor (South-East)------------

            if (isValid(i + 1, j + 1) == true)
            {
                if (isDestination(i + 1, j + 1, dest) == true)
                {

                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i + 1][j + 1] == false && isUnBlocked(grid, i + 1, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j + 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i + 1][j + 1].f == FLT_MAX || cellDetails[i + 1][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(fNew, std::make_pair(i + 1, j + 1)));

                        cellDetails[i + 1][j + 1].f = fNew;
                        cellDetails[i + 1][j + 1].g = gNew;
                        cellDetails[i + 1][j + 1].h = hNew;
                        cellDetails[i + 1][j + 1].parent_i = i;
                        cellDetails[i + 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 8th Successor (South-West)------------

            if (isValid(i + 1, j - 1) == true)
            {

                if (isDestination(i + 1, j - 1, dest) == true) {

                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                    qDebug() <<"The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                else if (closedList[i + 1][j - 1] == false&& isUnBlocked(grid, i + 1, j - 1)== true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j - 1, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[i + 1][j - 1].f == FLT_MAX|| cellDetails[i + 1][j - 1].f > fNew)
                {
                         openList.insert(make_pair(fNew, std::make_pair(i + 1, j - 1)));

                        cellDetails[i + 1][j - 1].f = fNew;
                        cellDetails[i + 1][j - 1].g = gNew;
                        cellDetails[i + 1][j - 1].h = hNew;
                        cellDetails[i + 1][j - 1].parent_i = i;
                        cellDetails[i + 1][j - 1].parent_j = j;
                    }
                }
            }
        }

        if (foundDest == false)
            qDebug() <<"Failed to find the Destination Cell\n";

        return;
}
void Level::move()
{
    try {
        for (int i = 0; i < enemies.size(); i++) {
            int row = enemies[i]->y;
            int column = enemies[i]->x;
            // graph
            //source send enemies location

            Pair src = std::make_pair(row, column);
            Pair dest = std::make_pair(player->getrow(),player->getcol());

            astarSearch(boardData,src,dest);

            enemies[i]->setPos(Environment::TILE_SCALE + enemies[i]->x * Environment::TILE_SCALE, Environment::TILE_SCALE + enemies[i]->y * Environment::TILE_SCALE);
            //  ---------------------------------------------------------------------------------------------------------------------------------------------------------

            Pathfinal.pop();
            Pair temp = Pathfinal.top();
            if(Pathfinal.empty()==false)
            {
                Pathfinal.pop();
                int row = temp.first;
                int col = temp.second;
                qDebug() << "still moving";
                qDebug() << "((" << row<< ","<< col<<"))";
                enemies[i]->setPos(Environment::TILE_SCALE+col*Environment::TILE_SCALE,Environment::TILE_SCALE+row*Environment::TILE_SCALE);
                enemies[i]->y = row;
                enemies[i]->x = col;
            }

            // Remove dead enemies
            if (enemies[i]->health <= 0) {
                enemies.removeAt(i);
            }
        }
    } catch (std::exception) {
        // ignored
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

    for (int i = 0; i < playerLives.size(); i++) {
        delete playerLives[i];
    }
}

