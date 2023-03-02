#pragma once
#include <QMainWindow>
#include "Calculator.h"

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Calculator *calculator;

public:
    explicit MainWindow(QWidget *parent = nullptr);

//    ~MainWindow() override {}


public slots:

    void onCheckBox(int state);

};