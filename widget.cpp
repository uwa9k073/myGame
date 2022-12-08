#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(1280,720);    /// Фиксируем размеры виджета

    checkingForGameOverTimer= new QTimer();

    gameState = GAME_STOPED;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gameFinish()
{
    if((map->getWhoWin()=='p')||(map->getWhoWin()=='e')){
        checkingForGameOverTimer->stop();
        map->gameFinished();
        gameState = GAME_STOPED;
        QMessageBox messageBox; // create a messageBox
        messageBox.setText((map->getWhoWin()=='p' ? "You win!":"You lost!"));
        messageBox.exec();
        ui->pushButton->setEnabled(true);
    }
}

void Widget::on_pushButton_clicked(){

    map = Map::getInstance();   /// Инициализируем графическую сцену
    ui->grV->setScene(map);  /// Устанавливаем графическую сцену в graphicsView
    ui->grV->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->grV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->grV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    map->setSceneRect(0,0,1200,700); /// Устанавливаем область графической сцены
    map->gameStart(ui->textEdit->toPlainText().toInt());
    connect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::gameFinish);
    checkingForGameOverTimer->start(10);

//    ui->grV->setMouseTracking(true);
    gameState = GAME_STARTED;
    ui->pushButton->setEnabled(false);
}
