#ifndef VIRUS_H
#define VIRUS_H

#include <baseCircle.h>

class Virus: public baseCircle{
    Q_OBJECT
public:
    explicit Virus(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, QObject *parent = 0);
    ~Virus();
signals:
    void punish(baseCircle* item);
};
#endif // VIRUS_H
