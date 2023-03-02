#include "TextEditor.h"
#include <QFile>
#include <QWidget>
#include <QScrollBar>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include "CustomEnvironment/CustomContext.h"

bool TextEditor::isChangedSaved() const {
    return isChangesSaved;
}

void TextEditor::setChangesSaved(bool changesSaved) {
    TextEditor::isChangesSaved = changesSaved;
}

void TextEditor::saveChanges() {
    if (isChangedSaved()) {
        qDebug() << "Changes saved!";
        return;
    }
    else if (path.isEmpty()) {
        qDebug() << "Empty. Nothing to save!";
        return;
    }
    QFile file(path);
    if (not file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        CustomMessageBoxes::Error("Error with writing in file" + path + "'");
        qDebug() << "Error with saving";
        return;
    }
    file.write(toPlainText().toStdString().c_str());
    qDebug() << path << " was saved successfully";
    setChangesSaved(true);
}

bool TextEditor::saveAs() {
    path = CustomDialog::getPathToSave();
    if (path.isEmpty()) {
        CustomMessageBoxes::Warning("No file selected");
        qDebug() << "No path specified";
        return false;
    }
    saveChanges();
    return true;
}

TextEditor::TextEditor(QWidget *parent) : QTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    connect(this->document(), SIGNAL(blockCountChanged(int)),
            this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(updateLineNumberArea(int)));
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(updateLineNumberArea()));
    updateLineNumberAreaWidth(0);
    setCursor(Qt::IBeamCursor);
}

TextEditor::TextEditor(const QString &path, QWidget *parent) : QTextEdit(parent), path(path) {
    lineNumberArea = new LineNumberArea(this);
    connect(this->document(), SIGNAL(blockCountChanged(int)),
            this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(updateLineNumberArea(int)));
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(updateLineNumberArea()));
    updateLineNumberAreaWidth(0);
    qDebug() << "Opening file " << path;
    QFile file(path);
    if (not file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        CustomMessageBoxes::Error("Error in opening file " + path + "'");
        qDebug() << "Error in opening file " << path;
        return;
    }
    setText(file.readAll());
}

const QString &TextEditor::getFilePath() const {
    return path;
}

void TextEditor::setFilePath(const QString &FilePath) {
    path = FilePath;
}

int TextEditor::getFirstVisibleBlockId() {
    QTextCursor cursor = QTextCursor(document());
    cursor.movePosition(QTextCursor::Start);
    for (auto i = 0; i < document()->blockCount(); ++i) {
        QTextBlock block = cursor.block();
        QRect rect1 = viewport()->geometry();
        QRect rect2 = document()->documentLayout()->blockBoundingRect(block).
                                  translated(viewport()->geometry().x(),
                                             viewport()->geometry().y() -
                                                 verticalScrollBar()->sliderPosition()).toRect();
        if (rect1.contains(rect2, true)) {
            return i;
        }
        cursor.movePosition(QTextCursor::NextBlock);
    }
    return 0;
}

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
    verticalScrollBar()->setSliderPosition(verticalScrollBar()->sliderPosition());

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), backgroundLinesColor);
    auto blockNumber = getFirstVisibleBlockId();

    auto block = document()->findBlockByNumber(blockNumber);
    auto previous_block = (blockNumber > 0) ? document()->findBlockByNumber(blockNumber - 1) : block;
    auto translate_y = (blockNumber > 0) ? -verticalScrollBar()->sliderPosition() : 0;

    auto top = viewport()->geometry().top();

    int additional_margin;
    if (blockNumber == 0) {
        additional_margin = static_cast<int>(document()->documentMargin() - 1 - verticalScrollBar()->sliderPosition());
    }
    else {
        additional_margin = static_cast<int>(this->document()->documentLayout()->blockBoundingRect(previous_block).
                                             translated(0, translate_y).intersected(viewport()->geometry()).height());
    }

    top += additional_margin;

    auto bottom = top + static_cast<int>(document()->documentLayout()->blockBoundingRect(block).height());

    while (block.isValid() and top <= event->rect().bottom()) {
        if (block.isVisible() and bottom >= event->rect().top()) {
            auto number = QString::number(blockNumber + 1);
            painter.setPen((textCursor().blockNumber() == blockNumber) ? currentLineColor : otherLinesColor);
            painter.drawText(-5, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(document()->documentLayout()->
                                        blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int TextEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 13 + fontMetrics().averageCharWidth() * (digits);
    return space;
}

void TextEditor::resizeEvent(QResizeEvent *e) {
    QTextEdit::resizeEvent(e);
    QRect rect = contentsRect();
    auto left = rect.left();
    auto top = rect.top();
    auto height = rect.height();
    auto width = lineNumberAreaWidth();
    lineNumberArea->setGeometry(left, top, width, height);
}

void TextEditor::updateLineNumberAreaWidth(int newBlockCount) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void TextEditor::updateLineNumberArea(QRectF) {
    TextEditor::updateLineNumberArea();
}

void TextEditor::updateLineNumberArea() {
    verticalScrollBar()->setSliderPosition(verticalScrollBar()->sliderPosition());
    QRect rect = this->contentsRect();
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    updateLineNumberAreaWidth(0);
    int y = verticalScrollBar()->sliderPosition();
    if (y > -1) {
        lineNumberArea->scroll(0, y);
    }
    int first_id = getFirstVisibleBlockId();
    if (first_id == 0 or textCursor().block().blockNumber() == first_id - 1) {
        verticalScrollBar()->setSliderPosition(y - document()->documentMargin());
    }
}

void TextEditor::updateLineNumberArea(int) {
    TextEditor::updateLineNumberArea();
}