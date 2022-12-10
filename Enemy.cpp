#include "Enemy.h"


Enemy::Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) :
    DynamicCircle(_xpos, _ypos, _radius, _numerOfColor, _who, parent)
{
    //    setFlag(QGraphicsItem::ItemIsMovable);
    who = 'e';
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

void Enemy::findTarget(QList<baseCircle *> listOfTarget, Player* player)
{
    double minDistance1 = 1000000;
    int minIndex1 = 0;
    //вычисляем расстояние до статичного кружка
    for (int i = 0; i < listOfTarget.size(); ++i){
        if (listOfTarget[i]->scene()!=nullptr && this->scene()!=nullptr){
            if (GetDistanceTo(listOfTarget[i])<=minDistance1 && isBiggerThenOtherCircle(listOfTarget[i])){
                minDistance1 = GetDistanceTo(listOfTarget[i]);
                minIndex1 = i;
            }
        }
    }

    if(GetDistanceTo(player)<minDistance1 && isBiggerThenOtherCircle(player)&& player->scene()!=nullptr && this->scene()!=nullptr)
        target = player;
    else
        target = listOfTarget[minIndex1];

}

void Enemy::MoveToTarget()
{
    if (target!=nullptr)
        MoveToPoint(target);
}


