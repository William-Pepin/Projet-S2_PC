#pragma once


#include "Gui.h"
#include "Inventory.h"
#include "ScrollWindow.h"
#include "Entity.h"
#include "Global.h"
#include "gestionnairegrabber.h"

class QPointF;

namespace qge{

class ItemCell;
class Item;
class ScrollWindow;

/// Represents a GUI element that visualizes and allows mouse interaction with
/// an Inventory. When an item in the inventory viewer is clicked, the
/// InventoryViewer emits a signal.
class GrabbedViewer : public Gui
{
    Q_OBJECT
public:
    GrabbedViewer(gestionnaireGrabber *grabber);

    QGraphicsItem* getGraphicsItem();

    void setBorder(double amount);
    void setBackgroundColor(const QColor& color);
    void setBackgroundPixmap(const QPixmap& pixmap);

    double getHeight();
    double getWidth();


    int getHealthState();
    int setHealthState();


public slots :
    void draw_();

private:
    double border_;
    double height;
    double width;
    double paddingBWCells_;
    int healthState;

    // cell options
    bool cellBackgroundIsColor_;
    QColor cellBackgroundColor_;
    QPixmap cellBackgroundPixmap_;

    std::unique_ptr<ScrollWindow> scrollWindow_;

};

}
