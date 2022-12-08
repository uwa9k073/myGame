#ifndef ENEMY_H
#define ENEMY_H

#include <DynamicCircle.h>

class Enemy: public DynamicCircle{
    Q_OBJECT
public:
    explicit Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who,QObject *parent = 0);
    ~Enemy();


    baseCircle *getTarget() const;
    void setTarget(baseCircle *newTarget);
    void findTarget(QList<baseCircle*>);
    void MoveToTarget();

private:
    baseCircle *target;

};
#endif // ENEMY_H
