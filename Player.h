#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <DynamicCircle.h>


class Player: public DynamicCircle{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();
signals:
    void signalCheckItem(QGraphicsItem *item);
public slots:
   void slotGameTimer(); /// Слот, который отвечает за обработку перемещения треугольника
private:

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PLAYER_H
