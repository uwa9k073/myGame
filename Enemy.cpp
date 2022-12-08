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

void Enemy::findTarget(QList<baseCircle *> listOfTarget/* QList<Enemy*> listOfBots*/, Player* player)
{
    double minDistance1 = GetDistanceTo(listOfTarget[0]) , minDistance2 = GetDistanceTo(player);
    int minIndex1 = 0;

    //вычисляем расстояние до статичного кружка
    for (int i = 0; i < listOfTarget.size(); ++i){
        if (GetDistanceTo(listOfTarget[i])<=minDistance1 && isBiggerThenOtherCircle(listOfTarget[i])){
            minDistance1 = GetDistanceTo(listOfTarget[i]);
            minIndex1 = i;
        }
    }

    //вычисялем расстояние до бота
//    for (int i = 0; i < listOfBots.size(); ++i){
//        if (this!=listOfBots[i]){
//            if (GetDistanceTo(listOfBots[i])<=minDistance2){
//                minDistance2 = GetDistanceTo(listOfBots[i]);
//                minIndex2 = i;
//            }
//        }
//    }

    if (minDistance1>minDistance2 && isBiggerThenOtherCircle(player))
        target = player;
    else
        target = listOfTarget[minIndex1];
}

void Enemy::MoveToTarget()
{
    MoveToPoint(target);
}


