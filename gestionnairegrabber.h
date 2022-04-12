#ifndef GESTIONNAIREGRABBER_H
#define GESTIONNAIREGRABBER_H

#include "QObject"
#include "qge/Entity.h"
#include "QTimer"
#include "Global.h"

class gestionnaireGrabber : public QObject
{
    Q_OBJECT
public:
    gestionnaireGrabber(qge::Entity *player);

signals :
    void Grab();

public slots:
    void Grabbed(qge::Entity *player, qge::Entity *collided);
    void invicible();
    void timeoutShake();
    void timoutResetTrigger();
    void willBeGrab();

private :

    int cpt;
    bool isInvicible;
    bool canBeGrab;
    QTimer *timerInvicible;
    QTimer *timerShake;
    QTimer *timerCanBeGrab;

    QTimer *timerResetTrigger;
};

#endif // GESTIONNAIREGRABBER_H
