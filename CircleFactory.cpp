#include "CircleFactory.h"


CircleFactory* CircleFactory::circleFactoryPtr = nullptr;

CircleFactory *CircleFactory::getInstance()
{
    if (!circleFactoryPtr)
            circleFactoryPtr = new CircleFactory();

    return circleFactoryPtr;
}

CircleFactory::~CircleFactory()
{
    delete circleFactoryPtr;
}

baseCircle *CircleFactory::createBaseCircle(qreal _x, qreal _y, int r)
{
    return new baseCircle(_x, _y, r, 1,'f',0);
}
Player *CircleFactory::createPlayer(qreal _x, qreal _y)
{
    return new Player(_x, _y, 15, 2,'p',0);

}

Enemy *CircleFactory::createEnemy(qreal _x, qreal _y)
{
    return new Enemy(_x,_y, 15, 3,'e', 0);
}

Virus *CircleFactory::createVirus(qreal _x, qreal _y)
{
    return new Virus(_x, _y, 30, 4, 'v',0);
}
