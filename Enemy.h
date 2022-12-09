#ifndef ENEMY_H
#define ENEMY_H

#include <DynamicCircle.h>
#include <Player.h>

class Enemy: public DynamicCircle{
    Q_OBJECT
public:
    explicit Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who,QObject *parent = 0);
    ~Enemy();


    baseCircle *getTarget() const;
    void setTarget(baseCircle *newTarget);
    void findTarget(QList<baseCircle*>,QList<Enemy*> listOfBots,Player* player);
    void MoveToTarget();

private:
    baseCircle *target;

};
#endif // ENEMY_H
