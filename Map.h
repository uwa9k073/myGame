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

constexpr int VIEW_SCALE = 2; // view scale constant
constexpr int FRAME_MS = 1000; // frame millisecond constant

// Class map handle QGraphicsScene items
class Map : public QGraphicsScene{
public:

    explicit Map(); // Map construct
    ~Map() override ; // Map destructor

    // dynamic functions
    void getNewFood(qreal, qreal); // adding new food

    void updateEnemy(Enemy*  item, int x); // update enemy info
    void getNewEnemy(qreal x, qreal y);//adding new enemy

    void updatePlayer(int x); // update player info
    void getNewPlayer(qreal x, qreal y);//adding new player

    void getNewVirus(qreal x, qreal y);

    // A list of pointers that hold food
    char getWhoWin() const;
    void gameStart(int numOfEnemies);
    void gameFinished();

    void punish(baseCircle* item);

signals:
    void signalGameOver();

public slots:
    void slotCreateFood();
    void slotDeleteFood(QGraphicsEllipseItem*);
    void slotDeleteEnemy(QGraphicsEllipseItem*);

    void gameSlot();  // this function is overloaded from QGraphicsScene for handle animation thing


protected:


    // events function
//    void keyPressEvent(QKeyEvent *event) override ;
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event ) override ; // Events function

private:

    // attributes
    static Map* mapPtr; // a pointer to Map's object that creates
    QTimer* timer; // A pointer that hold time
    QTimer* timerCreateFood;
    QList<baseCircle*> foodList;
    QList<Virus* > virusList;
    QList<Enemy*> enemyList;
    Player* player;
    char whoWin;


};

#endif // MAP_H
