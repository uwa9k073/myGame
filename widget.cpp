#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(1280,720);    /// Фиксируем размеры виджета

    checkingForGameOverTimer = new QTimer();
    updateScreenTimer = new QTimer();

    gameState = GAME_STOPED;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    map = new Map();   /// Инициализируем графическую сцену
    ui->grV->setScene(map);  /// Устанавливаем графическую сцену в graphicsView
    ui->grV->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->grV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->grV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    map->setSceneRect(0,0,1200,600); /// Устанавливаем область графической сцены
    map->gameStart(ui->textEdit->toPlainText().toInt());
    ui->textEdit->setText("");
    connect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::centerOnPlayer);
    connect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::gameFinish);
    checkingForGameOverTimer->start(10);

//    ui->grV->setMouseTracking(true);
    gameState = GAME_STARTED;
    ui->pushButton->setEnabled(false);
}

void Widget::gameFinish()
{
    if((map->getWhoWin()=='p')||(map->getWhoWin()=='e')){
        checkingForGameOverTimer->stop();
        disconnect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::gameFinish);
        map->gameFinished();
        gameState = GAME_STOPED;
        QMessageBox messageBox; // create a messageBox
        messageBox.setText((map->getWhoWin()=='p' ? "You win!":"You lost!"));
        messageBox.exec();
        ui->pushButton->setEnabled(true);
        map = nullptr;
    }
}

void Widget::centerOnPlayer()
{
    ui->grV->ensureVisible(map->getPlayer(), 100, 100);
    ui->grV->centerOn(map->getPlayer());
}

void Widget::on_pushButton_clicked(){
    start();
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Return:
            if(gameState==GAME_STOPED)
                start();
        break;
    }
}
