#ifndef BASECIRCLE_H
#define BASECIRCLE_H


#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class baseCircle: public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit baseCircle(QObject *parent = 0);
    ~baseCircle();
    void setRadius(int _r){r = _r;}
    void setNOfColor(int _nOfColor){nOfColor=_nOfColor;}
    int getRadius(){return r;}
    int getNColor(){return nOfColor;}
    void setPos(QPointF _p){this->pos() = _p;}
    void setPos(int _x, int _y){
        this->setX(_x);
        this->setY(_y);
    }
    double GetDistanceTo(baseCircle* tmp);
    bool HasCollisionWith(baseCircle* tmp);
signals:

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int r,nOfColor;
};
#endif
