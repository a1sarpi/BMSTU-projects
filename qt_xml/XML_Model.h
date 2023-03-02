#pragma once
#include <QAbstractItemModel>
#include <QStandardItem>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>


class XML_Model : public QAbstractItemModel {
private:
    QStandardItem *main_root;
    QMap<QString, QString> extract_map;

    QDomDocument XML_file;

    void XMLLoad(const QDomNode &element, QStandardItem *root);

    bool hasChildren(const QDomElement &element) const;

    QStringList readAttributes(const QDomElement &element) const;

    void createAttributesNodes(const QDomElement &element, QStandardItem *item);
    void createTextNode(const QDomElement &element, QStandardItem *item) const;

    void append(const QModelIndex &index, QStandardItem *);




public:
    explicit XML_Model(QObject *parent);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void readExtractionMap(const QDomElement &element);

    bool loadFromFile(const QString &path);

    void append(const QModelIndex &index);

};
