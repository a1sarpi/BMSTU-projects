#pragma once
#include <QMenuBar>

class DraggableMenuBar : public QMenuBar {
Q_OBJECT
public:
    explicit DraggableMenuBar(QWidget *parent = nullptr);
    bool isDraggingNow = false;
    void menuBarResizeEvent();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint startPos;

signals:
    void dragging(bool);
};