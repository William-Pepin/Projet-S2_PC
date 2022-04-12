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
    ItemBattery(Entity *player, int position);
    ~ItemBattery();
    void use_();
public slots:
    void use(qge::Entity *player, qge::Entity *collided);

signals:
    void BatteryColision(int position);

private:
    int position;
};

#endif // ITEMBATTERY_H
