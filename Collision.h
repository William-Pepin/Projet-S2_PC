#ifndef COLLISION_H
#define COLLISION_H

#include <QGraphicsRectItem>
#include "qge/ECKeyboardMover4Directional.h"

class Collision: public qge::ECKeyboardMover4Directional
{
private:
    bool canGoLeft;
    bool canGoRight;
    bool canGoUp;
    bool canGoDown;
public:
    void moveStep_();
};

#endif // COLLISION_H
