#include "FileTabWidget.h"
#include <QFile>
#include <QFileInfo>
#include "CustomEnvironment/CustomContext.h"
#include "TextEditor.h"
#include <QMessageBox>

void FileTabWidget::WelcomeTab() {
    QString welcome_text = "Hello!\n"
                        "\n\n\n"
                        "File Functions: \n\n"
                        "Ctrl+O       - Open File\n"
                        "Ctrl+N       - Open New File\n"
                        "Ctrl+S       - Save File\n"
                        "Ctrl+Shift+S - Save All\n"
                        "Ctrl+W       - Close File\n"
                        "Ctrl+Shift+W - Close All\n"
                        "Ctrl+Q       - Exit App\n"
                        "\n\n\n"
                        "Edit Functions: \n\n"
                        "Ctrl+C - Copy\n"
                        "Ctrl+V - Paste\n"
                        "Ctrl+X - Cut\n"
                        "Ctrl+A - Select All\n";
    auto *editor = new TextEditor(this);
    editor->setText(welcome_text);
    auto font = editor->font();
    font.setBold(true);
    editor->setChangesSaved(true);
    addTab(editor, "Welcome");
    setCurrentWidget(editor);
    editor->setReadOnly(true);
}

FileTabWidget::FileTabWidget(QWidget *parent) : QTabWidget(parent) {
    WelcomeTab();
    setTabsClosable(true);
    highlighter = new SyntaxHighlighter;
    highlighter->setParent(this);
    QObject::connect(this, SIGNAL(currentChanged(int)),
                     this, SLOT(onCurrentChanged(int)));
}

bool FileTabWidget::CloseAll() {
    auto i = count();
    bool success = true;
    while (i-- > 0) {
        success &= closeByIndex(0);
    }
    return success;
}

void FileTabWidget::SelectAll() {
    auto *editor = dynamic_cast<TextEditor *>(currentWidget());
    if (editor) {
        editor->selectAll();
    }
}

bool FileTabWidget::Save(int index) {
    auto *FileToSave = dynamic_cast<TextEditor *>(widget(index));
    if (not FileToSave) {
        CustomMessageBoxes::Error("Error while saving");
        CustomMessage::print("Invalid index to save [%1]", index);
        return false;
    }
    if (FileToSave->getFilePath().isEmpty() and tabText(index) != "Welcome") {
        qDebug() << "Save -> SaveAs " << tabText(index);
        if (SaveCurrentAs()) {
            if (closeByIndex(currentIndex())) {
                OpenFile(FileToSave->getFilePath());
            }
            else {
                CustomMessageBoxes::Error("Error while closing file");
            }
        } else return false;
    }
    else {
        qDebug() << "Save";
        FileToSave->saveChanges();
    }
    if (tabText(index).contains('*')) {
        setTabText(index, tabText(index).remove('*'));
    }
    return true;
}

bool FileTabWidget::SaveCurrent() {
    auto index = currentIndex();
    if (index == -1) {
        CustomMessageBoxes::Info("Nothing to save. No file selected");
        return false;
    }
    if (tabText(index) != "Welcome") {
        return Save(index);
    }
    else return false;
}

bool FileTabWidget::SaveCurrentAs() {
    if (tabText(currentIndex()) != "Welcome") {
        auto *FileToSave = dynamic_cast<TextEditor *>(currentWidget());
        if (not FileToSave) {
            CustomMessageBoxes::Info("Nothing to save. No file selected");
            return false;
        }
        qDebug() << "Save Current As";
        return FileToSave->saveAs();
    }
    else return false;
}

void FileTabWidget::OpenFile(const QString &path) {
    for (auto i = 0; i < count(); ++i) {
        if (tabText(i) == path or dynamic_cast<TextEditor *>(widget(i))->getFilePath() == path) {
            setCurrentIndex(i);
            return;
        }
    }
    auto *editor = new TextEditor(path, this);
    QObject::connect(editor, SIGNAL(cursorPositionChanged()),
                     this, SLOT(onCursorPositionChanged()));
    QFileInfo info(path);
    addTab(editor, info.fileName());
    setCurrentWidget(editor);
}

