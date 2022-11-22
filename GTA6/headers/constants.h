#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QBrush>
#include <QCoreApplication>
#include <QDir>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QString>


namespace Resources {
    // resources directory is copied to the build folder using qmake commands
    // WINDOWS: QDir::currentPath() + "\\resources\\XXX
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

    /**
     * @brief The directory of ui elements files
     */
    const QString UI_DIR = QDir::currentPath() + "\\resources\\ui\\";
}

namespace Environment {
    /**
     * @brief The screen width
     */
    const int SCREEN_WIDTH = 1600; // 1280

    /**
     * @brief The screen height
     */
    const int SCREEN_HEIGHT = 900; // 720

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
    const int TILE_SCALE = 65;

    /**
     * @brief The powerpellet number code in the text file
     */
    const int POWERPELLET_CODE = 99;

    /**
     * @brief The enemy number code in the text file
     */
    const int ENEMY_CODE = 98;

    /**
     * @brief The weapon number code in the text file
     */
    const int WEAPON_CODE = 97;

    /**
     * @brief The exterior number code in the text file
     */
    const int EXTERIOR_CODE = -1;

    /**
     * @brief The bookshelf number code in the text file
     */
    const int BOOKSHELF_CODE = -2;

    /**
     * @brief The box number code in the text file
     */
    const int BOX_CODE = -4;

    /**
     * @brief The bricks 2 number code in the text file
     */
    const int BRICKS2_CODE = -5;

    /**
     * @brief The room number code in the text file
     */
    const int ROOM_CODE = 04;
}

class UI {
public:
    /**
     * @brief Draws a panel with the given properties on top of a scene
     * @param scene The scene to draw the panel in
     * @param x The x start coordinate of the panel
     * @param y The y start coordinate of the panel
     * @param width The width of the panel
     * @param height The height of the panel
     * @param color The color of the panel
     * @param opacity The opacity of the panel
     */
    static void drawPanel(QGraphicsScene* scene, int x, int y, int width, int height, QColor color, double opacity){
        // draws a panel at the specified location with the specified properties
        QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        panel->setBrush(brush);
        panel->setOpacity(opacity);
        scene->addItem(panel);
    }

    /**
     * @brief Delays a UI component / function by n millisecond
     * @param n The delay time in milliseconds
     */
    static void delay(int n)
    {
        QTime dieTime= QTime::currentTime().addMSecs(n);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
};

/**
 * @brief Gets the string type name of the given object.
 * Used to avoid unintended side effects of using typeid(obj)
 * @param obj The object to get the string type name of
 * @return String type name of the given object
 */
template <typename T> char const* str_type( T const& obj ) { return typeid( obj ).name(); }

#endif // CONSTANTS_H
