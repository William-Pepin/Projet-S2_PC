#ifndef ITEMBATTERY_H
#define ITEMBATTERY_H

#include "qge/NoTargetItem.h"
#include "QTimer"
#include "qge/Sprite.h"
#include "qge/TopDownSprite.h"

class ItemBattery : public qge::NoTargetItem
{
    Q_OBJECT
public:
    ItemBattery();
    ItemBattery(Entity *player);
    ~ItemBattery();

public slots:
    void use_();

signals:
    void BatteryColision();

private:
    int position;
};

#endif // ITEMBATTERY_H
