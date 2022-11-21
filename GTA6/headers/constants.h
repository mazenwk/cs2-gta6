#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QCoreApplication>
#include <QDir>
#include <QGraphicsRectItem>
#include <QString>
#include <QBrush>
#include <QGraphicsScene>


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
     * @brief The bullet number code in the text file
     */
    const int BULLET_CODE = 97;

    static const int ObjectName = 0;
}

class UI {
public:
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

    static void delay(int n)
    {
        QTime dieTime= QTime::currentTime().addSecs(n);
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
