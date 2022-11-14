#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(QObject *parent) : baseCircle(parent) {}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::Move(QPointF p)
{
    this->setX(p.x() + this->x());
    this->setY(p.y() + this->y());
}
void DynamicCircle::MoveToPoint(QGraphicsItem *p)
{
    double alpha = qAtan2(p->y() - this->y(), p->x() - this->x()) / M_PI * 180;
    double deltaX = 2 * qCos(alpha * (M_PI / 180));
    double deltaY = 2 * qSin(alpha * (M_PI / 180));
    QPointF res;
    res.setX(deltaX);
    res.setY(deltaY);
    this->Move(res);
}
void DynamicCircle::SetTarget(QGraphicsItem *tmp)
{
    this->target = tmp;
}
void DynamicCircle::MoveToTarget()
{
    this->MoveToPoint(this->target);
}
QGraphicsItem *DynamicCircle::GetTarget() { return target; }
