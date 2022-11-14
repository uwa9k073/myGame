#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QShortcut>


#include <baseCircle.h>
#include <Player.h>
#include <Enemy.h>


#define GAME_STOPED 0
#define GAME_STARTED 1

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void slotCreateFood();
    void slotDeleteFood(QGraphicsItem * item);
    void on_pushButton_clicked();               // Слот для запуска игры
    void Mouse_current_pos();
    void Mouse_Pressed();
    void Mouse_Left();
    void slotUpdateTarget();

private:
    Ui::Widget *ui;
    QGraphicsScene  *scene; // Объявляем графическую сцену
    QTimer *timerCreateFood;

    Enemy *enemy;
    QTimer *updateEnemyTargetTimer;

    Player *user;
    QTimer *timer;

    QList<QGraphicsItem *> listOfFood;
    int gameState;

//    Player        *user;  //игрок
//    QTimer          *timer; //таймер игрока
};
#endif // WIDGET_H
