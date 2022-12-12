#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H

#include <baseCircle.h>

constexpr double SPEED_FACTOR = -0.0000001;
constexpr double MINIMUM_SPEED = 0.5;
constexpr double ADDITIONAL_SPEED_FACTOR = 2.5;

class DynamicCircle : public baseCircle
{
    Q_OBJECT
public:
    explicit DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent = 0);
    ~DynamicCircle();
    bool isBiggerThenOtherCircle(const baseCircle *tmp); // функция, определяющая больще ли объект, другого объекта
protected:
    void MoveToPoint(baseCircle *tmp); // функция двигающая объект по графической сцене
    void MoveToPoint(QPointF p);       // перегруженная функция
signals:
    void signalCheckItem(baseCircle *item); // сигнал удаления
private:
    double speed() const;
};

#endif // DYNAMICCIRCLE_H
