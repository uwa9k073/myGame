#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <baseCircle.h>

constexpr double SPEED_FACTOR = (-1.0)/(32.0);
constexpr double MINIMUM_SPEED = 0.5;
constexpr double ADDITIONAL_SPEED_FACTOR = 2.5;


class DynamicCircle: public baseCircle{
    Q_OBJECT
public:
    explicit DynamicCircle(QObject *parent = 0);
    ~DynamicCircle();
    void Move(QPointF p);
    double speed() const;
    bool isBiggerThenOtherCircle(const baseCircle* tmp);
};

#endif // DYNAMICCIRCLE_H
