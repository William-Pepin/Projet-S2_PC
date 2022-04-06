#include "gestionnairebattery.h"


GestionnaireBattery::GestionnaireBattery(ItemBattery batteries[])
{

    // Le timer maximum que la batterie peut avoir
    batteryTimerMax=100*milliToSec;

    // Nombre Maximum d'état (dessin) différent que la batterie peut contenir
    batteryStateMax=5;
    batteryState = batteryStateMax;

    // Représente l'intervalle
    batteryInterval = batteryTimerMax/batteryStateMax;

    //Timer avant un changement d'affichage
    intervalTimer= new QTimer();
    intervalTimer-> start(batteryInterval);

    for (int i =0; i < 10; i++) {
        connect(&batteries[i], &ItemBattery::BatteryColision, this, &GestionnaireBattery::BatteryPrise);

    }

    connect(intervalTimer, &QTimer::timeout, this, &GestionnaireBattery::intervalResponse);
}

void GestionnaireBattery::BatteryPrise()
{
    ///Si bargraph déjà plein, reset seulement timers et énergie
    if (batteryState == batteryStateMax)
    {
      intervalTimer->start(batteryInterval);   
    }
    else //On change image (émet signal)
    {
       emit ChangerUI(batteryState+1);
    }
    emit Flashdead(false);
}

GestionnaireBattery::~GestionnaireBattery()
{

}


void GestionnaireBattery::intervalResponse()
{
    if (batteryState >1)
    batteryState -= 1;
    else
    {
        batteryState -= 1;
        intervalTimer->stop();
        emit Flashdead(true);
    }
    emit ChangerUI(batteryState);
}
