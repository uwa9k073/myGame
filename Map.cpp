#include "Map.h"

// getRandom func
static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

// Map Constructor
Map::Map()
{
    for (int i = 0; i < 50; ++i)
    {
        getNewFood(randomBetween(50, 1050), randomBetween(50, 550)); // добавление еды на гшрафическую сцену
    }
    for (int i = 0; i < 5; ++i)
        getNewVirus(randomBetween(50, 1050), randomBetween(50, 550)); // добавление вирусов на графическуб сцену
    timerCreateFood = new QTimer();                                   // создание указателя на таймер
    timer = new QTimer();                                             // создание указателя на таймер

    player = cf.createPlayer(100, 100); // создание игрока
}

// Map destructor
Map::~Map()
{
    delete timer;                                          // delete timer pointer
    delete timerCreateFood;                                // delete timerCreateFood pointer
    enemyList.erase(enemyList.cbegin(), enemyList.cend()); // очиста листа указателей на ботов
    player->deleteLater();                                 // удаление указателя на игрока
    foodList.erase(foodList.cbegin(), foodList.cend());    // очиста листа указателей на еду
    virusList.erase(virusList.cbegin(), virusList.cend()); // очиста листа указателей на вирусы
}
// end destructor

void Map::gameStart(int numOfEnemies)
{
    addItem(player);                                                         // добавление игрока на графическую сцену
    connect(player, &Player::signalCheckItem, this, &Map::slotDeleteFood);   // connect signalCheckItem() to slotDeleteFood()
    connect(player, &Player::signalCheckEnemy, this, &Map::slotDeleteEnemy); // connect signalCheckEnemy() to slotDeleteEnemy()
    for (int i = 0; i < virusList.size(); ++i)
    {
        connect(virusList[i], &Virus::punishCircle, this, &Map::punish); // connect punishCircle() to punsih()
    }
    for (int i = 0; i < numOfEnemies; ++i)
        getNewEnemy(randomBetween(50, 1050), randomBetween(50, 550)); // добавление ботов
    for (int i = 0; i < enemyList.size(); ++i)
    {
        connect(enemyList[i], &Enemy::signalCheckItem, this, &Map::slotDeleteFood); // connect signalCheckItem() to slotDeleteFood()
    }
    connect(timerCreateFood, &QTimer::timeout, this, &Map::slotCreateFood); // connect timeout() of timerCreateFood to slotCreateFood()
    timerCreateFood->start(FRAME_MS / 1000);                                // старт таймера
    connect(timer, &QTimer::timeout, this, &Map::gameSlot);                 // connect timeout() to gameSlot()
    timer->start(FRAME_MS / 50);                                            // старт таймера
}

void Map::gameFinished()
{
    timer->stop();
    timerCreateFood->stop();
}

// overloading advance function of QGraphicsScene for handle animation
void Map::gameSlot()
{
    player->moveToCursor(); // movin player

    // find target for each enemy and chekin collison with player
    foreach (Enemy *enemy, enemyList)
    {
        enemy->findTarget(foodList, player); // findin target for enemy
        enemy->MoveToTarget();               // movin enemy to his target
        if (enemy->HasCollisionWith(player))
        {
            if (enemy->isBiggerThenOtherCircle(player))
                whoWin = 'e'; // set value to whoWin
            else
            {
                updatePlayer((enemy->getRadius() / 5) + 1); // updating player info
                emit player->signalCheckEnemy(enemy);
            }
        }
    }

    // checking for collison with food
    foreach (baseCircle *food, foodList)
    {
        foreach (Enemy *enemy, enemyList)
        {
            if (enemy->HasCollisionWith(food) && enemy->isBiggerThenOtherCircle(food))
            {
                updateEnemy(enemy, (food->getRadius() / 5) + 1); // updating enemy info
                emit enemy->signalCheckItem(food);
            }
        }

        if (player->HasCollisionWith(food) && player->isBiggerThenOtherCircle(food))
        {
            updatePlayer((food->getRadius() / 5) + 1); // updating player info
            emit player->signalCheckItem(food);
        }
    }

    // chekin for collision with virus
    foreach (Virus *virus, virusList)
    {
        if (virus->HasCollisionWith(player))
            emit virus->punishCircle(player); // punsih player
        foreach (Enemy *enemy, enemyList)
        {
            if (virus->HasCollisionWith(enemy))
                emit virus->punishCircle(enemy); // punish enemy
        }
        foreach (baseCircle *food, foodList)
        {
            if (virus->HasCollisionWith(food))
            {
                emit virus->punishCircle(food); // punish food
            }
        }
    }
}
// end advance function

void Map::slotCreateFood()
{
    if (foodList.size() < 100)                                       // проверяем кол-во еды на сцене
        getNewFood(randomBetween(31, 1069), randomBetween(31, 569)); // создаем новую игру
}

