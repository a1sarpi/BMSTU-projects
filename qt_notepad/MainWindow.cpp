#include "MainWindow.h"
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "CustomEnvironment/CustomContext.h"
#include <QStringListModel>
#include <QHeaderView>
#include <QStatusBar>
#include <QApplication>
#include "TextEditor.h"
#include <QDockWidget>
#include <QFileInfo>
#include <QShortcut>
#include <QLayout>
#include <QModelIndex>

bool MainWindow::ValidateFile(const QString &path) {
    QFile file(path);
    QFileInfo info(file);
    if (info.isDir()) {
        CustomMessage::print("Impossible to open " + info.fileName() + ", because it's directory");
        return false;
    }
    if (not info.isFile()) {
        CustomMessageBoxes::Warning("Impossible to open " + info.fileName() + ", because it isn't file");
        return false;
    }
    if (not info.isReadable()) {
        CustomMessageBoxes::Warning("Can't read file " + info.fileName());
        return false;
    }
    if (not info.isWritable()) {
        CustomMessageBoxes::Warning("Can't write into file " + info.fileName());
        return false;
    }
    if (not info.isReadable()) {
        CustomMessageBoxes::Warning(info.fileName() + " is executable");
        return false;
    }
    return true;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Qt Notepad");

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setWindowFlags(Qt::FramelessWindowHint);

    resize(1200, 800);

    TabWidget = new FileTabWidget(this);
    TabWidget->setTabsClosable(true);
    connect(TabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(CloseFile()));

    my_menubar = new DraggableMenuBar(this);
    my_menubar->setObjectName("MainMenu");
    my_menubar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    FileSystemDock  = new QDockWidget("File System", this);
    OpenedFilesDock = new QDockWidget("Opened Files",this);
    WorkspaceDock   = new QDockWidget("Workspace", this);
    OpenedFilesList = new QListView(this);

    addDockWidget(Qt::LeftDockWidgetArea, FileSystemDock, Qt::Orientation::Horizontal);
    addDockWidget(Qt::LeftDockWidgetArea, WorkspaceDock, Qt::Orientation::Horizontal);
    addDockWidget(Qt::RightDockWidgetArea, OpenedFilesDock, Qt::Orientation::Horizontal);

    FileSystemDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    OpenedFilesDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    WorkspaceDock->setFeatures(QDockWidget::DockWidgetMovable);

    QFile stylesheet(":/styles.qss");
    if (stylesheet.open(QIODevice::ReadOnly)) {
        auto styles = stylesheet.readAll();
        setStyleSheet(styles);
    }

    FileSystemModel = new QFileSystemModel(this);
    auto path = QDir::currentPath();
    FileSystemModel->setRootPath(path);

    QIcon GOUP(":/UP.svg");
    GoUp = new QPushButton(this);
    GoUp->setIcon(GOUP);
    GoUp->setIconSize(GoUp->size());
    GoUp->setCursor(Qt::PointingHandCursor);
    GoUp->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    auto CurrentDirectory = QDir::toNativeSeparators(path).split(QDir::separator()).back();
    CurrentDirLabel = new QLabel(CurrentDirectory, this);
    CurrentDirLabel->setText(CurrentDirectory);

    FileSystem = new QTreeView(this);

    FileSystem->setModel(FileSystemModel);
    FileSystem->setRootIndex(FileSystemModel->index(QDir::currentPath()));
    FileSystem->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    FileSystem->hideColumn(1);
    FileSystem->hideColumn(2);
    FileSystem->hideColumn(3);

    FileSystemWidget = new QWidget(this);
    FileSystemLayout = new QVBoxLayout(FileSystemWidget);

    FileSystemLayout->addWidget(CurrentDirLabel);
    FileSystemLayout->addWidget(GoUp);
    FileSystemLayout->addWidget(FileSystem);

    FileSystemWidget->setLayout(FileSystemLayout);

    FileSystemDock->setWidget(FileSystemWidget);
    OpenedFilesDock->setWidget(OpenedFilesList);
    WorkspaceDock->setWidget(TabWidget);

    connect(GoUp, SIGNAL(clicked(bool)),
            this, SLOT(OpenParentDirectoty()));

    auto *tool_bar = new QToolBar("Tool Bar", this);
    addToolBar(tool_bar);

    updateOpenedFileList();

    CaretPosition = new QLabel(this);
    statusBar()->addPermanentWidget(CaretPosition);
    QObject::connect(TabWidget, SIGNAL(currentChanged(int)),
                     this, SLOT(OnTabChanged(int)));
    QObject::connect(TabWidget, SIGNAL(cursorPositionChanged(int,int)),
                     this, SLOT(OnCursorPositionChanged(int,int)));

    auto *FILE = new QMenu("&File", this);
    auto *EDIT = new QMenu("&Edit", this);
    auto *VIEW = new QMenu("&View", this);

    QIcon NEW(":/NEW.svg");
    QIcon OPEN(":/OPEN.svg");
    QIcon SAVE(":/SAVE.svg");
    QIcon SAVEALL(":/SAVEALL.svg");
    QIcon COPE(":/COPE.svg");
    QIcon CUT(":/CUT.svg");
    QIcon PASTE(":/PASTE.svg");

    tool_bar->setCursor(Qt::PointingHandCursor);

    auto *NewFile = new QAction(NEW, "&New File", this);
    NewFile->setShortcut(Qt::CTRL | Qt::Key_N);
    connect(NewFile, SIGNAL(triggered(bool)),
            this, SLOT(NewFile()));
    FILE->addAction(NewFile);
    tool_bar->addAction(NewFile);

    auto *OpenFile = new QAction(OPEN, "&Open File", this);
    OpenFile->setShortcut(Qt::CTRL | Qt::Key_O);
    connect(OpenFile, SIGNAL(triggered(bool)),
            this, SLOT(OpenFile()));
    FILE->addAction(OpenFile);
    tool_bar->addAction(OpenFile);

    auto *SaveFile = new QAction(SAVE,"&Save File", this);
    SaveFile->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(SaveFile, SIGNAL(triggered(bool)),
            this, SLOT(SaveFile()));
    FILE->addAction(SaveFile);
    tool_bar->addAction(SaveFile);

    auto *SaveFileAs = new QAction("Save File As", this);
    connect(SaveFileAs, SIGNAL(triggered(bool)),
            this, SLOT(SaveFileAs()));
    FILE->addAction(SaveFileAs);

    auto *SaveAllFiles = new QAction(SAVEALL, "Save &All Files", this);
    SaveAllFiles->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    connect(SaveAllFiles, SIGNAL(triggered(bool)),
            this, SLOT(SaveAllFiles()));
    FILE->addAction(SaveAllFiles);
    tool_bar->addAction(SaveAllFiles);

    auto *CloseFile = new QAction("&Close File", this);
    CloseFile->setShortcut(Qt::CTRL | Qt::Key_W);
    connect(CloseFile, SIGNAL(triggered(bool)),
            this, SLOT(CloseFile()));
    FILE->addAction(CloseFile);

    auto *CloseAllFiles = new QAction("Close A&ll Files", this);
    CloseAllFiles->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_W);
    connect(CloseAllFiles, SIGNAL(triggered(bool)),
            this, SLOT(CloseAllFiles()));
    FILE->addAction(CloseAllFiles);

    auto *quit = new QAction("&Quit", this);
    quit->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(quit, SIGNAL(triggered(bool)),
            this, SLOT(quit()));
    FILE->addAction(quit);

    auto *copy = new QAction(COPE,"&Copy", this);
    copy->setShortcut(Qt::CTRL | Qt::Key_C);
    connect(copy, SIGNAL(triggered(bool)),
            this, SLOT(copy()));
    EDIT->addAction(copy);
    tool_bar->addAction(copy);

    auto *paste = new QAction(PASTE, "&Paste", this);
    paste->setShortcut(Qt::CTRL | Qt::Key_V);
    connect(paste, SIGNAL(triggered(bool)),
            this, SLOT(paste()));
    EDIT->addAction(paste);
    tool_bar->addAction(paste);

    auto *cut = new QAction(CUT, "Cu&t", this);
    cut->setShortcut(Qt::CTRL | Qt::Key_X);
    connect(cut, SIGNAL(triggered(bool)),
            this, SLOT(cut()));
    EDIT->addAction(cut);
    tool_bar->addAction(cut);

    auto *select_all = new QAction("S&elect All", this);
    select_all->setShortcut(Qt::CTRL | Qt::Key_A);
    connect(select_all, SIGNAL(triggered(bool)),
            this, SLOT(select_all()));
    EDIT->addAction(select_all);

    showFileSystem = new QAction("Show File System", this);
    showFileSystem->setCheckable(true);
    showFileSystem->setChecked(true);
    connect(showFileSystem, SIGNAL(toggled(bool)),
            FileSystemDock, SLOT(setVisible(bool)));
    VIEW->addAction(showFileSystem);

    showOpened = new QAction("Show Opened", this);
    showOpened->setCheckable(true);
    showOpened->setChecked(true);
    connect(showOpened, SIGNAL(toggled(bool)),
            OpenedFilesDock, SLOT(setVisible(bool)));
    VIEW->addAction(showOpened);

    connect(showFileSystem, SIGNAL(toggled(bool)),
            this, SLOT(UpdateExplorerStates()));
    connect(showOpened, SIGNAL(toggled(bool)),
            this, SLOT(UpdateExplorerStates()));
    connect(FileSystem, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(ExplorerItemDoubleClicked(QModelIndex)));

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
    main_bar->addMenu(EDIT);
    main_bar->addMenu(VIEW);

    my_menubar->setCornerWidget(bar, Qt::TopRightCorner);
    my_menubar->setCornerWidget(main_bar, Qt::TopLeftCorner);

    setMenuWidget(my_menubar);

    connect(my_menubar, SIGNAL(dragging(bool)),
            this, SLOT(showRestored()));
}

