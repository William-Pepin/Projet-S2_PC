#include "itembattery.h"
#include "qge/Sprite.h"
#include "qge/TopDownSprite.h"


ItemBattery::ItemBattery()
{
    // set sprite
    qge::TopDownSprite* sprite = new qge::TopDownSprite(QPixmap(":/resources/graphics/misc/battery.png"));
    setSprite(sprite);
   //setDescription("A AA Battery. Can provide energy for a flashlight.");
}


ItemBattery::ItemBattery(Entity *player, int positionVectoriel)
{
    // set sprite
    position = positionVectoriel;
    qge::TopDownSprite* sprite = new qge::TopDownSprite(QPixmap(":/resources/graphics/misc/battery.png"));
    setSprite(sprite);
    //setDescription("A AA Battery. Can provide energy for a flashlight.");

    connect(player, &Entity::collided, this, &ItemBattery::use_);
}

ItemBattery::~ItemBattery(){

}


// Add time to the battery's timer.
//Update the UI of the battery.
//Remove the used battery.


void ItemBattery::use_()
{

  emit BatteryColision();

}
