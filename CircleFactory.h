#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

#include "Player.h"
#include "Enemy.h"
#include "baseCircle.h"


class CircleFactory{
public:
    static CircleFactory* getInstance();
    ~CircleFactory();


    baseCircle* createBaseCircle(qreal _x, qreal _y, int _radius, int _numerOfColor);
    Player* createPlayer(qreal _x, qreal _y, int _radius, int _numerOfColor);
    Enemy* createEnemy(qreal _x, qreal _y, int _radius, int _numerOfColor);
private:
    static CircleFactory* circleFactoryPtr;
};

#endif // CIRCLEFACTORY_H
