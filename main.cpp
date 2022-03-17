#include <QApplication>

#include "qge/PathGrid.h"
#include "qge/Map.h"
#include "qge/MapGrid.h"
#include "qge/Entity.h"
#include "qge/SpriteSheet.h"
#include "qge/AngledSprite.h"
#include "qge/ECKeyboardMover4Directional.h"
#include "qge/ECCameraFollower.h"
#include "qge/ECBodyThruster.h"


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

    QPixmap* mansionImage = new QPixmap(":/resources/graphics/terrain/tilemap-visual.png");
    QPixmap* walkableImage = new QPixmap(":/resources/graphics/terrain/tilemap-walkable.png");

    // Create a TerrainLayer
    qge::TerrainLayer* mansion = new qge::TerrainLayer(1,1,*mansionImage);

    // Create a pathingMap
    qge::PathingMap* pathingMap = new qge::PathingMap(100,100, 32);

    // create a map
    qge::Map* map = new qge::Map(pathingMap);
    map->addTerrainLayer(mansion);


    // Creation du pathing map
    int cellSize = 32;
    QImage image(walkableImage->toImage());
    int imageWidth = image.width();
    int imageHeight = image.height();
    int numCellsWide_ = imageWidth/cellSize;
    int numCellsLong_ = imageHeight/cellSize;

    for (int y = 0; y < imageHeight; y+=8){
        for (int x = 0; x < imageWidth; x+=8){
            int alpha = qAlpha(image.pixel(x,y));
            if (alpha >= 200)
                map->pathingMap().fill(QPointF(x,y));
        }
    }

    // create a map grid
    qge::MapGrid* mapGrid = new qge::MapGrid();
    mapGrid->setMapAtPos(map, 0, 0);

    // create a game
    qge::Game* game = new qge::Game(mapGrid, 0, 0);
    game->launch();
    map->drawPathingMap();

    // player
     qge::Entity* player = buildEntity();

     player->setOrigin(QPointF(64,64));
     player->setPos(QPointF(300,300));
     game->move(QPoint(300,300));
     player->sprite()->play("walk_U",1,10,3);


     map->addEntity(player);


     //player control
     qge::ECKeyboardMover4Directional* keyboardMoverController = new qge::ECKeyboardMover4Directional(player);
     qge::ECCameraFollower* cameraFollowerController = new qge::ECCameraFollower(player);
     player->moveBy(10,10);
     keyboardMoverController->setStepSize(30);
     player->setHealth(100);

     // -------------- Boss -------------- //
     qge:: Entity* boss = new qge::Entity();

     boss->setOrigin(QPointF(64,64));
     boss->setPos(QPointF(500,750));
     map->addEntity(boss);

     // Violent
     player->setGroup(0);
     boss->setGroup(1);

     game->diplomacyManager().setRelationship(0,1,qge::Relationship::ENEMY);

     qge::ECBodyThruster* bodyThrust = new qge::ECBodyThruster(boss);
     bodyThrust->addTargetEntity(player);
     boss->damageEnemy(player,1);
     bodyThrust->setShowFOV(true);

     for (int y = 0; y < imageHeight; y+=8){
         for (int x = 0; x < imageWidth; x+=8){
             int alpha = qAlpha(image.pixel(x,y));
             if (alpha >= 200)
                 player->map()->pathingMap().fill(QPointF(x,y));
         }
     }


    return a.exec();
}
