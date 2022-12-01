#ifndef ENEMY_H
#define ENEMY_H


#include <DynamicCircle.h>

const int DISPLACEMENT = 5;


class Enemy: public DynamicCircle{
    Q_OBJECT
public:
    explicit Enemy(qreal,qreal, int,QObject *parent = 0);
    ~Enemy();
    void setTarget(QGraphicsEllipseItem *newTarget);

    QGraphicsEllipseItem *getTarget() const;

signals:
    void signalCheckItem(QGraphicsEllipseItem *item);
private:
    QGraphicsEllipseItem *target;
};
#endif // ENEMY_H
