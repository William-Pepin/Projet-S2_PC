#ifndef GLOBAL_H
#define GLOBAL_H

#include "qge/PathingMap.h"
#include "qge/Entity.h"
#include "controller.h"

extern qge::PathingMap* PATH_MAP;
extern qge::Entity* FLASH_LIGHT;
extern bool IS_GRABBED;
extern bool ACC;

extern controller* CONTROLLER;

#endif // GLOBAL_H
