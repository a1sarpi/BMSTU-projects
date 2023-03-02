#include "XML_Model.h"

XML_Model::XML_Model(QObject *parent) : QAbstractItemModel(parent) {
    main_root = new QStandardItem();
}

void XML_Model::XMLLoad(const QDomNode &element, QStandardItem *root) {
    auto next = element.firstChild();
    while (not next.isNull()) {
        if (next.isElement()) {
            auto elem = next.toElement();
            if (not elem.isNull()) {
                QString name = elem.tagName();
                QStandardItem *elem_item = nullptr;
                if (extract_map.contains(name)) {
                    auto children = elem.childNodes();
                    auto toExtractTag = extract_map.value(name);
//                    qDebug() << "to extract: "<<toExtractTag;
                    for (auto i = 0; i < children.count(); ++i) {
                        auto checkName = children.item(i).toElement().tagName();
//                        qDebug() << "checking " << checkName;
                        if (toExtractTag == checkName) {
                            elem_item = new QStandardItem(children.item(i).toElement().text());
                            break;
                        }
                    }
                }
                else {
                    elem_item = new QStandardItem(name);
                }
                if (name != "ExtractionMap") {
                    root->appendRow(elem_item);
                }
                createAttributesNodes(elem, elem_item);
                if(hasChildren(elem)) {
                    XMLLoad(elem, elem_item);
                }
                else {
                    createTextNode(elem, elem_item);
                }
            }
        }
        next = next.nextSibling();
    }
}

bool XML_Model::hasChildren(const QDomElement &element) const {
    return (!element.firstChild().toElement().text().isEmpty());
}

QStringList XML_Model::readAttributes(const QDomElement &element) const {
    auto attribute_map = element.attributes();
    QStringList attribute_list;
    for (auto i = 0; i < attribute_map.size(); ++i) {
        auto item = attribute_map.item(i).toAttr();
        attribute_list << item.nodeName() + "='" + item.nodeValue() + "'";
    }
    return attribute_list;
}

void XML_Model::createAttributesNodes(const QDomElement &element, QStandardItem *item) {
    if (element.hasAttributes()) {
        auto *attribute_item = new QStandardItem(readAttributes(element).join(' '));
        item->appendColumn({attribute_item});
    }
}

void XML_Model::createTextNode(const QDomElement &element, QStandardItem *item) const {
    auto *text_item = new QStandardItem(element.text());
    item->appendRow(text_item);
}


QModelIndex XML_Model::index(int row, int column, const QModelIndex &parent) const {
    if (hasIndex(row, column, parent)) {
        QStandardItem *parent_item;
        if(parent.isValid()) {
            parent_item = static_cast<QStandardItem *>(parent.internalPointer());
        }
        else {
            parent_item = main_root;
        }
        QStandardItem *child_item = parent_item->child(row, column);
        if (child_item) {
            return createIndex(row, column, child_item);
        }
    }
    return QModelIndex();

}

QModelIndex XML_Model::parent(const QModelIndex &child) const {
    if (not child.isValid()) {
        return QModelIndex();
    }
    QStandardItem *child_item = static_cast<QStandardItem *>(child.internalPointer());
    QStandardItem *parent_item = child_item->parent();
    if (not parent_item or parent_item == main_root) {
        return QModelIndex();
    }
    return createIndex(parent_item->row(), 0, parent_item);
}

int XML_Model::rowCount(const QModelIndex &parent) const {
    QStandardItem *parent_item;
    if (parent.column() > 0) {
        return 0;
    }
    if (parent.isValid()) {
        parent_item = static_cast<QStandardItem *>(parent.internalPointer());
    }
    else {
        parent_item = main_root;
    }
    return parent_item->rowCount();
}

int XML_Model::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return static_cast<QStandardItem *>(parent.internalPointer())->columnCount();
    }
    return main_root->columnCount();
}

QVariant XML_Model::data(const QModelIndex &index, int role) const {
   if (not index.isValid()) {
       return  QVariant();
   }
   if (role != Qt::DisplayRole) {
       return  QVariant();
   }
   auto *item = static_cast<QStandardItem *>(index.internalPointer());
   return item->data(role);
}