/*MainWindow::~MainWindow() {

}*/

void MainWindow::OpenParentDirectoty() {
    QModelIndex current_root = FileSystem->rootIndex();
    if (current_root.parent().isValid()) {
            FileSystem->setRootIndex(current_root.parent());
            auto upDir = qvariant_cast<QString>(FileSystem->rootIndex().data());
            CustomMessage::print("Switched to parent directory" + upDir);
            CurrentDirLabel->setText(upDir);
    }
}

void MainWindow::ExplorerItemDoubleClicked(const QModelIndex &index) {
    auto path = index.data(QFileSystemModel::FilePathRole).toString();
    if (path.isEmpty()) {
        TabWidget->setCurrentIndex(index.row());
        return;
    }
    QFile file(path);
    QFileInfo info(file);
    if (not MainWindow::ValidateFile(path)) {
        if (info.isDir()) {
            qDebug() << "set root" << path;
            FileSystem->setRootIndex(index);
            CurrentDirLabel->setText(QDir::toNativeSeparators(path).split(QDir::separator()).back());
        }
    }
    qDebug() << path;
    if (not info.isDir()) {
        TabWidget->OpenFile(path);
        updateOpenedFileList();
        statusBar()->showMessage(tr(QString("Opened existing file " + path).toStdString().c_str()), 5000);
    }
}

