#include <QApplication>

#include "qge/Game.h"
#include "qge/Map.h"
#include "qge/MapGrid.h"
#include "qge/Entity.h"
#include "qge/SpriteSheet.h"
#include "qge/AngledSprite.h"
#include "QPointF"
#include "qge/ECKeyboardMover4Directional.h"

// SPRITE AND ENTITY
qge::Entity* buildEntity(std::string entitySpritePath);
qge::AngledSprite* buildEntitySprite(qge::Entity* entity, qge::SpriteSheet spriteSheet);

qge::Entity* buildEntity()
{
    qge::Entity* entity = new qge::Entity();

    //spritesheet
    qge::SpriteSheet playerSpriteSheet(":/resources/graphics/characterSpritesheets/player-sprite.png",3,4,29,28);

    // Extract the spritesheet to the sprite
    qge::AngledSprite* entitySprite = buildEntitySprite(entity,playerSpriteSheet);

    entity->setSprite(entitySprite);

    return entity;
}

qge::AngledSprite* buildEntitySprite(qge::Entity* entity, qge::SpriteSheet spriteSheet)
{
     qge::AngledSprite* entitySprite = new qge::AngledSprite();

     std::string animationsName[] = {"walk_D", "walk_U", "walk_R", "walk_L"};
     for(int i = 0; i < spriteSheet.numYTiles(); i++) //for each angle
     {
         entitySprite->addFrames(180+(90*i) % 360,animationsName[i],spriteSheet,qge::Node(0,0+i),qge::Node(3,0+i));
     }

     return entitySprite;
}




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a map
    qge::Map* map = new qge::Map();

    // create a map grid
    qge::MapGrid* mapGrid = new qge::MapGrid();
    mapGrid->setMapAtPos(map, 0, 0);

    // create a game
    qge::Game* game = new qge::Game(mapGrid, 0, 0);
    game->launch();

    // player
     qge::Entity* player = buildEntity();

     player->setOrigin(QPointF(64,64));
     player->setPos(QPointF(300,300));
     player->sprite()->play("walk_U",1,10,3);

     map->addEntity(player);


     //player control
     qge::ECKeyboardMover4Directional* keyboardMoverController = new qge::ECKeyboardMover4Directional(player);
     keyboardMoverController->setStepSize(8);

    return a.exec();
}
