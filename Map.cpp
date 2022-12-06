#include "Map.h"

#include <iostream>

static qreal randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

Map *Map::mapPtr = nullptr;

// Map Constructor
Map::Map()
{
    for (int i = 0; i < 50; ++i)
        getNewFood(randomBetween(50,1050), randomBetween(50,550));
    timerCreateFood = new QTimer();
    timer = new QTimer();
    enemy = new Enemy(randomBetween(50, 1050), randomBetween(50, 550), 5, 3);
}

// getInstance return a pointer to Map's object
Map *Map::getInstance()
{
    // if there is no map, creates one
    if (!mapPtr)
        mapPtr = new Map();

    return mapPtr;
}
// end getInstance function

// Map destructor
Map::~Map()
{
    delete timer; // delete timer pointer
    delete timerCreateFood;
    delete enemy;
    delete player;
    foodList.erase(foodList.cbegin(), foodList.cend());

    delete mapPtr; // delete mapPtr pointer
}
// end destructor

void Map::gameStart()
{

    //    connect(player, &Player::signalCheckItem, this, &Map::slotDeleteFood);
    addItem(enemy);
    connect(enemy, &Enemy::signalCheckItem, this, &Map::slotDeleteFood);
    connect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    timerCreateFood->start(FRAME_MS);
    connect(timer, &QTimer::timeout, this, &Map::gameSlot); // connect timeout() to advance()
    timer->start(FRAME_MS/10);                            // emit the timeout() signal at FRAME_MS constant
}

void Map::gameFinished()
{
    timer->stop();
    timerCreateFood->stop();
    disconnect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    disconnect(timer, &QTimer::timeout, this, &Map::advance);

    foodList.erase(foodList.cbegin(), foodList.cend());
    enemy->deleteLater();
    player->deleteLater();
}

QPointF Map::getEnemyTargetPos() const
{
    if (enemy->getTarget()!=nullptr)
        return enemy->getTarget()->pos();
    return QPointF(-1000,-1000);
}

// overloading advance function of QGraphicsScene for handle animation
void Map::gameSlot()
{
    if (foodList.size() > 0)
    {
        enemy->findTarget(foodList);
        enemy->MoveToTarget();
        QString n = QString::number(foodList.size());
        std::cout << n.toStdString() + "\n";
    }
    foreach (baseCircle *el, foodList)
    {
        if (el->HasCollisionWith(enemy))
        {
            updateEnemy(1,1);
            emit enemy->signalCheckItem(el);
        }
    }
    std::cout << "ok\n";
}
// end advance function

void Map::slotCreateFood()
{
    if (foodList.size() < 100)
        getNewFood(randomBetween(31, 1069), randomBetween(31, 569));
}

// getNewFood add more food to map
void Map::getNewFood(qreal x, qreal y)
{
    baseCircle *food = new baseCircle(x, y, 10, 1); // creates an object from food class
    addItem(food);                                  // add food item to scene
    foodList.append(food);                          // add food item to foodList
    //    if (foodList.size() == 1) enemy->setTarget(foodList[0]);
}
// end getNewFood

void Map::slotDeleteFood(QGraphicsEllipseItem *item)
{
    foreach (QGraphicsEllipseItem *el, foodList)
    {
        if (el == item)
        {
            this->removeItem(el);
            foodList.removeOne(el);
            delete el;
        }
    }
}

// update bot position
void Map::moveEnemy(baseCircle *tmp)
{
    qreal dx = tmp->getXpos() - enemy->getXpos();
    qreal dy = tmp->getYpos() - enemy->getYpos();
    enemy->setPos(enemy->pos() + QPointF(dx, dy));
    enemy->setYpos(enemy->getXpos() + dx);
    enemy->setYpos(enemy->getYpos() + dy);
}
// update bot radius and score
void Map::updateEnemy(int r, int ds)
{
    enemy->setScore(enemy->getScore() + ds);
    enemy->setRadius(enemy->getRadius() + r);
}
// mouseMoveEvent handle mouse movement event
// void Map::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
//{
//    // take mouse x and y position
//    player->mouseMove(event->scenePos().x() / VIEW_SCALE, event->scenePos().y() / VIEW_SCALE);

//}
// end mouseMoveEvent

// update player position
void Map::movePlayer(qreal x, qreal y)
{
    player->setXpos(x);
    player->setYpos(y);

    player->setPos(player->getXpos(), player->getYpos());
}

// update player radius and score
void Map::updatePlayer(qreal r, int ds)
{
    player->setScore(player->getScore() + ds);
    player->setRadius(player->getRadius() + r);
}

// getter to gameFinish
char Map::getWhoWin() const
{
    return whoWin;
}

// Maybe this will be realized
//  add new virus to scene
// void Map::getNewVirus( QString x, QString y)
//{
//     Virus* virus = CellsFactory::getInstance() -> createVirus( x, y); // creates an object from virus class
//     addItem( virus ); // add virus item to scene
//     virusList.append( virus ); // add virus item to foodList
// }
// add new player
// void Map::getNewPlayer(QString x, QString y, QString c , QString r, QString s, QString id)
//{
//    Player* player = CellsFactory::getInstance()->createPlayer( x, y, c, r, s, id ); // creates an object from player class
//    addItem(player); // add player item to scene
//    playerList.append(player); // add player item to playerList
//}
