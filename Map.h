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
class Map : public QGraphicsScene
{

public:

    static Map* getInstance(); // get a pointer to object
    ~Map() override ; // Map destructor

    // dynamic functions
    void getNewFood(qreal, qreal); // adding new food

//    void getNewVirus( QString, QString ); // adding new virus

    void moveEnemy(baseCircle* tmp); // move enemy
    void updateEnemy(int, int); // update enemy info
    void updateEnemyTarget();
    void checkIfEscapeOrFollow(baseCircle* cell, int viewDis);

    void movePlayer(qreal, qreal); // move player
    void updatePlayer(qreal, int); // update player info

    // A list of pointers that hold food
    char getWhoWin() const;
    void gameStart();
    void gameFinished();
    QPointF getEnemyTargetPos() const;

signals:
    void signalGameOver();

public slots:
    void slotCreateFood();
    void slotDeleteFood(QGraphicsEllipseItem*);

    void gameSlot();  // this function is overloaded from QGraphicsScene for handle animation thing


protected:


    // events function
//    void keyPressEvent(QKeyEvent *event) override ;
//    void mouseMoveEvent( QGraphicsSceneMouseEvent *event ) override ; // Events function

private:
    Map(); // Map constructor

    // attributes
    static Map* mapPtr; // a pointer to Map's object that creates
    QTimer* timer; // A pointer that hold time
    QTimer* timerCreateFood;
    QList<baseCircle*> foodList;
    Enemy* enemy;
    Player* player;
    char whoWin;


};

#endif // MAP_H
