#pragma once

#include <QDebug>
#include <QTextEdit>

class TextEditor : public QTextEdit {
Q_OBJECT

private:
    QString path;
    bool isChangesSaved = true;
    QWidget *lineNumberArea;
    QColor currentLineColor = QColor("#4fa08b");
    QColor otherLinesColor      = QColor("#d3dae3");
    QColor backgroundLinesColor = QColor("#151a1e");

public:
    bool isChangedSaved() const;
    void setChangesSaved(bool changesSaved);
    void saveChanges();
    bool saveAs();

    explicit TextEditor(QWidget *parent = nullptr);
    TextEditor(const QString &path, QWidget *parent = nullptr);

    const QString &getFilePath() const;
    void setFilePath(const QString &FilePath);

    int getFirstVisibleBlockId();

    void lineNumberAreaPaintEvent(QPaintEvent *event);

    int lineNumberAreaWidth();

public slots:
    void resizeEvent(QResizeEvent *e) override;

private slots:
    void updateLineNumberAreaWidth(int);
    void updateLineNumberArea(QRectF);
    void updateLineNumberArea(int);
    void updateLineNumberArea();

};

// Класс, определяющий область строки
class LineNumberArea : public QWidget {
Q_OBJECT
private:
    QTextEdit *code_editor;

protected:
    void paintEvent(QPaintEvent *event) override {
        (qobject_cast<TextEditor *>(code_editor))->lineNumberAreaPaintEvent(event);
    }

public:
    explicit LineNumberArea(QTextEdit *editor) : QWidget(editor) {
        code_editor = editor;
    }

    QSize sizeHint() const {
        return {qobject_cast<TextEditor *>(code_editor)->lineNumberAreaWidth(), 0};
    }

};