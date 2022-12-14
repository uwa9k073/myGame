#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) : baseCircle(_xpos, _ypos, _radius, _numerOfColor, _who, parent) {}

DynamicCircle::~DynamicCircle() {}

void DynamicCircle::MoveToPoint(baseCircle *tmp)
{
    double alpha = atan2(tmp->pos().y() - pos().y(), tmp->pos().x() - pos().x()); /*вычисляем угол прямоугльного треугольника,
     гипотенуза которого является кратчайшим путем между двумя объектами*/
    qreal dx = speed() * cos(alpha);                                              // вычисляем расстояние по Ox, которое должен пройти объект
    qreal dy = speed() * sin(alpha);                                              // вычисляем расстояние по Oy, которое должен пройти объект
    moveBy(dx, dy);                                                               // двигаем объект на dx и dy
}

void DynamicCircle::MoveToPoint(QPointF p)
{
    double alpha = atan2(p.y() - pos().y(), p.x() - pos().x()); /*вычисляем угол прямоугльного треугольника,
     гипотенуза которого является кратчайшим путем между объектом и точкой*/
    qreal dx = speed() * cos(alpha);                            // вычисляем расстояние по Ox, которое должнен пройти объект
    qreal dy = speed() * sin(alpha);                            // вычисляем расстояние по Oy, которое должне пройти объект
    moveBy(dx, dy);                                             // двигаем объект на dx и dy
}

double DynamicCircle::speed() const
{
    double speed = (SPEED_FACTOR * radius) + ADDITIONAL_SPEED_FACTOR; // вычисляем скорость объекта
    if (speed < MINIMUM_SPEED)                                        // сравниваем получившуюся скорость с минимальной скоростью
        speed = MINIMUM_SPEED;
    return speed; // возвращаем скорость
}

bool DynamicCircle::isBiggerThenOtherCircle(const baseCircle *tmp)
{
    if (tmp->scene() == this->scene() && this->scene() != nullptr) // проверяем находятся ли объекты на одной сцене
        return radius >= tmp->getRadius();                         // только когда условие верно, возвращаем результат сравнения размеров
    return false;                                                  // если условие неверно, возвращаем ложь
}
