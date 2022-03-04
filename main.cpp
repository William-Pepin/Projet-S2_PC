#include <QApplication>
#include <QGraphicsScene>
#include <Player.h>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    Player * player = new Player();
    player->setRect(0,0,100,100);
    player->setX(600);
    player->setY(400);

    // add the item to the scene
    scene->addItem(player);

    // Create rectangle for collision
    QGraphicsRectItem * wall_L = new QGraphicsRectItem();
    QGraphicsRectItem * wall_R = new QGraphicsRectItem();
    QGraphicsRectItem * wall_U = new QGraphicsRectItem();
    QGraphicsRectItem * wall_D = new QGraphicsRectItem();

    wall_L->setRect(0,0,100,800);
    wall_R->setRect(1100,0,100,800);
    wall_U->setRect(0,0,1200,100);
    wall_D->setRect(0,700,1200,100);
    wall_L->setBrush(Qt::red);
    wall_R->setBrush(Qt::red);
    wall_U->setBrush(Qt::red);
    wall_D->setBrush(Qt::red);
    scene->addItem(wall_L);
    scene->addItem(wall_R);
    scene->addItem(wall_U);
    scene->addItem(wall_D);

    // focus the item in the scene in order to make him respond to KeyPressedEvent
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add a view to visualize the scene
    QGraphicsView * view = new QGraphicsView();

    view->setFixedHeight(800);
    view->setFixedWidth(1200);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // set the scene to the view
    view->setScene(scene);

    // invisible by default
    view->show();

    return a.exec();
}
