#ifndef BASECIRCLE_H
#define BASECIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <iostream>

constexpr int BOARD_WIDTH = 1100;
constexpr int BOARD_HEIGHT = 600;

class baseCircle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit baseCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent = 0);
    ~baseCircle();

    int getRadius() const;
    void setRadius(int newRadius);

    int getNumerOfColor() const;
    void setNumerOfColor(int newNumerOfColor);

    int getScore() const;
    void setScore(int newScore);

    void updateInfo(int x);

    char getWho() const;

protected:
    QRectF boundingRect() const override;                                                            // определяет прямоугольник, в котором будет нарисован круг
    QPainterPath shape() const override;                                                             // сужает гранцы прямоугольника объекта до круга
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // функция отрисовщик
    double GetDistanceTo(baseCircle *tmp);                                                           // определяет расстояние до объекта по теореме Пифагора
    bool HasCollisionWith(baseCircle *tmp);                                                          // проверяет столкновение с объектом
    int radius, numerOfColor, score;
    char who;
};
#endif
