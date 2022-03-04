#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    QGraphicsRectItem * player = new QGraphicsRectItem();
    player->setRect(0,0,100,100);

    // add the item
    scene->addItem(player);

    // add a view to visualize the scene
    QGraphicsView * view = new QGraphicsView();

    // set the scene to the view
    view->setScene(scene);

    // invisible by default
    view->show();

    return a.exec();
}
