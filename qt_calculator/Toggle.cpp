#include "Toggle.h"
#include <QDebug>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>


const QRect &Toggle::get_circle_position()
{
    return circle_position;
}

void Toggle::set_circle_position(const QRect &pos)
{
    circle_position = pos;
    update();
}

Toggle::Toggle(QWidget *parent) : QCheckBox(parent) {
    this->setFixedSize(60, 28);
    this->setCursor(Qt::PointingHandCursor);

    QRect rect1(3, 3, 22, 22);
    QRect rect2(this->width() - 26, 3, 22, 22);

    psm      = new QStateMachine;
    stateOff = new QState(psm);
    stateOn  = new QState(psm);

    stateOff->assignProperty(this, "circle_position", rect1);
    stateOn->assignProperty(this, "circle_position", rect2);

    psm->setInitialState(stateOff);

    QSignalTransition* transition_1 = stateOff->addTransition(this, SIGNAL(stateChanged(int)), stateOn);
    QSignalTransition* transition_2 = stateOn->addTransition(this, SIGNAL(stateChanged(int)), stateOff);

    auto animation1 = new QPropertyAnimation(this, "circle_position");
    transition_1->addAnimation(animation1);
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->setDuration(500);

    auto animation2 = new QPropertyAnimation(this, "circle_position");
    transition_2->addAnimation(animation2);
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->setDuration(500);

    connect(this, SIGNAL(stateChanged(int)),
            this, SLOT(debug()));

    psm->start();

}

bool Toggle::hitButton(const QPoint &pos) const
{
    return this->contentsRect().contains(pos);
}

void Toggle::paintEvent(QPaintEvent *e) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(Qt::NoPen);

        QRect rect(0, 0, this->width(), this->height());


        if (not isChecked()) {
            p.setBrush(QColor("#777"));
            p.drawRoundedRect(0, 0, rect.width(), this->height(),
                              static_cast<int>(this->height() / 2),
                              static_cast<int>(this->height() / 2));
            p.setBrush(QColor("#DDD"));
            p.drawEllipse(circle_position);

        }
        else {
            p.setBrush(QColor("#00ff00"));
            p.drawRoundedRect(0, 0, rect.width(), this->height(),
                              static_cast<int>(this->height() / 2),
                              static_cast<int>(this->height() / 2));
            p.setBrush(QColor("#DDD"));
            p.drawEllipse(circle_position);

        }

        p.end();
}

void Toggle::debug()
{
    qDebug() << "Status: " << isChecked();
}



