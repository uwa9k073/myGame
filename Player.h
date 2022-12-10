#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <DynamicCircle.h>

const int DISPLACEMENT_X = 11;
const int DISPLACEMENT_Y = 4;




class Player: public DynamicCircle{
    Q_OBJECT
public:
    explicit Player(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who,QObject *parent = 0);
    ~Player();

    //    QPointF getCursorVector() const;
    QPointF getCursorPos() const;
    void setCursorPos(QPointF newCursorPos);
    void moveToCursor();
signals:

public slots:
//   void slotGameTimer(); /// Слот, который отвечает за обработку перемещения треугольника
private:
   QPointF cursorPos;
};

#endif // PLAYER_H
