#include "BatteryViewer.h"
#include "Inventory.h"
#include "ItemCell.h"
#include "Item.h"
#include "ScrollWindow.h"

using namespace qge;

/// Creates a default InventoryViewer which visualizes the specified Inventory.
BatteryViewer::BatteryViewer():
    border_(15),
    scrollWindow_(new ScrollWindow())
{
    // defaults
    scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/battery/battery_0-5.png"));
}

QGraphicsItem *BatteryViewer::getGraphicsItem()
{
    return scrollWindow_->getGraphicsItem();
}


/// Sets the background of the InventoryViewer to the specified QPixmap.
/// @see InventoryViewer::setBackgroundColor(const QColor& color) for
/// more info.
void BatteryViewer::setBackgroundPixmap(const QPixmap &pixmap)
{
    scrollWindow_->setBackgroundPixmap(pixmap);
}


/// Returns the height of the InventoryViewer.
double BatteryViewer::getHeight()
{
    return height;
}

/// Returns the width of the InventoryViewer.
double BatteryViewer::getWidth()
{
    return width;
}



/// Draws the Inventory based on its current states.
void BatteryViewer::draw_()
{
    // draw background
    double bgWidth = getWidth();
    double bgHeight = getHeight();

    scrollWindow_->setWidth(bgWidth);
    scrollWindow_->setHeight(bgHeight);

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

