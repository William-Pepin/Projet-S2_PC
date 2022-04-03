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
#include "qge/InventoryUser.h"
#include "qge/BatteryViewer.h"
#include "qge/HPViewer.h"


#include "ItemBattery.h"

qge::Entity *buildPlayer();
qge::AngledSprite *buildPlayerSprite(qge::Entity *entity, qge::SpriteSheet spriteSheet);
qge::Entity *buildGhost();
qge::AngledSprite *buildGhostSprite(qge::Entity *entity, qge::SpriteSheet spriteSheet);
void buildPathMap();

qge::PathingMap *PATH_MAP;

void buildPathMap(qge::PathingMap *pathingMap, QPixmap *pixMap, int cellSize)
{
    QImage image(pixMap->toImage());
    int imageWidth = image.width();
    int imageHeight = image.height();

    for (int y = 0; y < imageHeight; y += 8)
    {
        for (int x = 0; x < imageWidth; x += 8)
        {
            int alpha = qAlpha(image.pixel(x, y));
            if (alpha >= 200)
                pathingMap->fill(QPointF(x, y));
        }
    }
}

// SPRITE AND ENTITY
qge::Entity *buildPlayer()
{
    qge::Entity *entity = new qge::Entity();

    // spritesheet
    qge::SpriteSheet playerSpriteSheet(":/resources/graphics/characterSpritesheets/player-sprite.png", 3, 4, 29, 28);

    // Extract the spritesheet to the sprite
    qge::AngledSprite *entitySprite = buildPlayerSprite(entity, playerSpriteSheet);

    entity->setSprite(entitySprite);

    return entity;
}

qge::AngledSprite *buildPlayerSprite(qge::Entity *entity, qge::SpriteSheet spriteSheet)
{
    qge::AngledSprite *entitySprite = new qge::AngledSprite();

    std::string animationsName[] = {"walk_D", "walk_U", "walk_R", "walk_L"};
    for (int i = 0; i < spriteSheet.numYTiles(); i++) // for each angle
    {
        entitySprite->addFrames(180 + (90 * i) % 360, animationsName[i], spriteSheet, qge::Node(0, 0 + i), qge::Node(3, 0 + i));
    }

    return entitySprite;
}

qge::Entity *buildGhost()
{
    qge::Entity *entity = new qge::Entity();

    // spritesheet
    qge::SpriteSheet ghostSpriteSheet(":/resources/graphics/characterSpritesheets/ghost-sprite.png",4,2,32,32);

    // Extract the spritesheet to the sprite
    qge::AngledSprite *ghostSprite = buildGhostSprite(entity, ghostSpriteSheet);

    entity->setSprite(ghostSprite);

    return entity;
}

qge::AngledSprite *buildGhostSprite(qge::Entity *entity, qge::SpriteSheet spriteSheet)
{
    qge::AngledSprite *entitySprite = new qge::AngledSprite();

    for (int i = 0; i < spriteSheet.numYTiles(); i++) // for each angle
    {
        entitySprite->addFrames((180 * i) +270 % 360, "walk", spriteSheet, qge::Node(0, 0 + i), qge::Node(3, 0 + i));
    }

    return entitySprite;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a TerrainLayer
    QPixmap *mansionImage = new QPixmap(":/resources/graphics/terrain/tilemap-visual.jpg");
    qge::TerrainLayer *mansion = new qge::TerrainLayer(1, 1, *mansionImage);

    // create a map
    qge::Map *map = new qge::Map(100, 75, 32);
    map->addTerrainLayer(mansion);

    // create a map grid
    qge::MapGrid *mapGrid = new qge::MapGrid();
    mapGrid->setMapAtPos(map, 0, 0);

    // Global Path_Map
    QPixmap *walkableImage = new QPixmap(":/resources/graphics/terrain/tilemap-walkable.png");
    PATH_MAP = new qge::PathingMap(map->pathingMap());
    buildPathMap(PATH_MAP, walkableImage, 32);

    // create a game
    qge::Game *game = new qge::Game(mapGrid, 0, 0);
    game->launch();
    //map->drawPathingMap();

    // player
    qge::Entity *player = buildPlayer();

    player->setOrigin(QPointF(20, 20));
    player->moveBy(250, 250);
    player->sprite()->play("walk_U", 1, 10, 3);

    map->addEntity(player);

    // player control
    qge::ECKeyboardMover4Directional *keyboardMoverController = new qge::ECKeyboardMover4Directional(player);
    qge::ECCameraFollower *cameraFollowerController = new qge::ECCameraFollower(player);
    player->moveBy(10, 10);

    keyboardMoverController->setStepSize(16);

    // -------------- Boss -------------- //
    qge::Entity ** ghosts = new qge::Entity*[5];
    qge::ECChaser ** chasers = new qge::ECChaser*[5];
    QPointF * ghostsPositions = new QPointF[5]{QPointF(500,700), QPointF(150,1500), QPointF(1300,1500), QPointF(1600,1800), QPointF(2800,1200)};
    for(int i = 0; i < 5; i++)
    {
        ghosts[i] = buildGhost();
        map->addEntity(ghosts[i]);

        ghosts[i]->setOrigin(QPointF(20, 20));
        ghosts[i]->setPos(ghostsPositions[i]);
        ghosts[i]->sprite()->play("walk", 1, 10, 3);

        chasers[i] = new qge::ECChaser(ghosts[i]);
        chasers[i]->addChasee(player);
        chasers[i]->startChasing();
        chasers[i]->setStopDistance(10);
        chasers[i]->setShowFOV(true);

    }

    // ------------------ UI ------------------ //
    qge::BatteryViewer *battery = new qge::BatteryViewer();
    qge::HPViewer *hp = new qge::HPViewer();
    game->addGui(battery);
    game->addGui(hp);

    // -------------- Batteries -------------- //
    ItemBattery** batteries = new ItemBattery*[10];
    QPointF *batteryPositions = new QPointF[10]{QPointF(120, 536), QPointF(38, 1140), QPointF(636, 1464), QPointF(668, 984), QPointF(1300, 462),
                                                 QPointF(539.0, 142.0), QPointF(1656.0, 1270.0), QPointF(2222.0, 1656.0), QPointF(2940.0, 910.0), QPointF(2972.0, 1326.0)};
    for(int i = 0; i < 10; i++)
    {
        batteries[i] = new ItemBattery();
        batteries[i]->setPos(batteryPositions[i]);
        map->addEntity(batteries[i]);
    }

    game->launch();
    player->moveBy(10, 10);
    return a.exec();
}
