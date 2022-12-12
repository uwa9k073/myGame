#ifndef ENEMY_H
#define ENEMY_H

#include <DynamicCircle.h>
#include <Player.h>

class Enemy : public DynamicCircle
{
    Q_OBJECT
public:
    explicit Enemy(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent = 0); // конструктор
    ~Enemy();                                                                                                 // деструктор

    baseCircle *getTarget() const;                                     // геттер цели
    void setTarget(baseCircle *newTarget);                             // сеттер цели
    void findTarget(QList<baseCircle *> listOfTarget, Player *player); // функция находящая цель
    void MoveToTarget();                                               // функция передвижения к цели

private:
    baseCircle *target; // цель
};
#endif // ENEMY_H
