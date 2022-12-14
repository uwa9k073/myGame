#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QTimer>
#include "CircleFactory.h"

constexpr int FRAME_MS = 1000; // frame millisecond constant

class Map : public QGraphicsScene
{
public:
    explicit Map();  // конструктор
    ~Map() override; // деструктор

    void getNewFood(qreal, qreal); // дбобавление новой еды

    void updateEnemy(Enemy *item, int x); // обновление иформации бота
    void getNewEnemy(qreal x, qreal y);   // добавление нового бота

    void updatePlayer(int x);            // обновления информации игрока

    void getNewVirus(qreal x, qreal y); // добавление нового вируса

    char getWhoWin() const;
    void gameStart(int numOfEnemies);        // функция начала игры
    void gameFinished();                     // функция конца игры
    QGraphicsEllipseItem *getPlayer() const;



public slots:
    void slotCreateFood();              // слот создания еды
    void slotDeleteFood(baseCircle *);  // слот удаления еды
    void slotDeleteEnemy(baseCircle *); // слот удаления ботов
    void punish(baseCircle *item); // функция нанемения урона объекту

    void gameSlot(); // слот игровой логики

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; // Events function

private:
    QTimer *timer;                // указатель хранящий основной игровой таймер
    QTimer *timerCreateFood;      // указатель хранящий таймер создания игры
    QList<baseCircle *> foodList; // лист указателей на еду
    QList<Virus *> virusList;     // лист указателей на вирусы
    QList<Enemy *> enemyList;     // лист указателей на ботов
    Player *player;               // указатель на игрока
    char whoWin;                  // переменная, содержащая тип победителя
    CircleFactory cf;             // вспомогательная переменная, которая позволяет проще создавать объекты
};

#endif // MAP_H
