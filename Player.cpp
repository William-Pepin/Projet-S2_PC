#include "Player.h"
#include <QKeyEvent>
#include <QDebug>

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
        setPos(x()-10,y());

    if(event->key() == Qt::Key_D)
        setPos(x()+10,y());

    if(event->key() == Qt::Key_W)
        setPos(x(),y()-10);

    if(event->key() == Qt::Key_S)
        setPos(x(),y()+10);
}
