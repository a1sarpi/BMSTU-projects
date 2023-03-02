#pragma once
#include <QFileSystemModel>
#include <QMainWindow>
#include <QStringList>
#include <QTreeView>
#include <QLabel>
#include <QDebug>
#include "CustomEnvironment/DraggableMenuBar.h"
#include "FileTabWidget.h"
#include <QListView>
#include <QPushButton>
#include <QLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    FileTabWidget *TabWidget;

    QPushButton *GoUp;

    QVBoxLayout *FileSystemLayout;
    QWidget     *FileSystemWidget;

    QMenuBar *bar;
    QMenuBar *main_bar;
    DraggableMenuBar *my_menubar;

    QAction *MAX;
    QAction *MIN;

    QAction *showOpened;
    QAction *showFileSystem;

    QTreeView *FileSystem;
    QLabel *CurrentDirLabel;

    QDockWidget *FileSystemDock;
    QDockWidget *OpenedFilesDock;
    QDockWidget *WorkspaceDock;

    QFileSystemModel *FileSystemModel;

    QListView *OpenedFilesList;

    QLabel *CaretPosition;

    static bool ValidateFile(const QString &path);

    void updateOpenedFileList();

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

public slots:
    void OpenParentDirectoty();
    void ExplorerItemDoubleClicked(const QModelIndex &index);

    void NewFile();
    void OpenFile();
    void SaveFile();
    void SaveFileAs();
    void SaveAllFiles();
    void CloseFile();
    bool CloseAllFiles();

    bool quit();
    void copy();
    void paste();
    void cut();
    void select_all();

    void OnTabChanged(int);
    void OnCursorPositionChanged(int, int);
    void UpdateExplorerStates();

    void showMinimized();
    void showMaximized();
    void showRestored();
    void close();

protected:
    void closeEvent(QCloseEvent *event) override;

};