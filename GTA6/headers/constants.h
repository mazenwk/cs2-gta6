#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QString>


namespace Resources {
    // resources directory is copied to the build folder using qmake commands [19:24]
    /**
     * @brief The directory of levels text files
     */
    const QString LEVELS_DIR = QDir::currentPath() + "\\resources\\levels\\";

    /**
     * @brief The directory of tiles png files
     */
    const QString TILES_DIR = QDir::currentPath() + "\\resources\\tiles\\";

    /**
     * @brief The directory of entities png files
     */
    const QString ENTITIES_DIR = QDir::currentPath() + "\\resources\\entities\\";
}

namespace EnvironmentConstants {
    /**
     * @brief The screen width
     */
    const int SCREEN_WIDTH = 800;

    /**
     * @brief The screen height
     */
    const int SCREEN_HEIGHT = 800;

    /**
     * @brief The board size, assuming it is always a square
     */
    const int BOARD_SIZE = 15;

    /**
     * @brief The tile scale; height & width
     */
    const int TILE_SCALE = 50;
}

#endif // CONSTANTS_H
