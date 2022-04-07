#ifndef GESTIONNAIREBATTERY_H
#define GESTIONNAIREBATTERY_H


#include "itembattery.h"
#include "QObject"
#include "QTimer"
#include "qge/Map.h"


class GestionnaireBattery : public  QObject
{
    Q_OBJECT
public:
   GestionnaireBattery(ItemBattery *batteries[10]);
   ~GestionnaireBattery();
    void add(ItemBattery *batteries);
    QTimer * getIntervalTimer();
    int getBatteryState();

signals:
   void ChangerUI(int state);
   void Flashdead(bool state);

public slots:
    void BatteryPrise(int position);

    void intervalResponse();


private:
    ItemBattery *battery[10];
    int pos;
    //Fait la conversion entre millisecondes et secondes
    const int milliToSec = 1000;

    // Le timer maximum que la batterie peut avoir
    int batteryTimerMax;

    //Batterie initiale de la flashlight
    QTimer *batteryTimer;

    //Timer avant un changement d'affichage
    QTimer *intervalTimer;

    //float BatteryTimer=BatteryTimerMax;

    // Nombre Maximum d'état (dessin) différent que la batterie peut contenir
    int batteryStateMax;

    //State initial de la batterie
    int batteryState;

    // Représente l'intervalle
    int batteryInterval;


};

#endif // GESTIONNAIREBATTERY_H
