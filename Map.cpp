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
    connect(player, &Player::signalCheckItem, this, &Map::slotDeleteFood);
    connect(enemy, &Enemy::signalCheckItem, this, &Map::slotDeleteFood);

}

char Map::getWhoWin() const
{
    return whoWin;
}
// end constructor

// Map destructor
Map::~Map()
{
    delete timer; // delete timer pointer

    delete mapPtr; // delete mapPtr pointer
}
// end destructor

// getInstance return a pointer to Map's object
Map* Map::getInstance()
{
    // if there is no map, creates one
    if (!mapPtr)
        mapPtr = new Map();

    return mapPtr;
}
// end getInstance function

// overloading advance function of QGraphicsScene for handle animation
void Map::advance()
{
//    movePlayer(player->getCursorVector().x(), player->getCursorVector().y());
//    moveEnemy(enemy->getTarget());
    for(int i = 0; i < foodList.size(); ++i){
        if (foodList[i]->HasCollisionWith(player)){
            updatePlayer(foodList[i]->getRadius(), foodList[i]->getScore());
            emit player->signalCheckItem(foodList[i]);
        }
        if (foodList[i]->HasCollisionWith(enemy)){
            updateEnemy(foodList[i]->getRadius(), foodList[i]->getScore());
            emit enemy->signalCheckItem(foodList[i]);
        }
        if (player->HasCollisionWith(enemy)){
            if(player->getRadius()>=enemy->getRadius()){
                whoWin = 'p';
            } else{
                whoWin = 'e';
            }
        }
    }

    getInstance()->update(); // update scene after timeout signal emits
}
//end advance function


void Map::gameFinished()
{
    timer->stop();
    timerCreateFood->stop();
    disconnect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    disconnect(timer, &QTimer::timeout, this, &Map::advance);

    enemy->deleteLater();
    player->deleteLater();
}

void Map::slotCreateFood()
{
    getNewFood(randomBetween(0,100),randomBetween(0,100));
}

void Map::slotDeleteFood(QGraphicsEllipseItem *item)
{
    foreach(QGraphicsEllipseItem *el, foodList){
        if (el==item){
            this->removeItem(el);
            foodList.removeOne(el);
            delete el;
        }
    }

}

void Map::gameStart()
{
    player = new Player();
    player->setRadius(30);
    player->setNumerOfColor(2);
    addItem(player);
    player->setPos(100.0, 100.0);


    // initialize timer
    timer = new QTimer(); // create an object from QTimer class
    connect( timer, &QTimer::timeout, this, &Map::advance); // connect timeout() to advance()
    timer -> start( FRAME_MS ); // emit the timeout() signal at FRAME_MS constant

    timerCreateFood = new QTimer();
    connect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);
    timerCreateFood->start(FRAME_MS);

}

// mouseMoveEvent handle mouse movement event
void Map::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    // take mouse x and y position
    player->mouseMove(event->scenePos().x() / VIEW_SCALE, event->scenePos().y() / VIEW_SCALE);

}
// end mouseMoveEvent

// update bot position
void Map::moveEnemy(QGraphicsEllipseItem* tmp)
{
            enemy->setXpos(tmp->x());
            enemy->setYpos(tmp->y());
            enemy->setPos( enemy->getXpos(), enemy->getYpos());
}

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

// update player that eject food
//void Map::playerEjectFood(QString id)
//{
//    for(int i = 0; i < playerList.size(); i++)
//    {
//        if( playerList[i]->getName() == id )
//        {
//            playerList[i]->score_ -= 12; // 9 is radius of ejected food
//            playerList[i]->radius_ =( ( playerList[i]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

//            break;
//        }
//    }
//}

// remove eaten ejected food
//void Map::removeEjectedFood(QString x , QString y)
//{
//    for( int k = 0; k < ejectedFoodList.size(); k++ )
//    {
//        if( ejectedFoodList[k]->getYPosition() == y.toDouble() && ejectedFoodList[k]->getXPosition() == x.toDouble())
//        {
//            removeItem(ejectedFoodList[k]);
//            ejectedFoodList.removeOne(ejectedFoodList[k]);
//        }
//    }
//}

// update bot radius and score
void Map::updateEnemy(qreal r, int ds)
{
            enemy->setScore(enemy->getScore() + ds);
            enemy->setRadius(enemy->getRadius() + r);
}

void Map::updateEnemyTarget()
{
    double minDistance = enemy->GetDistanceTo(foodList[0]);
    int minIndex = 0;
    for (int i = 0; i < foodList.size(); ++i){
        if (enemy->GetDistanceTo(foodList[i])<minDistance){
            minDistance = enemy->GetDistanceTo(foodList[i]);
            minIndex = i;
        }
    }
    if (minDistance<enemy->GetDistanceTo(player)){
        enemy->setTarget(foodList[minIndex]);
    } else{
        enemy->setTarget(player);
    }
}

// getNewFood add more food to map
void Map::getNewFood( qreal x, qreal y)
{
    baseCircle* food = CircleFactory::getInstance() -> createBaseCircle(x, y); // creates an object from food class
    addItem( food ); // add food item to scene
    foodList.append( food ); // add food item to foodList
}


// end getNewFood

//// add new virus to scene
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
