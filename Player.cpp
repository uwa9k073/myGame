#include "Player.h"

Player::Player(QObject *parent): DynamicCircle(parent){}


Player::~Player(){}

void Player::slotGameTimer()
{
    this->MoveToTarget();
//    if (this->HasCollisionWith())
}

