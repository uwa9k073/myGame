#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <DynamicCircle.h>

const int DISPLACEMENT_X = 11;
const int DISPLACEMENT_Y = 4;




class Player: public DynamicCircle{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();
    double speed() const;
    void mouseMove(qreal _x, qreal _y);
//    void setListOfCircles(const QList<QGraphicsEllipseItem *> &newListOfCircles);

    QPointF getCursorVector() const;

signals:
    void signalCheckItem(QGraphicsEllipseItem *item);
public slots:
//   void slotGameTimer(); /// Слот, который отвечает за обработку перемещения треугольника
private:
   QPointF cursorVector;
//   QList<QGraphicsEllipseItem*> listOfCircles;

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PLAYER_H