void MainWindow::NewFile() {
    qDebug() << "NewFile";
    TabWidget->OpenNewUntitled();
    updateOpenedFileList();
    statusBar()->showMessage(tr("New File Created"), 5000);
}

void MainWindow::OpenFile() {
    qDebug() << "OpenFile";
    auto path = CustomDialog::getPathToOpen();
    if (path.isEmpty()) {
        CustomMessageBoxes::Warning(tr("No File Selected"));
        qDebug() << "No path specified";
        return;
    }
    TabWidget->OpenFile(path);
    updateOpenedFileList();
    statusBar()->showMessage(tr(QString("Opened existing file " + path).toStdString().c_str()), 5000);
}

void MainWindow::SaveFile() {
    qDebug() << "SaveFile";
    if (TabWidget->SaveCurrent()) {
        updateOpenedFileList();
        statusBar()->showMessage(QString("File " + TabWidget->tabText(TabWidget->currentIndex()) + " successfully saved"), 5000);
    }
}

void MainWindow::SaveFileAs() {
    qDebug() << "SaveFileAs";
    if (TabWidget->SaveCurrentAs()) {
        updateOpenedFileList();
        statusBar()->showMessage(QString("File " + TabWidget->tabText(TabWidget->currentIndex()) + " successfully saved"), 5000);
    }
}

