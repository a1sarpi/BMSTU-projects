#include "CustomContext.h"
#include <QFile>
#include <QTabWidget>
#include <QHeaderView>
#include <QAbstractButton>
#include <QLayout>

QString CustomDialog::getPathToOpen() {
    return QFileDialog::getOpenFileName(nullptr, "Choose file");
}

QString CustomDialog::getPathToSave() {
    return QFileDialog::getSaveFileName(nullptr, "Saving file");
}

void CustomMessageBoxes::Error(const QString &message) {
    QMessageBox message_box(QMessageBox::Icon::Critical, "Error",
                            message, QMessageBox::Close);
}

void CustomMessageBoxes::Warning(const QString &message) {
    QMessageBox message_box(QMessageBox::Icon::Warning, "Warning",
                            message, QMessageBox::Close);
    message_box.exec();
    CustomMessage::print("[Info] " + message);
}

void CustomMessageBoxes::Info(const QString &message) {
    QMessageBox message_box(QMessageBox::Icon::Information, "Information",
                            message, QMessageBox::Close);
    message_box.exec();
    CustomMessage::print("[Info] " + message);
}

int CustomMessageBoxes::CloseUnsavedFileChoice(const QString &path) {
    QMessageBox message_box(QMessageBox::Icon::Question, "Unsaved file",
                            QString("Are you really want to close unsaved file " +  path + "\nSave changes?"),
                            QMessageBox::Discard | QMessageBox::Yes | QMessageBox::Close);
    return message_box.exec();
}

bool CustomMessageBoxes::AcceptMessage(const QString &message) {
    QMessageBox message_box(QMessageBox::Icon::Question, "Accepting",
                            QString("Are you really want " + message + "?"),
                            QMessageBox::Yes | QMessageBox::No);
    return message_box.exec() == QMessageBox::Yes;
}

MultipleUnsaved::MultipleUnsaved(const QVector<QPair<QString, QString>> &unsaved, QWidget *parent) : QDialog(parent) {
    setGeometry(0, 0, 500, 300);
    setWindowTitle("Multiple Unsaved Files");
    label = new QLabel(this);
    label->setText("Those files unsaved: ");
    DialogButtonBox = new QDialogButtonBox(this);
    DialogButtonBox->setStandardButtons(QDialogButtonBox::NoButton);
    DialogButtonBox->addButton("Select All", QDialogButtonBox::ButtonRole::ActionRole);
    DialogButtonBox->addButton("Remove Selection", QDialogButtonBox::ButtonRole::ActionRole);
    DialogButtonBox->addButton("Cancel", QDialogButtonBox::ButtonRole::RejectRole);
    DialogButtonBox->addButton("Save Selection", QDialogButtonBox::ButtonRole::AcceptRole);
    UnsavedFilesTable = new QTableWidget(this);
    UnsavedFilesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UnsavedFilesTable->setRowCount(unsaved.count());
    UnsavedFilesTable->setColumnCount(2);
    UnsavedFilesTable->verticalHeader()->hide();
    UnsavedFilesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    QStringList HeaderLabels;
    HeaderLabels << "Name" << "Path";
    UnsavedFilesTable->setHorizontalHeaderLabels(HeaderLabels);
    auto i{0};
    for (const auto &[file, path]: unsaved) {
        auto *fItem = new QTableWidgetItem();
        fItem->setData(Qt::DisplayRole, file);
        UnsavedFilesTable->setItem(i, 0, fItem);
        auto *pItem = new QTableWidgetItem();
        pItem->setData(Qt::DisplayRole, path);
        UnsavedFilesTable->setItem(i, 1, pItem);
        i++;
    }
    UnsavedFilesTable->resizeColumnsToContents();
    QFile stylesheet(":/styles.qss");
    if (stylesheet.open(QIODevice::ReadOnly)) {
        auto style = stylesheet.readAll();
        setStyleSheet(style);
    }
    dialog_widget = new QWidget(this);
    dialog_layout = new QVBoxLayout(dialog_widget);

    dialog_layout->addWidget(label);
    dialog_layout->addWidget(UnsavedFilesTable);
    dialog_layout->addWidget(DialogButtonBox);
    dialog_widget->setLayout(dialog_layout);

    connect(DialogButtonBox, SIGNAL(clicked(QAbstractButton *)),
            this, SLOT(onButtonClicked(QAbstractButton *)));
}

QPair<bool, QVector<bool>> MultipleUnsaved::execute() {
    auto r = exec();
    QVector<bool> result;
    if (r) {
        auto selection = UnsavedFilesTable->selectedItems();
        for (auto i = 0; i < UnsavedFilesTable->rowCount(); ++i) {
            auto *name = UnsavedFilesTable->item(i, 0);
            auto *path = UnsavedFilesTable->item(i, 1);
            result << (selection.contains(name) or selection.contains(path));
        }
        return {true, result};
    }
    else {
        return {false, result};
    }
}

void MultipleUnsaved::onButtonClicked(QAbstractButton *button) {
    auto ButtonText = button->property("text").toString();
    if (ButtonText == "Select All") {
        qDebug() << "Yes to all";
        UnsavedFilesTable->selectAll();
    }
    else if (ButtonText == "Remove Selection") {
        qDebug() << "No to all";
        UnsavedFilesTable->clearSelection();
    }
    else if (ButtonText == "Cancel") {
        qDebug() << "cancel";
        setResult(0);
        reject();
    }
    else if (ButtonText == "Save Selection") {
        qDebug() << "apply";
        setResult(1);
        accept();
    }
    else {
        setResult(0);
        reject();
    }
}
