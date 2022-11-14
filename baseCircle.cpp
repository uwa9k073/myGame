#include "baseCircle.h"

baseCircle::baseCircle(QObject *parent): QObject(parent), QGraphicsItem(){}


baseCircle::~baseCircle(){}

double baseCircle::GetDistanceTo(baseCircle *tmp)
{
    double d_x = pow(this->x() - tmp->x(), 2);
    double d_y = pow(this->y() - tmp->y(), 2);
    return sqrt(d_x+d_y);
}

bool baseCircle::HasCollisionWith(baseCircle *tmp)
{
    return (this->GetDistanceTo(tmp)<this->r+tmp->getRadius());
}

QRectF baseCircle::boundingRect() const
{
    return QRectF(-1000,-1000,1000,1000);   // Ограничиваем область, в которой лежит базовый круг/еда
}


void baseCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    if (this->nOfColor==1)painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    switch(this->nOfColor){
    case 1:
        painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        break;
    case 2:
        painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        break;
    case 3:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        break;
    }
    painter->drawEllipse(this->pos().x(),this->pos().y(),r,r);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
