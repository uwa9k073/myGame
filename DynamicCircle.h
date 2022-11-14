#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <baseCircle.h>


class DynamicCircle: public baseCircle{
    Q_OBJECT
public:
    explicit DynamicCircle(QObject *parent = 0);
    ~DynamicCircle();
    void Move(QPointF p);
    void MoveToPoint(QGraphicsItem *p);
    void SetTarget(QGraphicsItem *tmp);
    void MoveToTarget();
    QGraphicsItem* GetTarget();
signals:
public slots:
protected:
    QGraphicsItem *target;
};

#endif // DYNAMICCIRCLE_H
