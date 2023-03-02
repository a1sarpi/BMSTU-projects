#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QLayout>
#include <QToolButton>
#include <QPoint>
#include <QMenuBar>
#include <QWindow>
#include <QTreeView>
#include "DraggableMenuBar.h"
#include "XML_Model.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    QTreeView *getCurrentTabView();
    QTreeView *createNewTab(const QString &title);

    static XML_Model *getXMLModel(QTreeView *view);

    static int tab_index;

    QTabWidget *tabWidget;
    QMenuBar *bar;
    QMenuBar *main_bar;
    DraggableMenuBar *my_menubar;
    QAction *MAX;
    QAction *MIN;

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    ~MainWindow() override = default;

public slots:
    void OpenFile();
    void CloseAll();
    void FileContextMenu(QPoint pos);
    void CloseTab();

    void showMinimized();
    void showMaximized();
    void showRestored();
    void close();
};



