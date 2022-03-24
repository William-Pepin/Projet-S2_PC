#include "HPViewer.h"
#include "ScrollWindow.h"

using namespace qge;

/// Creates a default InventoryViewer which visualizes the specified Inventory.
HPViewer::HPViewer():
    border_(15),
    scrollWindow_(new ScrollWindow(210,65))
{
    // defaults
    height = 50;
    width = 80;


    this->setGuiPos(QPointF(1040,10));
    scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/hearts/coeur_6-6.png"));
}

QGraphicsItem *HPViewer::getGraphicsItem()
{
    return scrollWindow_->getGraphicsItem();
}


/// Sets the background of the InventoryViewer to the specified QPixmap.
/// @see InventoryViewer::setBackgroundColor(const QColor& color) for
/// more info.
void HPViewer::setBackgroundPixmap(const QPixmap &pixmap)
{
    scrollWindow_->setBackgroundPixmap(pixmap);
}


/// Returns the height of the InventoryViewer.
double HPViewer::getHeight()
{
    return height;
}

/// Returns the width of the InventoryViewer.
double HPViewer::getWidth()
{
    return width;
}

/// Draws the Inventory based on its current states.
void HPViewer::draw_()
{
    // draw background

    switch (batteryState) {
        case 0 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_0-5.png"));
        break;

        case 1 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_1-5.png"));
        break;

        case 2 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_2-5.png"));
        break;

        case 3 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_3-5.png"));
        break;

        case 4 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_4-5.png"));
        break;

        case 5 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_5-5.png"));
        break;
    }
}

