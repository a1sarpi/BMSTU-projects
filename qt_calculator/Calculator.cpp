#include "Calculator.h"
#include "QSpacerItem"
#include <iostream>
#include <unordered_map>
#include "String_Evaluate.h"

using namespace std;


Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QFile f(":/styles.qss"); //!!! Где ресурсы? Исправил.
    
    
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    auto styles = f.readAll();

    auto *item = new QSpacerItem(3, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

    auto *text_widget      = new QWidget(this);
    auto *digits_widget    = new QWidget(this);
    auto *toggle_widget    = new QWidget(this);
    auto *operators_widget = new QWidget(this);
    auto *buttons_widget   = new QWidget(this);
    auto *engineer_widget  = new QWidget(this);

    auto title        = new QLabel("Input Window", text_widget); //!!! Указать родителя. Указал.
    auto toggle_title = new QLabel("Engineer Mode", text_widget); //!!! Указать родителя. Указал.
    title->setStyleSheet(styles);
    toggle_title->setStyleSheet(styles);

    mode_slider = new Toggle(this);
    text        = new QLineEdit(text_widget);

    connect(text, SIGNAL(returnPressed()),
            this, SLOT(evaluate()));

    main_layout      = new QVBoxLayout();
    text_layout      = new QVBoxLayout(text_widget);
    buttons_layout   = new QHBoxLayout(buttons_widget);
    digits_layout    = new QGridLayout(digits_widget);
    toggle_layout    = new QHBoxLayout(toggle_widget);
    operators_layout = new QGridLayout(operators_widget);
    engineer_layout  = new QGridLayout(engineer_widget);

    text->setMaxLength(100);
    text->setMinimumHeight(100);
    text->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    text->setStyleSheet(styles);
    text->setCursor(Qt::IBeamCursor);

    text_layout->addWidget(title);
    text_layout->addWidget(text);
    buttons_layout->addWidget(digits_widget);
    buttons_layout->addWidget(operators_widget);
    buttons_layout->addWidget(engineer_widget);
    toggle_layout->addWidget(toggle_title);
    toggle_layout->addWidget(mode_slider);
    buttons_layout->addSpacerItem(item);
    main_layout->addWidget(text_widget);
    main_layout->addWidget(toggle_widget);
    main_layout->addWidget(buttons_widget);


    setLayout(main_layout);

    int row    = 0;
    int column = 0;
    vector<string> numbers = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "C"};
    for (auto &digit: numbers) {
        digits.push_back(new QPushButton(digit.c_str(), digits_widget));

        digits.back()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        digits.back()->setMinimumSize(50,50);
        digits.back()->setStyleSheet(styles);
        digits.back()->setCursor(Qt::PointingHandCursor);
        digits_layout->addWidget(digits.back(), row, column);

        QObject::connect(digits.back(), SIGNAL(clicked()),
                         this, SLOT(buttonPressed()));
        column++;
        if (column == 3) {
            row++;
            column = 0;
        }
    }

    unordered_map<string, pair<int, int>> operators_positions;
    operators_positions["+"] = make_pair(0, 0);
    operators_positions["-"] = make_pair(0, 1);
    operators_positions["*"] = make_pair(1, 0);
    operators_positions["/"] = make_pair(1, 1);
    operators_positions["("] = make_pair(2, 0);
    operators_positions[")"] = make_pair(2, 1);
    operators_positions["="] = make_pair(3, 0);
    vector<string> operators_str = {"+", "-", "*", "/", "(", ")", "="};
    for (auto &oper: operators_str) {
        operators.push_back(new QPushButton(oper.c_str(), operators_widget));

        operators.back()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        operators.back()->setMinimumSize(50,50);
        operators.back()->setStyleSheet(styles);
        operators.back()->setCursor(Qt::PointingHandCursor);

        auto position = operators_positions[oper];
        if (oper == "=") {
            operators_layout->addWidget(operators.back(), position.first, position.second, 1, 2);
        }
        else {
            operators_layout->addWidget(operators.back(), position.first, position.second);
        }
        QObject::connect(operators.back(), SIGNAL(clicked()),
                         this, SLOT(buttonPressed()));
    }

    unordered_map<string, pair<int, int>> engineer_positions;
    engineer_positions["sin" ] = make_pair(0, 0);
    engineer_positions["cos" ] = make_pair(0, 1);
    engineer_positions["tan" ] = make_pair(0, 2);
    engineer_positions["asin"] = make_pair(1, 0);
    engineer_positions["acos"] = make_pair(1, 1);
    engineer_positions["atan"] = make_pair(1, 2);
    engineer_positions["abs" ] = make_pair(2, 0);
    engineer_positions["^"   ] = make_pair(2, 1);
    engineer_positions["sqrt"] = make_pair(2, 2);
    engineer_positions["ln"  ] = make_pair(3, 0);
    engineer_positions["pi"  ] = make_pair(3, 1);
    engineer_positions["e"   ] = make_pair(3, 2);
    vector<string> engineer_str = {"sin", "cos", "tan", "asin", "acos", "atan", "ln", "pi", "e", "^", "sqrt", "abs"};
    for (auto &eng: engineer_str) {
        engineer_buttons.push_back(new QPushButton(eng.c_str(), engineer_widget));

        engineer_buttons.back()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        engineer_buttons.back()->setStyleSheet(styles);
        engineer_buttons.back()->setCursor(Qt::PointingHandCursor);

        auto &position = engineer_positions[eng];
        engineer_layout->addWidget(engineer_buttons.back(), position.first, position.second);
        QObject::connect(engineer_buttons.back(), SIGNAL(clicked()),
                         this, SLOT(buttonPressed()));
    }
    engineer_widget->setVisible(false);
    QObject::connect(mode_slider, SIGNAL(toggled(bool)),
                     engineer_widget, SLOT(setVisible(bool)));
}

void Calculator::buttonPressed()
{
    auto symbol = sender()->property("text").toString();
    if (symbol == "C") {
        text->clear();
    }
    else if (symbol == "=") {
        evaluate();
    }
    else {
        text->setText(text->text() + symbol);
    }
}

void Calculator::evaluate()
{
    // Для вычисления скачал библиотеку отсюда: https://github.com/Teddy-van-Jerry/String_Evaluate

    string error;

    QVector<QPair<QString, QString>> replacements{{"pi", "3.1415926535897932384626433832795028841971693993751058209749445923"},
                                                  {"e",  "2.7182818284590452353602874713526624977572470936999595749669676277"}};
    for (const auto &[constant, replacement]: replacements) {
        text->setText(text->text().replace(constant, replacement));
    }
    auto result = eval(text->text().toStdString(), vector<string> {}, vector<complex<double>> {}, &error).real();
    if (error.length()) {
        qDebug() << error.c_str();
        text->setText(QString::fromStdString(error));
    }
    else if (QString::number(result) == "inf") {
        text->setText("Error");
    }
    else {
        qDebug() << text->text();
        text->setText(QString::number(result));
    }
}
