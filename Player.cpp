#include "Player.h"

Player::Player(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who,QObject *parent):
    DynamicCircle(_xpos,_ypos,_radius, _numerOfColor, _who, parent){
    setFlag(QGraphicsItem::ItemIsFocusable);
}
Player::~Player(){}

QPointF Player::getCursorPos() const
{
    return cursorPos;
}

void Player::setCursorPos(QPointF newCursorPos)
{
    cursorPos = newCursorPos;
}

void Player::moveToCursor()
{
    MoveToPoint(cursorPos);
}


