#include "Enemy.h"

Enemy::Enemy(qreal x, qreal y, int r, QObject *parent):DynamicCircle(parent){
    setXpos(x);
    setYpos(y);
    setRadius(r);
    setNumerOfColor(3);
}

Enemy::~Enemy(){
    delete target;
}

void Enemy::setTarget(QGraphicsEllipseItem *newTarget)
{
    target = newTarget;
}

QGraphicsEllipseItem *Enemy::getTarget() const
{
    return target;
}
