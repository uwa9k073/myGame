#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Map.h>

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
    void on_pushButton_clicked(); // Слот для запуска игры
    void gameFinish();

private:
    Ui::Widget *ui;
    Map *map;
    QTimer *checkingForGameOverTimer;
    int gameState;
};

#endif // WIDGET_H
