#ifndef BASECIRCLE_H
#define BASECIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <iostream>
const int BOARD_WIDTH = 1100;
const int BOARD_HEIGHT = 600;
const int QRECT_SCALE = 2;
const int DISPLACEMENT = 5;

class baseCircle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit baseCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor,char _who, QObject *parent = 0);
    ~baseCircle();
    double GetDistanceTo(baseCircle *tmp);
    qreal getXpos() const;
    qreal getYpos() const;

    int getRadius() const;
    void setRadius(int newRadius);

    int getNumerOfColor() const;
    void setNumerOfColor(int newNumerOfColor);

    void setXpos(qreal newXpos);

    void setYpos(qreal newYpos);

    int getScore() const;
    void setScore(int newScore);
    bool HasCollisionWith(baseCircle*);

    void updateInfo(int x);

    char getWho() const;

signals:

public slots:

protected:
    QPainterPath shape() const override;  // return shape of the cell
    QRectF boundingRect() const override; // determine rectangle in which cell is painted in it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int radius, numerOfColor, score;
    qreal Xpos, Ypos;
    double GetDistanceTo(QPointF tmp);
    char who;
};
#endif
