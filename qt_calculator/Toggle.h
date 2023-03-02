#pragma once
#include <iostream>
#include <QCheckBox>
#include <QPaintEvent>
#include <QState>
#include <QStateMachine>

using namespace std;


//!!! Разбить на h и cpp-файлы. Разбил.


class Toggle : public QCheckBox {
Q_OBJECT

Q_PROPERTY(QRect circle_position READ get_circle_position WRITE set_circle_position)

private:
    QRect circle_position;
    
    //!!! Инициализацию перенести в конструктор. Перенес.
    
    QStateMachine* psm;
    QState* stateOff;
    QState* stateOn;

public:
    const QRect &get_circle_position();
    void set_circle_position(const QRect &pos);

    explicit Toggle(QWidget *parent);

    bool hitButton(const QPoint &pos) const override;
    void paintEvent(QPaintEvent *e) override;

public slots:

    //!!! Для вывода есть qDebug. Исправил.

    void debug();
};