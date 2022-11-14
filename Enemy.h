#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <DynamicCircle.h>
#include <Player.h>

class Enemy: public DynamicCircle{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = 0);
    ~Enemy();
    void FindTarget(QList<QGraphicsItem *> listOfTargets, Player* player);
signals:
    void signalCheckGameOver();
    void signalCheckItem(QGraphicsItem *item);
private:
    QTimer *timer;
    char typeOfTarget;
private slots:
    void slotGameTimer();
};
#endif // ENEMY_H
