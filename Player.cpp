#include "Player.h"

Player::Player(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent): DynamicCircle(_xpos,_ypos,_radius, _numerOfColor,parent){
    setFlag(QGraphicsItem::ItemIsFocusable);
}


Player::~Player(){}



void Player::mouseMove(qreal _x, qreal _y)
{
    QPointF tmpVec = QPointF(_x - Xpos, _y - Ypos);

    qreal dx = Xpos - _x;
    qreal dy = Ypos - _y;

    double distance = sqrt(dx*dx + dy*dy);

    if (distance){
        tmpVec /= distance;
        cursorVector = tmpVec;
    }

    if ((cursorVector.x())||(cursorVector.y())){
        cursorVector /=  (sqrt( cursorVector.x() * cursorVector.x() + cursorVector.y() * cursorVector.y()));
    }

}

QPointF Player::getCursorVector() const
{
    return cursorVector;
}

//void Player::slotGameTimer()
//{
//    foreach(QGraphicsEllipseItem* item, listOfCircles){
//        if (HasCollisionWith(dynamic_cast<baseCircle*>(item)))
//            emit signalCheckItem(item);
//    }
//}

//void Player::setListOfCircles(const QList<QGraphicsEllipseItem *> &newListOfCircles)
//{
//    listOfCircles = newListOfCircles;
//}

