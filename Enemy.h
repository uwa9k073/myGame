#ifndef ENEMY_H
#define ENEMY_H

#include <DynamicCircle.h>

class Enemy: public DynamicCircle{
    Q_OBJECT
public:
    explicit Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor,QObject *parent = 0);
    ~Enemy();


signals:
    void signalCheckItem(QGraphicsEllipseItem *item);
private:
    QPointF targetPos;
public:
    virtual void advance(int phase = 1);
    QPointF getTargetPos() const;
    void setTargetPos(QPointF newTargetPos);
};
#endif // ENEMY_H
