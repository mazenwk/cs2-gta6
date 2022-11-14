#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QString>

// resources directory is copied to the build folder using qmake commands
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

#endif // CONSTANTS_H
