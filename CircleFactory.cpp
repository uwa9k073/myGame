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

baseCircle *CircleFactory::createBaseCircle(qreal _x, qreal _y, int _radius, int _numerOfColor)
{
    return new baseCircle(_x, _y, _radius, _numerOfColor,0);
}
Player *CircleFactory::createPlayer(qreal _x, qreal _y, int _radius, int _numerOfColor)
{
    return new Player(_x, _y, _radius, _numerOfColor,0);

}

Enemy *CircleFactory::createEnemy(qreal _x, qreal _y,int _radius, int _numerOfColor)
{
    return new Enemy(_x,_y, _radius, _numerOfColor, 0);
}

Virus *CircleFactory::createVirus(qreal _x, qreal _y, int _radius, int _numerOfColor)
{
    return new Virus(_x, _y, _radius, _numerOfColor, 0);
}
