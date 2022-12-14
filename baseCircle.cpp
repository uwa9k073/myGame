#include "baseCircle.h"

#include <iostream>

baseCircle::baseCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) : QObject(parent), QGraphicsEllipseItem()
{

    radius = _radius;
    numerOfColor = _numerOfColor;
    score = _radius;
    setPos(_xpos, _ypos);
    who = _who;
}

baseCircle::~baseCircle()
{
}

double baseCircle::GetDistanceTo(baseCircle *tmp)
{
    if (tmp->scene() != nullptr && this->scene() != nullptr)
    {
        double d_x = pow(pos().x() - tmp->pos().x(), 2);
        double d_y = pow(pos().y() - tmp->pos().y(), 2);
        return sqrt(d_x + d_y);
    }
    return 1000000;
}

char baseCircle::getWho() const
{
    return who;
}

bool baseCircle::HasCollisionWith(baseCircle *tmp)
{
    if (this->scene() != nullptr && tmp->scene() != nullptr)
        return ((GetDistanceTo(tmp)) <= (radius + tmp->getRadius()));
    return false;
}

QRectF baseCircle::boundingRect() const
{
    return QRectF(-radius, -radius,
                  2 * radius, 2 * radius);
}

void baseCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (this->numerOfColor)//выбираем цвет заливки
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
    painter->drawPath(shape());//рисуем круг
    if (who == 'p' || who == 'e')
    {
        painter->setPen(Qt::black);
        painter->drawText(-8, 5, QString::number(this->score));//рисуем счет
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);//уведомляем о том, что этот параметр не был использован
}

void baseCircle::updateInfo(int x)
{
    radius += x;
    score += x;
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
