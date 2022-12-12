#include "Virus.h"
Virus::Virus(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who, QObject *parent) : baseCircle(_xpos, _ypos, _radius, _numerOfColor, _who, parent) {}

Virus::~Virus() {}
