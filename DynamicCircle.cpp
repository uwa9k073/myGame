#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(QObject *parent) : baseCircle(parent) {}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::Move(QPointF p)
{
    setXpos(p.x());
    setYpos(p.y());
    this->setPos(Xpos, Ypos);
}

double DynamicCircle::speed() const
{
    double speed = ( SPEED_FACTOR * radius ) + ADDITIONAL_SPEED_FACTOR;
    if(speed < MINIMUM_SPEED)
        speed = MINIMUM_SPEED;
    return speed;
}

bool DynamicCircle::isBiggerThenOtherCircle(const baseCircle *tmp)
{
    return this->getRadius()>=tmp->getRadius();
}
//void DynamicCircle::MoveToPoint(QGraphicsItem *p)
//{
//    setPos(mapToParent(0, -(rand() % ((4 + 1) - 1) + 1)));
//}
//void DynamicCircle::SetTarget(QGraphicsItem *tmp)
//{
//    this->target = tmp;
//}
