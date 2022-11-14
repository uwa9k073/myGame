#include "widget.h"
#include "ui_widget.h"
#include "myqgraphicsview.h"

static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(1280,720);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    ui->grV->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->grV->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->grV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->grV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    connect(ui->grV, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos));
    connect(ui->grV, SIGNAL(Mouse_Press()), this, SLOT(Mouse_Pressed()));
    connect(ui->grV, SIGNAL(MouseLeft()), this, SLOT(Mouse_Left()));



    scene->setSceneRect(-550,-300,550,300); /// Устанавливаем область графической сцены

    //timer = new QTimer();
    timerCreateFood = new QTimer();
    updateEnemyTargetTimer = new QTimer();


    gameState = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotCreateFood(){
    baseCircle *food = new baseCircle();
    food->setRadius(30);
    food->setNOfColor(1);
    scene->addItem(food);
    food->setPos(randomBetween(-450, 450), randomBetween(-200,200));
    food->setZValue(-1);
    listOfFood.append(food);
}

void Widget::slotDeleteFood(QGraphicsItem *item)
{
    /* Получив сигнал от Мухи
     * Перебираем весь список яблок и удаляем найденное яблоко
     * */
    foreach (QGraphicsItem *Food, listOfFood) {
        if(Food == item){
            scene->removeItem(Food);   // Удаляем со сцены
            listOfFood.removeOne(Food);    // Удаляем из списка
            delete Food;               // Вообще удаляем
        }
    }
}

void Widget::on_pushButton_clicked(){

    user = new Player();
    user->setRadius(30);
    user->setNOfColor(2);
    scene->addItem(user);
    user->setPos(0.0,0.0);


    connect(user, &Player::signalCheckItem, this, &Widget::slotDeleteFood);


//----------объявляем бота----------//
    enemy = new Enemy();
    enemy->setRadius(30);
    enemy->setNOfColor(3);
    scene->addItem(enemy);
    enemy->setPos(300.0, 300.0);

    connect(updateEnemyTargetTimer, &QTimer::timeout, this, &Widget::slotUpdateTarget);
    updateEnemyTargetTimer->start(1000);
    connect(enemy, &Enemy::signalCheckItem, this, &Widget::slotDeleteFood);


    connect(timerCreateFood, &QTimer::timeout, this, &Widget::slotCreateFood);
    timerCreateFood->start(1000);


    gameState = 1;
    ui->pushButton->setEnabled(false);
}

void Widget::Mouse_current_pos()
{
    QGraphicsItem* c = user->GetTarget();
    c->setPos(ui->grV->getCurs());
    user->SetTarget(c);
}

void Widget::slotUpdateTarget()
{
    enemy->FindTarget(listOfFood,user);
}
