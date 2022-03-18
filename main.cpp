#include <QApplication>
#include "QPointF"
#include "QPixmap"
#include "QImage"

#include "qge/Game.h"
#include "qge/TerrainLayer.h"
#include "qge/PathingMap.h"
#include "qge/PathGrid.h"
#include "qge/Map.h"
#include "qge/MapGrid.h"
#include "qge/Entity.h"
#include "qge/SpriteSheet.h"
#include "qge/AngledSprite.h"
#include "qge/ECKeyboardMover4Directional.h"
#include "qge/ECCameraFollower.h"
#include "qge/PathGrid.h"
#include "qge/ECChaser.h"

qge::Entity* buildEntity(std::string entitySpritePath);
qge::AngledSprite* buildEntitySprite(qge::Entity* entity, qge::SpriteSheet spriteSheet);
void buildPathMap();

qge::PathingMap* PATH_MAP;

void buildPathMap(qge::PathingMap* pathingMap, QPixmap* pixMap, int cellSize)
{
    QImage image(pixMap->toImage());
    int imageWidth = image.width();
    int imageHeight = image.height();

    for (int y = 0; y < imageHeight; y+=8){
        for (int x = 0; x < imageWidth; x+=8){
            int alpha = qAlpha(image.pixel(x,y));
            if (alpha >= 200)
                pathingMap->fill(QPointF(x,y));
        }
    }
}

// SPRITE AND ENTITY
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

    // Create a TerrainLayer
    QPixmap* mansionImage = new QPixmap(":/resources/graphics/terrain/tilemap-visual.png");
    qge::TerrainLayer* mansion = new qge::TerrainLayer(1,1,*mansionImage);

    // create a map
    qge::Map* map = new qge::Map(100,100,32);
    map->addTerrainLayer(mansion);

    // create a map grid
    qge::MapGrid* mapGrid = new qge::MapGrid();
    mapGrid->setMapAtPos(map, 0, 0);

    // Global Path_Map
    QPixmap* walkableImage = new QPixmap(":/resources/graphics/terrain/tilemap-walkable.png");
    PATH_MAP = new qge::PathingMap(map->pathingMap());
    buildPathMap(PATH_MAP,walkableImage,32);

    // create a game
    qge::Game* game = new qge::Game(mapGrid, 0, 0);
    game->launch();
    map->drawPathingMap();

    // player
     qge::Entity* player = buildEntity();

     player->setOrigin(QPointF(16,16));
     player->moveBy(250,250);
     player->sprite()->play("walk_U",1,10,3);

     map->addEntity(player);

     //player control
     qge::ECKeyboardMover4Directional* keyboardMoverController = new qge::ECKeyboardMover4Directional(player);
     qge::ECCameraFollower* cameraFollowerController = new qge::ECCameraFollower(player);
     player->moveBy(10,10);

     keyboardMoverController->setStepSize(16);

     // -------------- Boss -------------- //
qge:: Entity* boss = new qge::Entity();
map->addEntity(boss);

boss->setOrigin(QPointF(16,16));
boss->moveBy(500,500);

qge::ECChaser* chaser = new qge::ECChaser(boss);
chaser->addChasee(player);
chaser->startChasing();
chaser->setStopDistance(10);
chaser->setShowFOV(true);


game->launch();
     player->moveBy(10,10);
    return a.exec();
}
