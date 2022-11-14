#include "Enemy.h"
#include "QtCore/qtimer.h"

Enemy::Enemy(QObject *parent):DynamicCircle(parent){
    this->timer = new QTimer();   // Инициализируем игровой таймер паука
    // подключаем сигнал таймера к игровому слоту паука
    connect(timer, &QTimer::timeout, this, &Enemy::slotGameTimer);
    this->timer->start(15);       // Запускаем таймер

}

Enemy::~Enemy(){}

void Enemy::FindTarget(QList<QGraphicsItem *> listOfTarget, Player *player)
{
    double minDistance = this->GetDistanceTo(static_cast<baseCircle*>(listOfTarget[0]));
    int minIndex = 0;
    for(int i = 0; i< listOfTarget.size(); ++i){
        if (this->GetDistanceTo(static_cast<baseCircle*>(listOfTarget[i])) < minDistance) {
            minDistance = this->GetDistanceTo(static_cast<baseCircle*>(listOfTarget[i]));
            minIndex = i;
        }
    }
    if ((this->r<player->getRadius()) || (minDistance < this->GetDistanceTo(player))){
        this->typeOfTarget = 'f';
        this->SetTarget(listOfTarget[minIndex]);
    } else if ((minDistance>this->GetDistanceTo(player)) && (this->r>player->getRadius())){
        this->typeOfTarget = 'p';
        this->SetTarget(player);
    }
}

void Enemy::slotGameTimer(){
    this->MoveToTarget();
    if (this->HasCollisionWith(static_cast<baseCircle*>(target))){
        if (this->typeOfTarget=='f'){
            this->setRadius(this->getRadius()+5);
            emit signalCheckItem(target);
        }
        if (this->typeOfTarget=='p') emit signalCheckGameOver();
    }
//        if(this->x() - this->getRadius() < -610){
//                this->setX(-610);       // слева
//            }
//            if(this->x() + this->getRadius() > 630-this->getRadius()){
//                this->setX(240);        // справа
//            }

//            if(this->y() - 10 < -250){
//                this->setY(-240);       // сверху
//            }
//            if(this->y() + 10 > 250){
//                this->setY(240);        // снизу
//            }
}
