#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <baseCircle.h>

constexpr double SPEED_FACTOR = -0.01;
constexpr double MINIMUM_SPEED = 0.5;
constexpr double ADDITIONAL_SPEED_FACTOR = 2.5;

class DynamicCircle : public baseCircle
{
    Q_OBJECT
public:
    explicit DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent = 0);
    ~DynamicCircle();
    void MoveToPoint(QPointF p);
    void MoveToPoint(baseCircle* tmp);
    void MoveToPoint(qreal x, qreal y);
    double speed() const;
    bool isBiggerThenOtherCircle(const baseCircle *tmp);
    void checkCollision();
signals:
    void signalCheckItem(QGraphicsEllipseItem *item);
};

#endif // DYNAMICCIRCLE_H
