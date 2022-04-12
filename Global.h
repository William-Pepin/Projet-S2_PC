#ifndef GLOBAL_H
#define GLOBAL_H

#include "qge/PathingMap.h"
#include "qge/Entity.h"
#include "qge/ECRotater.h"
#include "controller.h"
#include "lightsource.h"
#include "gestionnairebattery.h"

extern qge::PathingMap* PATH_MAP;
extern qge::Entity* FLASH_LIGHT;
extern qge::ECRotater* FLASH_LIGHT_ROTATER;

extern LightSource* LIGHT_SOURCE;
extern controller* CONTROLLER;
extern GestionnaireBattery* GESTIONNAIRE_BATTERIE;

extern bool interact;
extern bool IS_PAUSED;
extern bool IS_GRABBED;
extern bool ACC;
extern bool IS_END;

#endif // GLOBAL_H
