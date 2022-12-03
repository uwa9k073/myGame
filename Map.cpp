#include "Map.h"

#include <iostream>

static qreal randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}


Map* Map::mapPtr = nullptr;

// Map Constructor
Map::Map()
{
    timerCreateFood = new QTimer();
    connect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    foodList.append(CircleFactory::getInstance()->createBaseCircle(randomBetween(131,769),randomBetween(231,269), 10, 1));
    enemy = new Enemy(randomBetween(31,1069),randomBetween(31,569),20,3);
    addItem(enemy);
    connect(enemy, &Enemy::signalCheckItem, this, &Map::slotDeleteFood);
}

// getInstance return a pointer to Map's object
Map* Map::getInstance()
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

    delete mapPtr; // delete mapPtr pointer
}
// end destructor

void Map::gameStart()
{
//    player = new Player();
//    player->setRadius(30);
//    player->setNumerOfColor(2);
//    addItem(player);
//    player->setPos(100.0, 100.0);
//     initialize timer
//    connect(player, &Player::signalCheckItem, this, &Map::slotDeleteFood);
    timerCreateFood->start(FRAME_MS*2);
    timer = new QTimer(); // create an object from QTimer class
    connect( timer, &QTimer::timeout, this, &Map::advance); // connect timeout() to advance()
    timer -> start( FRAME_MS ); // emit the timeout() signal at FRAME_MS constant
}


void Map::gameFinished()
{
    timer->stop();
    timerCreateFood->stop();
    disconnect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    disconnect(timer, &QTimer::timeout, this, &Map::advance);

    enemy->deleteLater();
    player->deleteLater();
}

// overloading advance function of QGraphicsScene for handle animation
void Map::advance()
{
//    movePlayer(player->getCursorVector().x(), player->getCursorVector().y());
//    updateEnemyTarget();
    enemy->advance();
    for(int i = 0; i < foodList.size(); ++i){
//        if (foodList[i]->HasCollisionWith(player)){
//            updatePlayer(foodList[i]->getRadius(), foodList[i]->getScore());
//            emit player->signalCheckItem(foodList[i]);
//        }
        if (foodList[i]->HasCollisionWith(enemy)){
            updateEnemy(foodList[i]->getRadius()/2, foodList[i]->getScore()/2);
            emit enemy->signalCheckItem(foodList[i]);
        }
//        if (player->HasCollisionWith(enemy)){
//            if(player->getRadius()>=enemy->getRadius()){
//                whoWin = 'p';
//            } else{
//                whoWin = 'e';
//            }
//        }
    }

    getInstance()->update(); // update scene after timeout signal emits
}
//end advance function





void Map::slotCreateFood()
{
    getNewFood(randomBetween(31,1069),randomBetween(31,569));
}

// getNewFood add more food to map
void Map::getNewFood( qreal x, qreal y)
{
    baseCircle* food = CircleFactory::getInstance() -> createBaseCircle(x, y, 10, 1); // creates an object from food class
    addItem( food ); // add food item to scene
    foodList.append( food ); // add food item to foodList
//    if (foodList.size() == 1) enemy->setTarget(foodList[0]);
}
// end getNewFood

void Map::slotDeleteFood(QGraphicsEllipseItem *item)
{
    foreach(QGraphicsEllipseItem *el, foodList){
        if (el==item){
            this->removeItem(el);
            foodList.removeOne(el);
            delete el;
            updateEnemyTarget();
        }
    }
//    updateEnemyTarget();

}

// update bot position
void Map::moveEnemy(baseCircle* tmp)
{
            qreal dx = tmp->getXpos()-enemy->getXpos();
            qreal dy = tmp->getYpos()-enemy->getYpos();
            enemy->setPos(enemy->pos()+QPointF(dx,dy));
            enemy->setYpos(enemy->getXpos()+dx);
            enemy->setYpos(enemy->getYpos()+dy);
}
// update bot radius and score
void Map::updateEnemy(int r, int ds)
{
            enemy->setScore(enemy->getScore() + ds);
            enemy->setRadius(enemy->getRadius() + r);
}

void Map::updateEnemyTarget()
{
    if (enemy->HasCollisionWith(enemyTarget)){
    double minDistance = enemy->GetDistanceTo(foodList[0]);
    int minIndex = 0;
    for (int i = 0; i < foodList.size(); ++i){
        if (enemy->GetDistanceTo(foodList[i])<minDistance){
            minDistance = enemy->GetDistanceTo(foodList[i]);
            minIndex = i;
        }
    }/*
    if (minDistance<enemy->GetDistanceTo(player)){
        enemy->setTarget(foodList[minIndex]);
    } else{
        enemy->setTarget(player);
    }*/
    enemyTarget = foodList[minIndex];
    }
    if (enemyTarget)
    {
        enemy->setTargetPos(enemyTarget->pos());
    }
}

// mouseMoveEvent handle mouse movement event
//void Map::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
//{
//    // take mouse x and y position
//    player->mouseMove(event->scenePos().x() / VIEW_SCALE, event->scenePos().y() / VIEW_SCALE);

//}
// end mouseMoveEvent

// update player position
void Map::movePlayer(qreal x , qreal y)
{
            player->setXpos(x);
            player->setYpos(y);

            player->setPos( player->getXpos(), player->getYpos());
}

// update player radius and score
void Map::updatePlayer(qreal r, int ds)
{
    player->setScore(player->getScore()+ds);
    player->setRadius(player->getRadius()+r);
}


//getter to gameFinish
char Map::getWhoWin() const
{
    return whoWin;
}


//Maybe this will be realized
// add new virus to scene
//void Map::getNewVirus( QString x, QString y)
//{
//    Virus* virus = CellsFactory::getInstance() -> createVirus( x, y); // creates an object from virus class
//    addItem( virus ); // add virus item to scene
//    virusList.append( virus ); // add virus item to foodList
//}

// if food is eat remove it and add new food

// add new bot mode Player to map
//void Map::getNewBot( QString x, QString y, QString c , QString r, QString s, QString id )
//{
//    Bot* bot = CellsFactory::getInstance()->createBot( x, y, c, r, s, id ); // creates an object from bot class
//    addItem(bot); // add bot item to scene
//    botsList.append(bot); // add bot item to botList
//}
// end getNewBot

// add new player
//void Map::getNewPlayer(QString x, QString y, QString c , QString r, QString s, QString id)
//{
//    Player* player = CellsFactory::getInstance()->createPlayer( x, y, c, r, s, id ); // creates an object from player class
//    addItem(player); // add player item to scene
//    playerList.append(player); // add player item to playerList
//}

// punish bot
//void Map::botPunish(QString id)
//{
//    for(int k = 0; k < botsList.size(); k++)
//    {
//        if( botsList[k]->getName() == id )
//        {
//            botsList[k]->score_ -= 14; // 9 is radius of ejected food
//            botsList[k]->radius_ =( ( botsList[k]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

//            break;
//        }
//    }
//}

// punish player
//void Map::playerPunish(QString n)
//{
//    for(int k = 0; k < playerList.size(); k++)
//    {
//        if( playerList[k]->getName() == n )
//        {
//            playerList[k]->score_ -= 14; // 14 is punish
//            playerList[k]->radius_ =( ( playerList[k]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

//            break;
//        }
//    }
//}
