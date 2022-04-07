#include "itembattery.h"
#include "qge/Map.h"



ItemBattery::ItemBattery()
{
    // set sprite
    qge::TopDownSprite* sprite = new qge::TopDownSprite(QPixmap(":/resources/graphics/misc/battery.png"));
    setSprite(sprite);
   //setDescription("A AA Battery. Can provide energy for a flashlight.");
}


ItemBattery::ItemBattery(Entity *player, int position)
{
    // set sprite
    qge::TopDownSprite* sprite = new qge::TopDownSprite(QPixmap(":/resources/graphics/misc/battery.png"));
    setSprite(sprite);
    //setDescription("A AA Battery. Can provide energy for a flashlight.");

    connect(player, &Entity::collided, this, &ItemBattery::use);

    this->position = position;
    this->setGroup(5);
}

ItemBattery::~ItemBattery(){

}


// Add time to the battery's timer.
//Update the UI of the battery.
//Remove the used battery.


void ItemBattery::use(qge::Entity *player, qge::Entity *collided)
{

    if (collided->group() == 5) {
        emit BatteryColision(this->position);
        use_();
    }


}

void ItemBattery::use_()
{

}
