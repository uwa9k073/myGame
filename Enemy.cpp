#include "Enemy.h"


Enemy::Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent) : DynamicCircle(_xpos, _ypos, _radius, _numerOfColor, parent)
{
    //    setFlag(QGraphicsItem::ItemIsMovable);
}

Enemy::~Enemy()
{
    delete target;
}


baseCircle *Enemy::getTarget() const
{
    return target;
}

void Enemy::setTarget(baseCircle *newTarget)
{
    target = newTarget;
}

void Enemy::findTarget(QList<baseCircle *> listOfTarget)
{
    double minDistance = GetDistanceTo(listOfTarget[0]);
    int minIndex = 0;
    for (int i = 0; i < listOfTarget.size(); ++i){
        if (GetDistanceTo(listOfTarget[i])<=minDistance){
            minDistance = GetDistanceTo(listOfTarget[i]);
            minIndex = i;
        }
    }
    target = listOfTarget[minIndex];
    std::cout << target<< ' ' << minIndex << ' ' << minDistance << ' ' << target->pos().x() << ", " <<target->pos().y() <<'\n';
}

void Enemy::MoveToTarget()
{
    MoveToPoint(target);
}


