#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

class myQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myQGraphicsView(QWidget *parent = 0);
//    ~myQGraphicsView();
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *ev);
    QPointF getCurs(){return curs;}
signals:
    void Mouse_Press();
    void Mouse_Pos();
    void MouseLeft();
public slots:

private:

    QPointF curs;
};

#endif // MYQGRAPHICSVIEW_H