// getNewFood add more enemies to map
void Map::getNewEnemy(qreal x, qreal y)
{
    Enemy *tmp = cf.createEnemy(x, y); // creates an object from food class
    addItem(tmp);                      // add food item to scene
    enemyList.append(tmp);             // add food item to foodList
}
// end getNewFood

// getNewFood add more food to map
void Map::getNewFood(qreal x, qreal y)
{
    baseCircle *food = cf.createBaseCircle(x, y, randomBetween(1, 15)); // creates an object from food class
    addItem(food);                                                      // add food item to scene
    foodList.append(food);                                              // add food item to foodList
}
// end getNewFood

void Map::slotDeleteFood(baseCircle *item)
{
    foreach (baseCircle *el, foodList)
    {
        if (el == item && el->scene() == item->scene() && el->scene() == this) // проверяем соответствие сцен
        {
            this->removeItem(el);   // удаляем элемент со сцены
            foodList.removeOne(el); // удаляем элемент из списка элементов
            delete el;              // совсем удаляем
        }
    }
}

void Map::slotDeleteEnemy(baseCircle *item)
{
    if (enemyList.size() == 1)
    {
        whoWin = 'p'; // если удаляется последний элемент из списка ботов, то победа присваивается игроку
    }
    else
    {
        foreach (Enemy *el, enemyList)
        {
            if (el == item && el->scene() == item->scene() && el->scene() != nullptr)
            {                                                                        // проверяем соответствие сцен
                disconnect(el, &Enemy::signalCheckItem, this, &Map::slotDeleteFood); // отключаем signalCheckItem() от slotDeleteFood()
                this->removeItem(el);                                                // удаляем элемент со сцены
                enemyList.removeOne(el);                                             // удаляем элемент из списка элементов
                delete el;                                                           // совсем удаляем
            }
        }
    }
}

// update bot radius and score
void Map::updateEnemy(Enemy *item, int x)
{
    if (item->getScore() + 1 > 220)
    {
        whoWin = 'e'; // если бот достигает критической массы, то победа присуждается ему
    }
    else
    {
        item->updateInfo(x); // обновляем информацию бота
    }
}
// mouseMoveEvent handle mouse movement event
void Map::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // take mouse x and y position
    player->setCursorPos(event->scenePos());
}
// end mouseMoveEvent

// update player radius and score
void Map::updatePlayer(int x)
{
    if (player->getScore() + 1 > 220)
        whoWin = 'p'; // если игрок достигает критической массы, то победа присуждается ему
    else
        player->updateInfo(x); // обновляем информацию игрока
}

// getter to gameFinish
char Map::getWhoWin() const
{
    return whoWin;
}

//  add new virus to scene
void Map::getNewVirus(qreal x, qreal y)
{
    Virus *virus = cf.createVirus(x, y); // creates an object from virus class
    addItem(virus);                      // add virus item to scene
    virusList.append(virus);             // add virus item to foodList
}

void Map::punish(baseCircle *item)
{
    if (item->getWho() == 'e')
    {
        if (item->getRadius() - 2 <= 0)
        {
            if (enemyList.size() == 1)
            {
                whoWin = 'p'; // присваиваем победу игроку, если удаляем последний элемент из enemyList
            }
            else
            {
                foreach (Enemy *el, enemyList)
                {
                    if (el == item && el->scene() == item->scene() && el->scene() == this)
                    {                                                                        // проверяем соответствие тем
                        disconnect(el, &Enemy::signalCheckItem, this, &Map::slotDeleteFood); // отключаем signalCheckItem() от slotDeleteFood;
                        this->removeItem(el);                                                // удаляем элемент со сцены
                        enemyList.removeOne(el);                                             // удаляем элемент из списка
                        delete el;                                                           // удаляем элемент совсем
                    }
                }
            }
        }
        else
        {
            item->updateInfo(-2); // обновляем информацию о боте
        }
    }
    else if (item->getWho() == 'p')
    {
        if (item->getRadius() - 2 <= 0)
        {
            whoWin = 'e'; // присваивем победу ботам, если размер игрока становится не больши нуля
        }
        else
        {
            item->updateInfo(-2); // обновляем информацию игрока
        }
    }
    else
    {
        foreach (baseCircle *el, foodList)
        {
            if (el == item && el->scene() == item->scene() && el->scene() == this) // проверяем соответствие сцен
            {
                this->removeItem(el);   // удаляем элемент со сцены
                foodList.removeOne(el); // удаляем элемент из списка еды
                delete el;              // удаляем на совсем
            }
        }
    }
}

QGraphicsEllipseItem *Map::getPlayer() const
{
    return player;
}
