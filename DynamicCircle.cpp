#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent) : baseCircle(_xpos, _ypos, _radius, _numerOfColor, parent)
{
}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::MoveToPoint(QPointF p)
{
    double alpha = atan2(p.y() - pos().y(), p.x() - pos().x())/M_PI;
    setRotation(alpha);
    qreal dx = speed() * cos(alpha * (M_PI / 180));
    qreal dy = speed() * sin(alpha * (M_PI / 180));
    moveBy(dx, dy);
}

void DynamicCircle::MoveToPoint(baseCircle *tmp)
{
    double alpha = atan2(tmp->pos().y() - pos().y(), tmp->pos().x() - pos().x());
//    setRotation(alpha);
    qreal dx = speed() * cos(alpha);
    qreal dy = speed() * sin(alpha);
    std::cout << "dx: "<<dx << ", dy: "<<dy<<'\n';
    moveBy(dx,dy);
}

void DynamicCircle::MoveToPoint(qreal x, qreal y)
{
    double alpha = atan2(y - Ypos, x - Xpos);
    qreal dx = 2 * cos(alpha * (M_PI / 180));
    qreal dy = 2 * sin(alpha * (M_PI / 180));
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
    return radius > tmp->getRadius();
}
