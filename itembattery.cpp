#include "itembattery.h"
#include "qge/Sprite.h"
#include "qge/TopDownSprite.h"

ItemBattery::ItemBattery()
{
    // set sprite
    qge::TopDownSprite* sprite = new qge::TopDownSprite(QPixmap(":/resources/graphics/misc/battery.png"));
    setSprite(sprite);
    setDescription("A AA Battery. Can provide energy for a flashlight.");
}

void ItemBattery::use_()
{
    // does nothing
}
