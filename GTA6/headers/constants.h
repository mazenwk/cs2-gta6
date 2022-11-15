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

namespace Environment {
    /**
     * @brief The screen width
     */
    const int SCREEN_WIDTH = 800;

    /**
     * @brief The screen height
     */
    const int SCREEN_HEIGHT = 800;

    /**
     * @brief The board width
     */
    const int BOARD_WIDTH = 15;

    /**
     * @brief The board height
     */
    const int BOARD_HEIGHT = 12;

    /**
     * @brief The tile scale; height & width
     */
    const int TILE_SCALE = 50;

    const int POWERPELLET_CODE = 99;
    const int ENEMY_CODE = 98;
    const int BULLET_CODE = 97;
}

template <typename T> char const* str_type( T const& obj ) { return typeid( obj ).name(); }

#endif // CONSTANTS_H
