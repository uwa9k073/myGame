#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent) : baseCircle(_xpos, _ypos, _radius, _numerOfColor,parent) {

}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::MoveToPoint(QPointF p)
{
//    setXpos(p.x());
//    setYpos(p.y());
//    this->setPos(Xpos, Ypos);
    double alpha = atan2(p.y() - Ypos, p.x()-Xpos);
    double dx = speed() * cos(alpha* (M_PI/180));
    double dy = speed() * sin(alpha* (M_PI/180));
    moveBy(dx, dy);
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
