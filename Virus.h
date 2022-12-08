#ifndef VIRUS_H
#define VIRUS_H

#include <baseCircle.h>
#include <Player.h>
#include <Enemy.h>
class Virus: public baseCircle{
    Q_OBJECT
public:
    explicit Virus(qreal _xpos, qreal _ypos, int _radius, int _numerOfColor, char _who,QObject *parent = 0);
    ~Virus();
signals:
    void punishEnemy(Enemy* item);
    void punishPlayer(Player* item);
};
#endif // VIRUS_H
