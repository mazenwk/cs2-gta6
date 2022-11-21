#include "headers/constants.h"
#include "headers/gamewindow.h"

#include <headers/button.h>

GameWindow::GameWindow(QString gameTitle)
{
    // Set up the screen
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle(gameTitle);

    // Set the background
    QBrush brush(Qt::black);
    this->setBackgroundBrush(brush);

    // Set the scene
    mainMenuScene = new QGraphicsScene();
    mainMenuScene->setSceneRect(0 , 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);
    this->setScene(mainMenuScene);
}

void GameWindow::start()
{
    loadMainMenu();
    this->show();
}

void GameWindow::getLevels()
{
    QDir dir(Resources::LEVELS_DIR);
    for (const QFileInfo &file : dir.entryInfoList(QDir::Files))
    {
        levels.append(file.fileName());
    }
}

void GameWindow::loadMainMenu()
{
    // -------------------------- Load Cover --------------------------
    QPixmap mainMenuCover(Resources::UI_DIR + "main-menu-cover.png");
    mainMenuCover = mainMenuCover.scaledToWidth(Environment::SCREEN_WIDTH);
    mainMenuCover = mainMenuCover.scaledToHeight(Environment::SCREEN_HEIGHT);

    mainMenuScene->addItem(new QGraphicsPixmapItem(mainMenuCover));
    // ----------------------------------------------------------------

    // -------------------------- Add Buttons --------------------------
    Button* playButton = new Button(QString("Play"));
    playButton->setPos(100, 200);
    mainMenuScene->addItem(playButton);
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(play()), Qt::QueuedConnection);


    Button* optionsButton = new Button(QString("Options"));
    optionsButton->setPos(100, 300);
    mainMenuScene->addItem(optionsButton);
    //QObject::connect(optionsButton, SIGNAL(clicked()), this, SLOT(quit()), Qt::QueuedConnection);

    Button* quitButton = new Button(QString("Quit"));
    quitButton->setPos(100, 400);
    mainMenuScene->addItem(quitButton);
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()), Qt::QueuedConnection);
    // ----------------------------------------------------------------
}

void GameWindow::displayGameOverWindow()
{
    // Disable all scene items
    for (size_t i = 0, n = currentLevel->levelScene->items().size(); i < n; i++){
        currentLevel->levelScene->items()[i]->setEnabled(false);
    }

    // Pop up semi transparent panel
    UI::drawPanel(currentLevel->levelScene, 0, 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT, Qt::black, 0.65);

    // Draw panel
    UI::drawPanel(currentLevel->levelScene, 312, 184, 400, 550, Qt::lightGray, 0.75);

    // Create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410, 300);
    currentLevel->levelScene->addItem(playAgain);
    Button::connect(playAgain, SIGNAL(clicked()), this, SLOT(retryLevel()));

    // Create quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(410, 375);
    currentLevel->levelScene->addItem(quit);
    Button::connect(quit, SIGNAL(clicked()), this, SLOT(returnToMenu()));

    QGraphicsTextItem* overText = new QGraphicsTextItem("GAME OVER!");
    QFont* font = new QFont;
    overText->setPos(380, 210);
    font->setPointSize(32);
    font->setBold(true);
    overText->setFont(*font);
    overText->setDefaultTextColor(Qt::white);

    currentLevel->levelScene->addItem(overText);
}

void GameWindow::play()
{
    if (levelsScene != NULL) {
        this->setScene(levelsScene);
        return;
    }

    // -------------------------- Set The Scene--------------------------
    levelsScene = new QGraphicsScene();
    levelsScene->setSceneRect(0 , 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT);
    this->setScene(levelsScene);
    // ----------------------------------------------------------------

    // -------------------------- Load Cover --------------------------
    QPixmap levelsCover(Resources::UI_DIR + "main-menu-cover.png");
    levelsCover = levelsCover.scaledToWidth(Environment::SCREEN_WIDTH);
    levelsCover = levelsCover.scaledToHeight(Environment::SCREEN_HEIGHT);

    levelsScene->addItem(new QGraphicsPixmapItem(levelsCover));
    // ----------------------------------------------------------------

    // -------------------------- Add Back Button --------------------------
    Button* backButton = new Button("Back");
    backButton->setPos(25, 75);
    levelsScene->addItem(backButton);
    QObject::connect(backButton, SIGNAL(clicked()), this, SLOT(back()), Qt::QueuedConnection);
    // ----------------------------------------------------------------

    // -------------------------- Add Levels --------------------------
    getLevels();

    for (int i = 0; i < levels.size(); i++) {
        Button* levelButton = new Button(QString(levels[i]));
        levelButton->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
        levelButton->setData(0, levels[i]);
        levelButton->setPos(100, 200 + (i * 200));
        levelsScene->addItem(levelButton);
        QObject::connect(levelButton, SIGNAL(clicked()), this, SLOT(loadLevel()), Qt::QueuedConnection);
    }
    // ----------------------------------------------------------------
}

void GameWindow::quit()
{
    //scene->clear();
    this->close();
}

void GameWindow::back()
{
    this->setScene(mainMenuScene);
}

void GameWindow::loadLevel(QString levelName)
{
    currentLevel = new Level((levelName == "" ? levelsScene->focusItem()->data(0).toString() : levelName));
    this->setScene(currentLevel->levelScene);
    currentLevel->watch();
    displayGameOverWindow();
}

void GameWindow::retryLevel()
{
    loadLevel(currentLevel->name);
}

void GameWindow::returnToMenu()
{
    this->setScene(levelsScene);
    delete currentLevel;
}
