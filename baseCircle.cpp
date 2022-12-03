#include "baseCircle.h"

#include <iostream>

baseCircle::baseCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent) : QObject(parent), QGraphicsEllipseItem() {
    Xpos = _xpos;
    Ypos = _ypos;
    radius = _radius;
    numerOfColor = _numerOfColor;
    score = _radius;
}

baseCircle::~baseCircle() {}

double baseCircle::GetDistanceTo(baseCircle *tmp)
{
    double d_x = pow(Xpos - tmp->getXpos(), 2);
    double d_y = pow(Ypos - tmp->getYpos(), 2);
    return sqrt(d_x + d_y);
}

double baseCircle::GetDistanceTo(QPointF tmp){
    double d_x = pow(pos().x() - tmp.x(), 2);
    double d_y = pow(pos().y() - tmp.y(), 2);
    return sqrt(d_x + d_y);
}

bool baseCircle::HasCollisionWith(baseCircle *tmp)
{
    return (GetDistanceTo(tmp->pos()) <= static_cast<double>(radius + tmp->getRadius()));
}

QRectF baseCircle::boundingRect() const
{
    return QRectF( Xpos- radius, Ypos - radius,
                       QRECT_SCALE * radius, QRECT_SCALE * radius);
}

void baseCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //    if (this->nOfColor==1)painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    switch (this->numerOfColor)
    {
    case 1:
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        break;
    case 2:
        painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        break;
    case 3:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        break;
    }
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(Xpos-DISPLACEMENT-3, Ypos+DISPLACEMENT, QString::number(this->score));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int baseCircle::getScore() const
{
    return score;
}

void baseCircle::setScore(int newScore)
{
    score = newScore;
}

QPainterPath baseCircle::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void baseCircle::setYpos(qreal newYpos)
{
    Ypos = newYpos;
    setX(Ypos);
}

void baseCircle::setXpos(qreal newXpos)
{
    Xpos = newXpos;
    setX(Xpos);
}

int baseCircle::getNumerOfColor() const
{
    return numerOfColor;
}

void baseCircle::setNumerOfColor(int newNumerOfColor)
{
    numerOfColor = newNumerOfColor;
}

//QPainterPath baseCircle::shape() const
//{
//    QPainterPath path; // create an object of QPainterPath
//    path.addEllipse( boundingRect() ); // add an ellipse to this object via given boundary and size
//    return path; // return the object
//}

int baseCircle::getRadius() const
{
    return radius;
}

void baseCircle::setRadius(int newRadius)
{
    radius = newRadius;
}

qreal baseCircle::getYpos() const
{
    return Ypos;
}

qreal baseCircle::getXpos() const
{
    return Xpos;
}
