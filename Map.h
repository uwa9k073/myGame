#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QTimer>
#include <QMessageBox>
#include "CircleFactory.h"

constexpr int VIEW_SCALE = 2;  // view scale constant
constexpr int FRAME_MS = 1000; // frame millisecond constant

class Map : public QGraphicsScene
{
public:
    explicit Map();  // конструктор
    ~Map() override; // деструктор

    // dynamic functions
    void getNewFood(qreal, qreal); // дбобавление новой еды

    void updateEnemy(Enemy *item, int x); // обновление иформации бота
    void getNewEnemy(qreal x, qreal y);   // добавление нового бота

    void updatePlayer(int x);            // обновления информации игрока
    void getNewPlayer(qreal x, qreal y); // добавление нового игрока

    void getNewVirus(qreal x, qreal y); // добавление нового вируса

    char getWhoWin() const;
    void gameStart(int numOfEnemies);        // функция начала игры
    void gameFinished();                     // функция конца игры
    QGraphicsEllipseItem *getPlayer() const; //

    void punish(baseCircle *item); // функция нанемения урона объекту

public slots:
    void slotCreateFood();              // слот создания еды
    void slotDeleteFood(baseCircle *);  // слот удаления еды
    void slotDeleteEnemy(baseCircle *); // слот удаления ботов

    void gameSlot(); // слот игровой логики

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; // Events function

private:
    QTimer *timer;                // указатель хранящий основной игровой таймер
    QTimer *timerCreateFood;      // указатель хранящий
    QList<baseCircle *> foodList; // лист указателей на еду
    QList<Virus *> virusList;     // лист указателей на вирусы
    QList<Enemy *> enemyList;     // лист указателей на ботов
    Player *player;               // указатель на игрока
    char whoWin;                  // переменная содержащая победителя
    CircleFactory cf;             // вспомогательный класс, который позволяет проще создавать объекты
};

#endif // MAP_H
