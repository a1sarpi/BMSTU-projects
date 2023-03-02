#include "MainWindow.h"
#include <QPainter>
#include <QMenuBar>
#include <QMenu>
#include <QTimer>
#include <QLabel>
#include <QFile>
#include <QEvent>
#include <QShortcut>
#include <QCloseEvent>
#include <QToolBar>
#include <QLayout>
#include <QFileDialog>

int MainWindow::tab_index = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(CloseTab()));
    my_menubar = new DraggableMenuBar(this);
    my_menubar->setObjectName("MainMenu");
    my_menubar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    resize(1200, 800);

    setWindowTitle("XML Reader");
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setWindowFlags(Qt::FramelessWindowHint);

    QFile f(":/styles.qss");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    auto styles = f.readAll();
    setStyleSheet(styles);

    auto *FILE = new QMenu("&File", this);


    auto *OpenFile = new QAction("&Open File", this);
    connect(OpenFile, SIGNAL(triggered(bool)),
            this, SLOT(OpenFile()));
    FILE->addAction(OpenFile);

    auto *CloseAll = new QAction("&Close All", this);
    FILE->addAction(CloseAll);
    connect(CloseAll, SIGNAL(triggered(bool)),
            this, SLOT(CloseAll()));

    auto *CloseTab = new QAction("Close &Tab", this);
    FILE->addAction(CloseTab);
    connect(CloseTab, SIGNAL(triggered(bool)),
            this, SLOT(CloseTab()));

    auto *CLOSE = new QAction("E&xit", this);
    connect(CLOSE, SIGNAL(triggered(bool)),
            this, SLOT(close()));
    FILE->addAction(CLOSE);

    QIcon home_icon(":/HOME.svg");
    QIcon minus_icon(":/MINUS.svg");
    QIcon maximize_icon(":/MAXIMIZE.svg");
    QIcon minimize_icon(":/MINIMIZE.svg");
    QIcon close_icon(":/CLOSE.svg");

    auto *HOME = new QAction(home_icon, "HOME", this);
    HOME->setDisabled(true);
    auto *MINUS = new QAction(minus_icon, "MINUS", this);
    MAX = new QAction( maximize_icon, "MAX", this);
    MIN = new QAction(minimize_icon, "MIN", this);
    auto *X = new QAction( close_icon, "CLOSE", this);

    HOME->setObjectName("HOME");
    MINUS->setObjectName("MINUS");
    MAX->setObjectName("MAX");
    MIN->setObjectName("MIN");
    X->setObjectName("CLOSE");

    connect(MINUS, SIGNAL(triggered(bool)), this, SLOT(showMinimized()));
    connect(MAX, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));
    connect(MIN, SIGNAL(triggered(bool)), this, SLOT(showRestored()));
    connect(X, SIGNAL(triggered(bool)), this, SLOT(close()));


    bar = new QMenuBar(my_menubar);
    bar->addAction(MINUS);
    bar->addAction(MAX);
    bar->addAction(MIN);
    bar->addAction(X);

    MIN->setVisible(false);

    main_bar = new QMenuBar(my_menubar);
    main_bar->addAction(HOME);
    main_bar->addMenu(FILE);

    my_menubar->setCornerWidget(bar, Qt::TopRightCorner);
    my_menubar->setCornerWidget(main_bar, Qt::TopLeftCorner);
    createNewTab("Tab ");

    connect(my_menubar, SIGNAL(dragging(bool)),
            this, SLOT(showRestored()));

    setMenuWidget(my_menubar);
    setCentralWidget(tabWidget);
}

void MainWindow::showMinimized() {
    QMainWindow::showMinimized();
}

void MainWindow::showMaximized() {
    setWindowState(Qt::WindowMaximized);
    MAX->setVisible(false);
    MIN->setVisible(true);
    my_menubar->menuBarResizeEvent();
    QMainWindow::showMaximized();
}

void MainWindow::showRestored() {
    setWindowState(Qt::WindowNoState);
    MAX->setVisible(true);
    MIN->setVisible(false);
    my_menubar->menuBarResizeEvent();
    QMainWindow::showNormal();
}


void MainWindow::close() {
    QWidget::close();
}

void MainWindow::OpenFile()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Choose XML-file"), "../Data", "XML-Files (*.xml)");
    if (not path.isEmpty()) {
        QFile file(path);
        auto *tree_view = getCurrentTabView();
        tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tree_view->setWordWrap(true);
        auto *xml_model = getXMLModel(tree_view);
        if (xml_model->loadFromFile(path)) {
            tree_view->reset();
            tree_view->setModel(xml_model);
        }
    }
}

void MainWindow::CloseAll() {
    auto *tree_view = getCurrentTabView();
    auto *xml_model = getXMLModel(tree_view);
    tree_view->reset();
    delete xml_model;
    xml_model = new XML_Model(this);
    tree_view->setModel(xml_model);
    qDebug() << "Closed";
}

void MainWindow::FileContextMenu(QPoint pos) {
    auto *tree_view = getCurrentTabView();
    if (tree_view->currentIndex().parent() == QModelIndex() and tree_view->indexAt(pos).isValid()) {
        auto *menu = new QMenu(this);
        auto *close_action = new QAction(tr("Close"), this);
        menu->addAction(close_action);
        connect(close_action, &QAction::triggered, [&]() {
            auto *tree_view = getCurrentTabView();
            auto current_index = tree_view->currentIndex();
            auto result = tree_view->model()->removeRow(current_index.row(), QModelIndex());
            qDebug() << "Close Action on " + QString::number(current_index.row())
                              + " success" + QString::number(result);
            tree_view->reset();
        });
        auto *toNewTabAction = new QAction(tr("Move to new tab"), this);
        menu->addAction(toNewTabAction);
        connect(toNewTabAction, &QAction::triggered, [&]() {
            qDebug() << "toNewTabAction";
            auto *current_tree_view = getCurrentTabView();
            auto *current_model = getXMLModel(current_tree_view);
            auto current_index = current_tree_view->currentIndex();
            auto *new_tree_view = createNewTab("Tab ");
            auto *new_model = getXMLModel(new_tree_view);
            new_model->append(current_index);
            auto new_tab_index = tabWidget->currentIndex();
            current_model->removeRow(current_index.row());
        });
        menu->popup(tree_view->viewport()->mapToGlobal(pos));
    }
}

QTreeView *MainWindow::getCurrentTabView() {
    auto *current = dynamic_cast<QTreeView *>(tabWidget->currentWidget());
    if (current == nullptr) {
        createNewTab("Tab ");
    }
    return dynamic_cast<QTreeView *>(tabWidget->currentWidget());
}

XML_Model *MainWindow::getXMLModel(QTreeView *view) {
    return dynamic_cast<XML_Model *>(view->model());
}

QTreeView *MainWindow::createNewTab(const QString &title) {
    auto *tree_view = new QTreeView(tabWidget);
    tree_view->setContextMenuPolicy(Qt::CustomContextMenu);
    tree_view->setHeaderHidden(true);
    auto *model = new XML_Model(tree_view);
    tree_view->setModel(model);
    QObject::connect(tree_view, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(FileContextMenu(QPoint)));
    tabWidget->addTab(tree_view, title + QString::number(++tab_index));
    tabWidget->setCurrentIndex(tabWidget->indexOf(tree_view));
    return tree_view;
}

void MainWindow::CloseTab() {
    tabWidget->removeTab(tabWidget->currentIndex());
    qDebug() << "Tab Closed " << tabWidget->currentIndex();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

