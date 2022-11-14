#include "myqgraphicsview.h"

myQGraphicsView::myQGraphicsView(QWidget *parent):
    QGraphicsView(parent){
}
void myQGraphicsView::mouseMoveEvent(QMouseEvent *ev){
    this->curs.setX(ev->position().x());
    this->curs.setY(ev->position().y());
    emit Mouse_Pos();
}

void myQGraphicsView::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Press();
    Q_UNUSED(ev)
}

void myQGraphicsView::leaveEvent(QEvent *ev)
{
    emit MouseLeft();
    Q_UNUSED(ev);
}
