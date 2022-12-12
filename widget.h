#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Map.h>

#define GAME_STOPED 0
#define GAME_STARTED 1

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void start(); // функция запуска игры

public slots:
    void on_pushButton_clicked(); // Слот для запуска игры
    void gameFinish();            // слот для завершения игры
    void centerOnPlayer();        // слот фокусирования на игроке

private:
    Ui::Widget *ui;
    Map *map; // игровое поле
    QTimer *checkingForGameOverTimer;
    int gameState; // состояние игры

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override; //
};

#endif // WIDGET_H
