#include "MainWindow.h"
#include <QGridLayout>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) : calculator(new Calculator(this))
{
    resize(800, 800);

    setStyleSheet("background-color: #222");
    setWindowTitle("My Calculator (Classic Mode)");
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setCentralWidget(calculator);

    QObject::connect(calculator->mode_slider, SIGNAL(stateChanged(int)),
                     this, SLOT(onCheckBox(int)));

}

void MainWindow::onCheckBox(int state)
{
    if (state == 2) {
        setWindowTitle("My Calculator (Engineer Mode)");
        resize(1200, 800);
    }
    else {
        setWindowTitle("My Calculator (Classic Mode)");
        resize(800, 800);
    }
}