bool XML_Model::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (not index.isValid()) {
        return false;
    }
    auto *item = static_cast<QStandardItem *>(index.internalPointer());
    if (role == Qt::EditRole) {
        item->setData(value, Qt::EditRole);
        emit dataChanged(index, index, {role});
    }
    return false;
}

bool XML_Model::insertRows(int row, int count, const QModelIndex &parent) {
    QStandardItem *item = nullptr;
    QModelIndex correct_parent;
    if(parent.isValid()) {
        item = static_cast<QStandardItem *>(parent.internalPointer());
        correct_parent = parent;
    }
    else {
        item           = main_root;
        correct_parent = QModelIndex();
    }
    beginInsertRows(correct_parent, row, row + count + 1);
    for (auto i = 0; i < count; ++i) {
        item->insertRow(row, new QStandardItem(QString::number(i)));
    }
    endInsertRows();
    return true;
}

bool XML_Model::removeRows(int row, int count, const QModelIndex &parent) {
    QStandardItem *item = nullptr;
    QModelIndex correct_parent;
    if (parent.isValid()) {
        item = static_cast<QStandardItem *>(parent.internalPointer());
        correct_parent = parent;
    }
    else {
        item = main_root;
        correct_parent = QModelIndex();
    }
    auto start = row;
    beginRemoveRows(correct_parent, start, start + count - 1);
    item->removeRows(start, count);
    endRemoveRows();
    return true;
}

void XML_Model::append(const QModelIndex &index) {
    if (index.isValid()) {
        beginResetModel();
        auto *cloned_item = static_cast<QStandardItem *>(index.internalPointer())->clone();
        main_root->appendRow(cloned_item);
        append(index, cloned_item);
        endResetModel();
    }
}

void XML_Model::readExtractionMap(const QDomElement &element) {
    auto map_element = element.elementsByTagName("ExtractionMap").at(0).toElement();
    auto extract_list = map_element.childNodes();
    for (auto i = 0; i < extract_list.count(); ++i) {
        auto extraction_rule = extract_list.item(i).toElement();
        auto attributes = extraction_rule.attributes();
        QString from;
        QString to;
        for (auto j = 0; j < attributes.size(); ++j) {
            auto item = attributes.item(j).toAttr();
            auto attr_name = item.nodeName();
            if (attr_name == "from") {
                from = item.nodeValue();
            }
            else if (attr_name == "to") {
                to = item.nodeValue();
            }
        }
//        qDebug() << "from " << from << " to " << to;
        extract_map.insert(from, to);
    }
}

bool XML_Model::loadFromFile(const QString &path) {
    QFile file(path, this);
    QFileInfo file_info(file);

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox message(QMessageBox::Icon::Critical, "Error",
                            "Error while opening or reading file '" + file_info.fileName() + "'",
                            QMessageBox::Close);
        message.exec();
        qDebug() << "error while opening or reading file (XML_Model.cpp:170)";
        return false;
    }
    else qDebug() << "Loading file... " << file_info.fileName() << " have been successfully opened";
    XML_file.setContent(file.readAll());
    auto *file_root = new QStandardItem(file_info.fileName());
    extract_map.clear();
    readExtractionMap(XML_file.documentElement());
    XMLLoad(XML_file.documentElement(), file_root);
    main_root->appendRow(file_root);

    QMessageBox message(QMessageBox::Icon::Information, "Success",
                        "File successfully read '" + file_info.fileName() + "'",
                        QMessageBox::Ok);

    message.exec();
    qDebug() << "File '" + file_info.fileName() + "' successfully loaded!";
    return true;
}

void XML_Model::append(const QModelIndex &index, QStandardItem *item) {
    if (index.isValid()) {
        for (auto i = 0; i < rowCount(index); ++i) {
            auto child = index.model()->index(i, 0, index);
            auto *cloned_item = static_cast<QStandardItem *>(child.internalPointer())->clone();
            item->appendRow(cloned_item);
            append(child, cloned_item);
        }
    }
}

