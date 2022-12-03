#include "Enemy.h"

Enemy::Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent):DynamicCircle(_xpos,_ypos,_radius, _numerOfColor,parent){
//    setFlag(QGraphicsItem::ItemIsMovable);

}

Enemy::~Enemy(){
}

QPointF Enemy::getTargetPos() const
{
    return targetPos;
}

void Enemy::setTargetPos(QPointF newTargetPos)
{
    targetPos = newTargetPos;
}

void Enemy::advance(int phase)
{
    if (phase){
        MoveToPoint(targetPos);
//        moveBy(target->pos().x() - pos().x(), target->pos().y()-pos().y());
//        moveBy(1,-0.1);
    }
}
