#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

#include "Player.h"
#include "Enemy.h"
#include "baseCircle.h"
#include "Virus.h"

class CircleFactory{
public:
    static CircleFactory* getInstance();
    ~CircleFactory();


    baseCircle* createBaseCircle(qreal _x, qreal _y, int r);
    Player* createPlayer(qreal _x, qreal _y);
    Enemy* createEnemy(qreal _x, qreal _y);
    Virus* createVirus(qreal _x, qreal _y);
private:
    static CircleFactory* circleFactoryPtr;
};

#endif // CIRCLEFACTORY_H
