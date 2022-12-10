#include "baseCircle.h"

#include <iostream>

baseCircle::baseCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) :
    QObject(parent), QGraphicsEllipseItem() {
//    Xpos=_xpos;
//    Ypos=_ypos;
    radius = _radius;
    numerOfColor = _numerOfColor;
    score = _radius;
    setPos(_xpos, _ypos);
    who = _who;
}

baseCircle::~baseCircle() {
}

double baseCircle::GetDistanceTo(baseCircle *tmp)
{
    if(tmp->scene()!=nullptr && this->scene()!=nullptr){
        double d_x = pow(pos().x() - tmp->pos().x(), 2);
        double d_y = pow(pos().y() - tmp->pos().y(), 2);
        return sqrt(d_x + d_y);
    }
    return 1000000;
}

double baseCircle::GetDistanceTo(QPointF tmp){
    double d_x = pow(pos().x() - tmp.x(), 2);
    double d_y = pow(pos().y() - tmp.y(), 2);
    return sqrt(d_x + d_y);
}

char baseCircle::getWho() const
{
    return who;
}

bool baseCircle::HasCollisionWith(baseCircle *tmp)
{
    if(this->scene()!=nullptr && tmp->scene()!=nullptr)
        return ((GetDistanceTo(tmp))<=(radius+tmp->getRadius()));
    return false;
}



QRectF baseCircle::boundingRect() const
{
    return QRectF( - radius, - radius,
                       QRECT_SCALE * radius, QRECT_SCALE * radius);
}

void baseCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    case 4:
        painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    }
    painter->drawEllipse(boundingRect());
    if(who=='p'||who=='e'){
        painter->setPen(Qt::black);
        painter->drawText(-DISPLACEMENT-3, DISPLACEMENT, QString::number(this->score));
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void baseCircle::updateInfo(int x)
{
    radius+=x;
    score+=x;
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
