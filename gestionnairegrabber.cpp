#include "gestionnairegrabber.h"
#include "QtDebug"


gestionnaireGrabber::gestionnaireGrabber(qge::Entity *player)
{
    timerInvicible = new QTimer();
    timerShake = new QTimer();
    timerCanBeGrab = new QTimer();
    timerResetTrigger =new QTimer();
    canBeGrab = false;
    isInvicible = false;
    cpt = 0;
    connect(player, &qge::Entity::collided, this, &gestionnaireGrabber::Grabbed);
    connect(timerInvicible, &QTimer::timeout, this, &gestionnaireGrabber::invicible);
    connect(timerShake, &QTimer::timeout, this, &gestionnaireGrabber::timeoutShake);
    connect(timerResetTrigger, &QTimer::timeout, this, &gestionnaireGrabber::timoutResetTrigger);
    connect(timerCanBeGrab, &QTimer::timeout, this, &gestionnaireGrabber::willBeGrab);


}

void gestionnaireGrabber::Grabbed(qge::Entity *player, qge::Entity *collided)
{
    if(collided->group() == 666 && isInvicible == false && !timerCanBeGrab->isActive())
    {
        timerCanBeGrab->start(1000);


    }

    if(collided->group() == 666 && isInvicible == false && canBeGrab == true)
    {

        timerInvicible->start(5000);
        player->setHealth(player->health()-1);
        timerShake->start(10);
        IS_GRABBED = true;
        isInvicible = true;
        canBeGrab=false;
    }
}

void gestionnaireGrabber::invicible()
{
    qDebug() << "invicible";
    isInvicible = false;
}

void gestionnaireGrabber::timeoutShake()
{
    qDebug() << "timeoutShake";
    if(ACC == true && IS_GRABBED)
    {
        timerShake->stop();
        IS_GRABBED = false;
        ACC = false;
    }else
    {
        timerShake->start(10);
    }

}


void gestionnaireGrabber::timoutResetTrigger()
{
    canBeGrab=false;
}

void gestionnaireGrabber::willBeGrab()
{
    canBeGrab = true;
}
