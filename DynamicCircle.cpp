#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) :
    baseCircle(_xpos, _ypos, _radius, _numerOfColor, _who, parent) {}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::MoveToPoint(QPointF p)
{
    double alpha = atan2(p.y() - pos().y(), p.x() - pos().x());
    qreal dx = speed() * cos(alpha);
    qreal dy = speed() * sin(alpha);
    moveBy(dx, dy);
}

void DynamicCircle::MoveToPoint(baseCircle *tmp)
{
    double alpha = atan2(tmp->pos().y() - pos().y(), tmp->pos().x() - pos().x());
    qreal dx = speed() * cos(alpha);
    qreal dy = speed() * sin(alpha);
    moveBy(dx,dy);
}

double DynamicCircle::speed() const
{
    double speed = (SPEED_FACTOR * radius) + ADDITIONAL_SPEED_FACTOR;
    if (speed < MINIMUM_SPEED)
        speed = MINIMUM_SPEED;
    return speed;
}

bool DynamicCircle::isBiggerThenOtherCircle(const baseCircle *tmp)
{
    return radius > tmp->getRadius();
}
