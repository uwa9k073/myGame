#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280, 720);       // Задаем размеры виджета, то есть окна
    this->setFixedSize(1280, 720); // Фиксируем размеры виджета

    checkingForGameOverTimer = new QTimer(); // создаем указатель на таймер

    gameState = GAME_STOPED; // устанавливаем значение состояние игры
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    map = new Map();                                                                    // Инициализируем графическую сцену
    ui->grV->setScene(map);                                                             // Устанавливаем графическую сцену в graphicsView
    ui->grV->setRenderHint(QPainter::Antialiasing);                                     // Устанавливаем сглаживание
    ui->grV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                        // Отключаем скроллбар по вертикали
    ui->grV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                      // Отключаем скроллбар по горизонтали
    map->setSceneRect(0, 0, 1200, 600);                                                 // Устанавливаем область графической сцены
    map->gameStart(ui->textEdit->toPlainText().toInt());                                // начинаем игру и передаем на граф. сцену кол-во ботов
    ui->textEdit->setText("");                                                          // обнуляем форму
    connect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::centerOnPlayer); // подключаем таймер к слоту фокуса на игрока
    connect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::gameFinish);     // подключаем таймер к слоту проверки значения whoWin
    checkingForGameOverTimer->start(10);                                                // запускаем таймер на отсчет каждые 10 милисекунд
    gameState = GAME_STARTED;                                                           // устанавливаем значения состояния игры
    ui->pushButton->setEnabled(false);                                                  // делаем кнопку недоступной к нажатию
}

void Widget::gameFinish()
{
    if ((map->getWhoWin() == 'p') || (map->getWhoWin() == 'e'))
    {                                                                                      // проверяем значение whoWin
        checkingForGameOverTimer->stop();                                                  // останавливаем таймер
        disconnect(checkingForGameOverTimer, &QTimer::timeout, this, &Widget::gameFinish); // отключаем таймер от слота проверки состояния игры
        map->gameFinished();                                                               // останавливаем игру
        gameState = GAME_STOPED;                                                           // устанавливаем значание состояния игры
        QMessageBox messageBox;                                                            // создаем messageBox
        messageBox.setText((map->getWhoWin() == 'p' ? "You win!" : "You lost!"));          // присваиваем значение его контента
        messageBox.exec();                                                                 // выводим messageBox на экран
        ui->pushButton->setEnabled(true);                                                  // делаем кнопку доступной к нажатию
        map = nullptr;                                                                     // обнуляем графическую сцену
    }
}

void Widget::centerOnPlayer()
{
    ui->grV->ensureVisible(map->getPlayer(), 50, 50);
    ui->grV->centerOn(map->getPlayer()); // фокусируем камеру на игроке
}

void Widget::on_pushButton_clicked()
{
    start(); // запускаем игру
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return:
        if (gameState == GAME_STOPED) // проверяем состояние игры
            start();                  // запускаем игру
        break;
    //устанавливаем количество врагов
    case Qt::Key_0:
        ui->textEdit->setText("");
        ui->textEdit->setText("0");
        break;
    case Qt::Key_1:
        ui->textEdit->setText("");
        ui->textEdit->setText("1");
        break;
    case Qt::Key_2:
        ui->textEdit->setText("");
        ui->textEdit->setText("2");
        break;
    case Qt::Key_3:
        ui->textEdit->setText("");
        ui->textEdit->setText("3");
        break;
    case Qt::Key_4:
        ui->textEdit->setText("");
        ui->textEdit->setText("4");
        break;
    default:
        break;
    }
}
