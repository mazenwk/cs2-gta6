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

namespace Constants {
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 600;
    const int BOARD_SIZE = 10;
    const int TILE_SCALE = 50;
}

#endif // CONSTANTS_H
