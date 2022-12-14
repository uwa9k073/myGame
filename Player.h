#ifndef PLAYER_H
#define PLAYER_H

#include <DynamicCircle.h>

class Player : public DynamicCircle
{
    Q_OBJECT
public:
    explicit Player(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent = 0);
    ~Player();
    QPointF getCursorPos() const;            // геттер позиции курсора
    void setCursorPos(QPointF newCursorPos); // сеттер позиции курсора
    void moveToCursor();                     // функция передвижения игрока к курсору
signals:
    void signalCheckEnemy(baseCircle *item); // сигнал удаления бота
private:
    QPointF cursorPos; // позиция курсора
};

#endif // PLAYER_H
