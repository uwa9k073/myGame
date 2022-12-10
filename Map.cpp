#include "Map.h"


#include <iostream>


//getRandom func
static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}


// Map Constructor
Map::Map()
{
    for (int i = 0; i < 50; ++i){
        getNewFood(randomBetween(50, 1050), randomBetween(50, 550));
    }
    for(int i = 0; i<5; ++i)
        getNewVirus(randomBetween(50, 1050), randomBetween(50, 550));
    timerCreateFood = new QTimer();
    timer = new QTimer();

    player = new Player(300, 300,15,2,'p', 0);
}

// Map destructor
Map::~Map()
{
    delete timer; // delete timer pointer
    delete timerCreateFood;
    enemyList.erase(enemyList.cbegin(), enemyList.cend());
    delete player;
    foodList.erase(foodList.cbegin(), foodList.cend());
    virusList.erase(virusList.cbegin(), virusList.cend());
}
// end destructor

void Map::gameStart(int numOfEnemies)
{
    addItem(player);
    connect(player, &Player::signalCheckItem, this, &Map::slotDeleteFood);
    connect(player, &Player::signalCheckEnemy, this, &Map::slotDeleteEnemy);
    for (int i = 0; i<virusList.size(); ++i){
        connect(virusList[i], &Virus::punishPlayer, this, &Map::punish);
        connect(virusList[i], &Virus::punishEnemy, this, &Map::punish);
    }
    for(int i = 0; i < numOfEnemies; ++i)
        getNewEnemy(randomBetween(50, 1050), randomBetween(50, 550));
    for (int i = 0; i< enemyList.size(); ++i){
        connect(enemyList[i], &Enemy::signalCheckItem, this, &Map::slotDeleteFood);//connect signalCheckItem() to slotDeleteFood()
//        connect(enemyList[i], &Enemy::signalCheckEnemy, this, &Map::slotDeleteEnemy);//connect signalCheckEnemy() to slotDeleteEnemy()
    }
    connect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood);//connect timeout() of timerCreateFood to slotCreateFood()
    timerCreateFood->start(FRAME_MS/1000);
    connect(timer, &QTimer::timeout, this, &Map::gameSlot); // connect timeout() to advance()
    timer->start(FRAME_MS/50);
}

void Map::gameFinished()
{
    timer->stop();
    timerCreateFood->stop();
}




// overloading advance function of QGraphicsScene for handle animation
void Map::gameSlot()
{
    std::cout << "NumOfEnemies: "<<enemyList.size() <<'\n';
    player->moveToCursor();//movin player

    //find target for each enemy and chekin clollison with player
    foreach(Enemy* enemy, enemyList){
        enemy->findTarget(foodList, player);
        enemy->MoveToTarget();
        if (enemy->HasCollisionWith(player)){
            if (enemy->isBiggerThenOtherCircle(player))
                whoWin = 'e';//set value to whoWin
            else{
                updatePlayer((enemy->getRadius()/5)+1);
                emit player->signalCheckEnemy(enemy);
            }
        }
    }

    //chtcking for collison with food
    foreach(baseCircle* food, foodList){
        foreach(Enemy* enemy, enemyList){
            if (enemy->HasCollisionWith(food)&&enemy->isBiggerThenOtherCircle(food)){
                updateEnemy(enemy,(food->getRadius()/5)+1);
                emit enemy->signalCheckItem(food);
            }
        }

        if(player->HasCollisionWith(food) && player->isBiggerThenOtherCircle(food)){
            updatePlayer((food->getRadius()/5)+1);
            emit player->signalCheckItem(food);
        }
    }

    //chekin for collision with virus
    foreach(Virus* virus, virusList){
        if (virus->HasCollisionWith(player))
            emit virus->punishPlayer(player);
        foreach(Enemy* enemy, enemyList){
            if(virus->HasCollisionWith(enemy))
                emit virus->punishEnemy(enemy);
        }
    }
}
// end advance function


void Map::slotCreateFood()
{
    if (foodList.size() < 100)
        getNewFood(randomBetween(31, 1069), randomBetween(31, 569));
}

// getNewFood add more enemies to map
void Map::getNewEnemy(qreal x, qreal y)
{
    Enemy *tmp = cf.createEnemy(x, y); // creates an object from food class
    addItem(tmp);// add food item to scene
    enemyList.append(tmp);// add food item to foodList
}
// end getNewFood

// getNewFood add more food to map
void Map::getNewFood(qreal x, qreal y)
{
    baseCircle *food = cf.createBaseCircle(x, y,randomBetween(1, 15)); // creates an object from food class
    addItem(food);// add food item to scene
    foodList.append(food);// add food item to foodList
}
// end getNewFood

void Map::slotDeleteFood(baseCircle *item)
{
    foreach (baseCircle *el, foodList)
    {
        if (el == item && el->scene()!=nullptr)
        {
            this->removeItem(el);
            foodList.removeOne(el);
            delete el;
        }
    }
    std::cout<<"item is delete\n";
}

void Map::slotDeleteEnemy(QGraphicsEllipseItem *item)
{
    if (enemyList.size() == 1){
        whoWin='p';
    }
    else{
        foreach(Enemy* el, enemyList){
            if (el==item && el->scene()!=nullptr){
                disconnect(el, &Enemy::signalCheckItem, this, &Map::slotDeleteFood);
                this->removeItem(el);
                enemyList.removeOne(el);
                delete el;
                std::cout<<"Enemy is delete\n";
            }
        }
    }

}

// update bot radius and score
void Map::updateEnemy(Enemy* item, int x)
{
    if (item->getScore()+1>220){
        whoWin = 'e';
    }else {
        item->updateInfo(x);
    }
}
// mouseMoveEvent handle mouse movement event
 void Map::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    // take mouse x and y position
    player->setCursorPos(event->scenePos());

}
// end mouseMoveEvent

// update player radius and score
void Map::updatePlayer(int x)
{
    if(player->getScore()+1>220)
        whoWin = 'p';
    else
        player->updateInfo(x);
}

// getter to gameFinish
char Map::getWhoWin() const
{
    return whoWin;
}

//  add new virus to scene
 void Map::getNewVirus( qreal x, qreal y)
{
     Virus* virus = cf.createVirus( x, y); // creates an object from virus class
     addItem( virus ); // add virus item to scene
     virusList.append( virus ); // add virus item to foodList
 }

 void Map::punish(baseCircle *item)
 {
     if(item->getWho()=='e'){
        if (item->getRadius()-2<=0) {
            if(enemyList.size()==1){
                whoWin='p';
            } else {
                foreach(Enemy* el, enemyList){
                    if (el==item && el->scene()!=nullptr){
                        disconnect(el, &Enemy::signalCheckItem, this, &Map::slotDeleteFood);
                        disconnect(el, &Enemy::signalCheckEnemy, this, &Map::slotDeleteEnemy);
                        this->removeItem(el);
                        enemyList.removeOne(el);
                        delete el;
                    }
                }
            }
        }else{
            item->updateInfo(-2);
        }
     }else{
         if(item->getRadius()-2<=0){
             whoWin='e';
         }else{
             item->updateInfo(-2);
         }
     }

 }

 QGraphicsEllipseItem *Map::getPlayer() const
 {
     return player;

 }
