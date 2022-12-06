#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent) : baseCircle(_xpos, _ypos, _radius, _numerOfColor, parent)
{
}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::MoveToPoint(QPointF p)
{
    double alpha = atan2(p.y() - Ypos, p.x() - Xpos);
    double dx = speed() * cos(alpha * (M_PI / 180));
    double dy = speed() * sin(alpha * (M_PI / 180));
    moveBy(dx, dy);
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
    return this->getRadius() > tmp->getRadius();
}
