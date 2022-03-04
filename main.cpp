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
    QGraphicsRectItem * player = new Player();
    player->setRect(0,0,100,100);

    // add the item to the scene
    scene->addItem(player);

    // focus the item in the scene in order to make him respond to KeyPressedEvent
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add a view to visualize the scene
    QGraphicsView * view = new QGraphicsView();

    // set the scene to the view
    view->setScene(scene);

    // invisible by default
    view->show();

    return a.exec();
}