void MainWindow::SaveAllFiles() {
    qDebug() << "SaveAllDocuments";
    for (auto i = 0; i < TabWidget->count(); ++i) {
        TabWidget->Save(i);
        updateOpenedFileList();
    }
    statusBar()->showMessage("All files saved", 5000);
}

void MainWindow::CloseFile() {
    qDebug() << "CloseFile";
    auto index = TabWidget->currentIndex();
    if (index == -1) {
        CustomMessageBoxes::Info("Nothing to close. Choose some file.");
        return;
    }
    else {
        auto file = TabWidget->tabText(index);
        TabWidget->closeByIndex(index);
        updateOpenedFileList();
        statusBar()->showMessage(QString("File " + file + " successfully closed"), 5000);
    }
}

bool MainWindow::CloseAllFiles() {
    qDebug() << "CloseALlFiles";
    QVector<QPair<QString, QString>> unsaved_files;
    for (auto i = 0; i < TabWidget->count(); ++i) {
        auto *editor = dynamic_cast<TextEditor *>(TabWidget->widget(i));
        if (not editor) continue;
        if (not editor->isChangedSaved()) {
            auto name = TabWidget->tabText(i);
            auto path = editor->getFilePath();
            unsaved_files << qMakePair(name, path);
        }
    }
    if (unsaved_files.count() > 1) {
        auto dialog = MultipleUnsaved(unsaved_files, this);
        auto [success, toSave] = dialog.execute();
        if (success) {
            for (auto i = 0; i < unsaved_files.count(); ++i) {
                toSave[i] ? CustomMessage::print("true", unsaved_files[i].first) :
                            CustomMessage::print("false", unsaved_files[i].first);
                if (toSave[i]) {
                    TabWidget->Save(i);
                }
            }
            while (TabWidget->count() > 0) {
                TabWidget->removeTab(0);
            }
            updateOpenedFileList();
            return true;
        }
        else return false;
    }
    if (TabWidget->CloseAll()) {
        updateOpenedFileList();
        statusBar()->showMessage("All files are closed", 5000);
        return true;
    }
    return false;
}

bool MainWindow::quit() {
    qDebug() << "quit";
    if (CloseAllFiles()) {
        if (TabWidget->count() != 0) {
            CustomMessageBoxes::Info("Not all files closed! Can't quit.");
            return false;
        }
        if (CustomMessageBoxes::AcceptMessage("Quit")) {
            QApplication::closeAllWindows();
            QApplication::quit();
            return true;
        }
    }
    return false;
}

void MainWindow::copy() {
    qDebug() << "copy";
    TabWidget->copy();
}

void MainWindow::paste() {
    qDebug() << "paste";
    TabWidget->paste();
}

void MainWindow::cut() {
    qDebug() << "cut";
    TabWidget->cut();
}

void MainWindow::select_all() {
    qDebug() << "select_all";
    TabWidget->SelectAll();
}

void MainWindow::OnTabChanged(int index) {
    if (index == -1) {
        CaretPosition->setVisible(false);
    }
    else {
        CaretPosition->setVisible(true);
        TabWidget->onCursorPositionChanged();
    }
}

void MainWindow::OnCursorPositionChanged(int line, int column) {
    auto text = QString(QString::number(line) + ":" + QString::number(column));
    CaretPosition->setText(text);
}

void MainWindow::UpdateExplorerStates() {
    showFileSystem->setChecked(FileSystemDock->isVisible());
    showOpened->setChecked(OpenedFilesDock->isVisible());
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
    QMainWindow::close();
}

void MainWindow::updateOpenedFileList() {
    QStringList files;
    for (auto i = 0; i < TabWidget->count(); ++i) {
        files << TabWidget->tabText(i);
    }
    auto *model = new QStringListModel(files, this);
    OpenedFilesList->setModel(model);
    OpenedFilesList->show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (quit()) {
        QWidget::closeEvent(event);
        event->accept();
    }
    else {
        event->ignore();
    }
}