void FileTabWidget::OpenNewUntitled() {
    auto *editor = new TextEditor;
    QObject::connect(editor, SIGNAL(cursorPositionChanged()),
                     this, SLOT(onCursorPositionChanged()));
    addTab(editor, "Untitled*");
    setCurrentWidget(editor);
    editor->setChangesSaved(false);
    highlighter->setDocument(editor->document());
    highlighter->SetExtension();
}

void FileTabWidget::cut() {
    auto editor = dynamic_cast<TextEditor *>(currentWidget());
    if (editor) {
        editor->cut();
    }
}

void FileTabWidget::copy() {
    auto editor = dynamic_cast<TextEditor *>(currentWidget());
    if (editor) {
        editor->copy();
    }
}

void FileTabWidget::paste() {
    auto editor = dynamic_cast<TextEditor *>(currentWidget());
    if (editor) {
        editor->paste();
    }
}

void FileTabWidget::onCurrentChanged(int index) {
    CustomMessage::print("Current changed to %1 from %2", index, currentTabIndex);
    auto *editor = dynamic_cast<TextEditor *>(currentWidget());
    if (editor) {
        if (currentTabIndex != -1) {
            auto *previous = dynamic_cast<TextEditor *>(widget(currentTabIndex));
            if (previous) {
                QObject::disconnect(previous, SIGNAL(textChanged()),
                                    this, SLOT(onTextChanged()));
            }
            highlighter->setDocument(editor->document());
            highlighter->SetExtension(tabText(index));
            highlighter->rehighlight();
            currentTabIndex = index;
            QObject::connect(editor, SIGNAL(textChanged()),
                             this, SLOT(onTextChanged()));
        }
    }
}

bool FileTabWidget::closeByIndex(int index) {
    if (tabText(index) == "Welcome") {
        removeTab(index);
        return true;
    }
    auto *editor = dynamic_cast<TextEditor *>(widget(index));
    if (editor) {
        if (not editor->isChangedSaved()) {
            switch (CustomMessageBoxes::CloseUnsavedFileChoice(tabText(index).remove("*"))) {
                case QMessageBox::Yes:
                    Save(index);
                    break;
                case QMessageBox::Close:
                    return false;
                case QMessageBox::Discard:
                    break;
                default:
                    break;
            }
        }
        CustomMessage::print("Closing %1, which is %2", tabText(index),
                             (editor->isChangedSaved()? "saved" : "not saved"));
        removeTab(index);
        return true;
    }
    return false;
}

void FileTabWidget::onTextChanged() {
    auto *editor = dynamic_cast<TextEditor *>(sender());
    CustomMessage::print("%1 have been changed", tabText(indexOf(editor)));
    if (editor->isChangedSaved()) {
        editor->setChangesSaved(false);
        setTabText(indexOf(editor), tabText(indexOf(editor)) + "*");
    }
}

void FileTabWidget::onCursorPositionChanged() {
    auto *editor = dynamic_cast<TextEditor *>(sender());
    QTextCursor cursor;
    if (editor) {
        cursor = editor->textCursor();
    }
    else {
        cursor = dynamic_cast<TextEditor *>(currentWidget())->textCursor();
    }
    auto position = cursor.position();
    cursor.movePosition(QTextCursor::StartOfLine);
    auto column = position - cursor.position() + 1;
    auto line = 1;
    while (cursor.positionInBlock() > 0) {
        cursor.movePosition(QTextCursor::Up);
        line++;
    }
    QTextBlock block = cursor.block().previous();
    while (block.isValid()) {
        line += block.lineCount();
        block = block.previous();
    }
    emit cursorPositionChanged(line, column);
}


