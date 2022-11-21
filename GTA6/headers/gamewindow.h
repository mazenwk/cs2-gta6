#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "headers/button.h"
#include "headers/constants.h"
#include "headers/level.h"

#include <QGraphicsView>
#include <QObject>

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief Default parameterized constructor.
     * Creates a new view with sizes from the confguration and with the title given
     * @param gameTitle The game view window title
     */
    GameWindow(QString gameTitle);

    void start();
private:
    /**
     * @brief The main menu scene
     */
    QGraphicsScene* mainMenuScene {};

    /**
     * @brief The levels selection scene
     */
    QGraphicsScene* levelsScene {};
    QList<Button> levelsButtons;

    QList<QString> levels;
    Level* currentLevel {};

    void getLevels();

    void loadMainMenu();

    void displayGameOverWindow();

private slots:
    void play();
    void quit();
    void back();
    void loadLevel(QString levelName = "");
    void retryLevel();
    void returnToMenu();
};

#endif // GAMEWINDOW_H
