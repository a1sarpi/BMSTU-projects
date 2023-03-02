#pragma once
#include <iostream>
#include <QtWidgets>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QClipboard>
#include <QGuiApplication>
#include "Toggle.h"

class Calculator : public QWidget {
Q_OBJECT
public:
    Toggle *mode_slider;
    explicit Calculator(QWidget *parent = nullptr);

private:
    QLineEdit *text;

    QVector<QPushButton *> digits;
    QVector<QPushButton *> operators;
    QVector<QPushButton *> engineer_buttons;

    QVBoxLayout *main_layout;

    QHBoxLayout *buttons_layout;
    QVBoxLayout *text_layout;
    QGridLayout *digits_layout;
    QGridLayout *operators_layout;
    QGridLayout *engineer_layout;
    QHBoxLayout *toggle_layout;

public slots:
    void evaluate();

    void buttonPressed();

};
