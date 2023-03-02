#pragma once
#include <QTabWidget>
#include "SyntaxHighlighter.h"

class FileTabWidget : public QTabWidget {
    Q_OBJECT
private:
    int currentTabIndex = 0;
    SyntaxHighlighter *highlighter;
    void WelcomeTab();

public:
    explicit FileTabWidget(QWidget *parent);

    bool CloseAll();
    void SelectAll();
    bool Save(int index = -1);
    bool SaveCurrent();
    bool SaveCurrentAs();
    void OpenFile(const QString&);
    void OpenNewUntitled();
    void cut();
    void copy();
    void paste();

signals:
    void cursorPositionChanged(int, int);

public slots:
    void onCurrentChanged(int);
    bool closeByIndex(int);
    void onTextChanged();
    void onCursorPositionChanged();
};
