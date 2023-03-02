#include "DraggableMenuBar.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

DraggableMenuBar::DraggableMenuBar(QWidget *parent) : QMenuBar(parent)
{
    setMinimumSize(100, 25);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
}

void DraggableMenuBar::mousePressEvent(QMouseEvent *event)
{
    isDraggingNow = true;
    emit dragging(isDraggingNow);
    startPos = event->pos();
    QMenuBar::mousePressEvent(event);
}

void DraggableMenuBar::mouseMoveEvent(QMouseEvent *event)
{
    if (isDraggingNow) {
        QPoint delta = event->pos() - startPos;
        QWidget *w = window();
        if (w)
            w->move(w->pos() + delta);
    }
    QMenuBar::mouseMoveEvent(event);
}

void DraggableMenuBar::mouseReleaseEvent(QMouseEvent *event) {
    isDraggingNow = false;
    emit dragging(isDraggingNow);
    QMenuBar::mouseReleaseEvent(event);
}

void DraggableMenuBar::menuBarResizeEvent() {
    resize(parentWidget()->width(), 25);
}
