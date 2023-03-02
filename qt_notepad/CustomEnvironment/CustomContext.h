#pragma once

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDialogButtonBox>
#include <QTableWidget>
#include <QLabel>
#include <QLayout>

class CustomDialog {
public:
    static QString getPathToOpen();
    static QString getPathToSave();

};

class CustomMessage {
public:
    static void print(const QString& format) {
        qDebug() << format;
    }

    template<typename... Args, typename Type>
    static void print(const QString& format, Type first, Args... args) {
        print(format.arg(first), args...);
    }
    template<typename Type>
    static void print(const QString& format, Type first) {
        qDebug() << format.arg(first);
    }

};

class CustomMessageBoxes {
public:
    static void Error(const QString& message);
    static void Warning(const QString& message);
    static void Info(const QString& message);
    static int CloseUnsavedFileChoice(const QString& path);
    static bool AcceptMessage(const QString& message);
};

class MultipleUnsaved : public QDialog {
    Q_OBJECT
public:
    explicit MultipleUnsaved(const QVector<QPair<QString, QString>> &unsaved, QWidget *parent = nullptr);
    QPair<bool, QVector<bool>> execute();
    ~MultipleUnsaved() override = default;

public slots:
    void onButtonClicked(QAbstractButton *);

private:
    QWidget *dialog_widget;
    QVBoxLayout *dialog_layout;
    QDialogButtonBox *DialogButtonBox;
    QTableWidget *UnsavedFilesTable;
    QLabel *label;
};