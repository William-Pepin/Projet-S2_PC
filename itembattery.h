#ifndef ITEMBATTERY_H
#define ITEMBATTERY_H

#include "qge/NoTargetItem.h"
#include "QTimer"

class ItemBattery : public qge::Entity
{
    Q_OBJECT
public:
    ItemBattery();
    ItemBattery(Entity *player, int position);
    ~ItemBattery();

public slots:
    void use_();

signals:
    void BatteryColision();

private:
    int position;
};

#endif // ITEMBATTERY_H
