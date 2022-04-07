#include "grabbedviewer.h"
#include "ScrollWindow.h"



using namespace qge;

/// Creates a default InventoryViewer which visualizes the specified Inventory.
GrabbedViewer::GrabbedViewer(gestionnaireGrabber *grabber):
    border_(15),
    scrollWindow_(new ScrollWindow(530,330))
{
    // defaults
    height = 50;
    width = 80;


    this->setGuiPos(QPointF(360,200));
    scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/notgrab.png"));
    connect(grabber, &gestionnaireGrabber::Grab , this, &GrabbedViewer::draw_);
}

QGraphicsItem *GrabbedViewer::getGraphicsItem()
{
    return scrollWindow_->getGraphicsItem();
}


/// Sets the background of the InventoryViewer to the specified QPixmap.
/// @see InventoryViewer::setBackgroundColor(const QColor& color) for
/// more info.
void GrabbedViewer::setBackgroundPixmap(const QPixmap &pixmap)
{
    scrollWindow_->setBackgroundPixmap(pixmap);
}


/// Returns the height of the InventoryViewer.
double GrabbedViewer::getHeight()
{
    return height;
}

/// Returns the width of the InventoryViewer.
double GrabbedViewer::getWidth()
{
    return width;
}

/// Draws the Inventory based on its current states.
void GrabbedViewer::draw_()
{

    // draw background

    switch (IS_GRABBED) {
        case 0 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/notgrab.png"));
        break;

        case 1 :
        scrollWindow_->setBackgroundPixmap(QPixmap(":/resources/graphics/Grabbed/grab.png"));
        break;



    }
}

