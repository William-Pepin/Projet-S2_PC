#include "EndViewer.h"
#include "ScrollWindow.h"
#include "Global.h"



using namespace qge;

/// Creates a default InventoryViewer which visualizes the specified Inventory.
EndViewer::EndViewer(ECKeyboardMover4Directional *keyboardMoverController):
    border_(1),
    scrollWindow_(new ScrollWindow(530,330))
{
    // defaults
    height = 50;
    width = 80;


    this->setGuiPos(QPointF(360,200));
    scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/notgrab.png"));
    scrollWindow_->showBorder(false);
    connect(keyboardMoverController, &ECKeyboardMover4Directional::end , this, &EndViewer::draw_);
}

QGraphicsItem *EndViewer::getGraphicsItem()
{
    return scrollWindow_->getGraphicsItem();
}


/// Sets the background of the InventoryViewer to the specified QPixmap.
/// @see InventoryViewer::setBackgroundColor(const QColor& color) for
/// more info.
void EndViewer::setBackgroundPixmap(const QPixmap &pixmap)
{
    scrollWindow_->setBackgroundPixmap(pixmap);
}


/// Returns the height of the InventoryViewer.
double EndViewer::getHeight()
{
    return height;
}

/// Returns the width of the InventoryViewer.
double EndViewer::getWidth()
{
    return width;
}

/// Draws the Inventory based on its current states.
void EndViewer::draw_()
{

    // draw background

    switch (IS_END) {
        case 0 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/notgrab.png"));
        break;

        case 1 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/grab.png"));
        break;



    }
}

