#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "headers/button.h"
#include "headers/level.h"

#include <QGraphicsView>
#include <QObject>

/**
 * @brief The GameWindow class
 */
class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief Default parameterized constructor.
     * Creates a new game view with sizes from the confguration and with the title given
     * @param gameTitle The game view window title
     */
    GameWindow(QString gameTitle);

    /**
     * @brief Starts the game and displays the new game view.
     * Starts with the main menu scene
     */
    void start();

private:
    bool extremeMode = false;
    /**
     * @brief The main menu scene
     */
    QGraphicsScene* mainMenuScene {};

    /**
     * @brief The levels selection scene
     */
    QGraphicsScene* levelSelectionScene {};

    QGraphicsScene* optionsScene {};

    /**
     * @brief The available levels
     */
    QList<QString> levels;

    /**
     * @brief A list of buttons for each available level
     */
    QList<Button> levelsButtons;

    /**
     * @brief The currently running level
     */
    Level* currentLevel {};

    /**
     * @brief Draws and Loads the main menu scene
     */
    void loadMainMenu();

    /**
     * @brief Gets the levels available level names.
     * Used to create a button for each level with the level name as the button text
     */
    void getAvailableLevelsNames();

    /**
     * @brief Draws and displays the game over window over the current level scene
     */
    void displayGameOverWindow();

private slots:
    /**
     * @brief Play button.
     * Loads the level selection scene
     */
    void btnPlay();

    /**
     * @brief Quit button.
     * Quits the game
     */
    void btnQuit();

    void btnOptions();

    void btnExtremeMode();

    /**
     * @brief Back button.
     * Goes back from the level selection scene to the main menu scene
     */
    void btnBack();

    /**
     * @brief Load level button.
     * Loads the scene for the selected level
     * @param levelName The selected level name
     */
    void btnLoadLevel(QString levelName = "");

    /**
     * @brief Retry level button.
     * Retries the currently selected level.
     * Shown in the game over screen
     */
    void btnRetryLevel();

    /**
     * @brief Return to menu button.
     * Returns to the level selection scene.
     * Shown in the game over screen
     */
    void btnReturnToMenu();
};

#endif // GAMEWINDOW_H
