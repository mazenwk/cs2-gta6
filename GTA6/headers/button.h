#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

/**
 * @brief The Button class
 */
class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    /**
     * @brief Default parameterized constructor
     * Creates a new button on the UI
     * @param text The text inside the button
     * @param parent The parent of the button
     */
    Button(QString text, QGraphicsItem* parent=NULL);

    /**
     * @brief mousePressEvent Raised when the button is clicked on
     * @param event The raised event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief hoverEnterEvent Raised when the button is hovered on
     * @param event The raised event
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /**
     * @brief hoverLeaveEvent Raised when the button is no longer hovered on
     * @param event The raised event
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    /**
     * @brief clicked Clicked signal, fired when the button is clicked on
     * The function called when clicked is connected using the QObject::connect() function
     */
    void clicked();

private:
    /**
     * @brief The text inside the button
     */
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
