#include "Player.h"
#include <QKeyEvent>
#include <QDebug>

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A && x() > 100)
        setPos(x()-10,y());

    if(event->key() == Qt::Key_D && x() < 1000)
        setPos(x()+10,y());

    if(event->key() == Qt::Key_W && y() > 100)
        setPos(x(),y()-10);

    if(event->key() == Qt::Key_S && y() < 600)
        setPos(x(),y()+10);
    qDebug() << "Y: " << y() << " X: " << x();
}
