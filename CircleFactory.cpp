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

baseCircle *CircleFactory::createBaseCircle(qreal _x, qreal _y)
{
    baseCircle* tmp = new baseCircle;
    tmp->setXpos(_x);
    tmp->setYpos(_y);
    return tmp;

}

Player *CircleFactory::createPlayer(qreal _x, qreal _y)
{
    Player* tmp = new Player;
    tmp->setXpos(_x);
    tmp->setYpos(_y);
    return tmp;
}

Enemy *CircleFactory::createEnemy(qreal _x, qreal _y)
{
    return new Enemy(_x,_y,0);
}
