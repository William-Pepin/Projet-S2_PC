#ifndef ITEMBATTERY_H
#define ITEMBATTERY_H

#include "qge/NoTargetItem.h"

class ItemBattery : public qge::NoTargetItem
{
public:
    ItemBattery();
    virtual void use_();
};

#endif // ITEMBATTERY_H
