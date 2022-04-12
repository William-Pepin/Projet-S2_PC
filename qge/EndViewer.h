#ifndef ENDVIEWER_H
#define ENDVIEWER_H

#pragma once


#include "Gui.h"
#include "Inventory.h"
#include "ScrollWindow.h"
#include "Entity.h"
#include "Global.h"
#include "ECKeyboardMover4Directional.h"

class QPointF;

namespace qge{

class ItemCell;
class Item;
class ScrollWindow;

/// Represents a GUI element that visualizes and allows mouse interaction with
/// an Inventory. When an item in the inventory viewer is clicked, the
/// InventoryViewer emits a signal.
class EndViewer : public Gui
{
   Q_OBJECT
public:
   EndViewer(ECKeyboardMover4Directional *keyboardMoverController);

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


#endif // ENDVIEWER_H
