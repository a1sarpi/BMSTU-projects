#include "SyntaxHighlighter.h"
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QFileInfo>
#include <algorithm>
#include "CustomEnvironment/CustomContext.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    ReadRules();
}

void SyntaxHighlighter::highlightBlock(const QString &text) {
    if (isExtensionHighlightable) {
        for (auto &rule: qAsConst(currentHR)) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
        setCurrentBlockState(0);
        int start_index = 0;
        if (previousBlockState() != 1) {
            start_index = text.indexOf(currentMR.BeginPattern);
        }
        while (start_index >= 0) {
            QRegularExpressionMatch match = currentMR.EndPattern.match(text, start_index);
            auto end_index = match.capturedStart();
            auto comment_length = 0;
            if (end_index == -1) {
                setCurrentBlockState(1);
                comment_length = text.length() - start_index;
            }
            else {
                comment_length = end_index - start_index + match.capturedLength();
            }
            setFormat(start_index, comment_length, currentMR.format);
            start_index = text.indexOf(currentMR.BeginPattern, start_index + comment_length);
        }
    }
}

void SyntaxHighlighter::ReadRules() {
    QFile file(":/highlight_rules.xml");
    QDomDocument document;
    if (not file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Error", "Error while reading highlight rules");
        qDebug() << "Failed opening 'highlight_rules.xml'";
        return;
    }
    QString error_message;
    int line, column;
    if (not document.setContent(&file, &error_message, &line, &column)) {
        error_message += "Error at: (" + QString::number(line) + ", " +
                         QString::number(column) + ")";
        qDebug() << error_message;
        return;
    }
    QDomElement top_element = document.documentElement();
    auto syntaxes = top_element.firstChild().childNodes();
    for (auto i = 0; i < syntaxes. count(); ++i) {
        auto syntax = syntaxes.at(i).toElement();
        auto extensions = syntax.attribute("extensions").split(' ');
        auto rules = syntax.childNodes();
        QList<Rule> syntax_rule_list;
        for (auto j = 0; j < rules.count(); ++j) {
            Rule rule;
            auto rule_element = rules.at(j).toElement();
            if (rule_element.hasAttribute("comment")) {
                MultilineRule MR;
                MR.BeginPattern = QRegularExpression(rule_element.elementsByTagName("beginPattern").
                                                                       at(0).toElement().attribute("value"));
                MR.EndPattern   = QRegularExpression(rule_element.elementsByTagName("endPattern").
                                                                       at(0).toElement().attribute("value"));
                MR.format.setFontWeight(rule_element.elementsByTagName("format").at(0).toElement().
                                                                                 attribute("font_weight").toInt());
                MR.format.setForeground(QColor(rule_element.elementsByTagName("format").at(0).
                                                                             toElement().attribute("foreground")));
                MultilineHighlightingRules[extensions] = MR;
            }
            else {
                auto format = rule_element.elementsByTagName("format").at(0);
                rule.format.setFontWeight(format.toElement().attribute("font_weight").toInt());
                rule.format.setForeground(QColor(format.toElement().attribute("foreground")));
                auto patterns = rule_element.elementsByTagName("pattern");
                for (auto k = 0; k < patterns.count(); ++k) {
                    auto pattern = patterns.at(k);
                    rule.pattern = QRegularExpression(pattern.toElement().attribute("value"));
                    syntax_rule_list.append(rule);
                }
            }
        }
        HighlightingRules[extensions] = syntax_rule_list;
    }
}

void SyntaxHighlighter::SetExtension(const QString &file) {
    QFileInfo info(file);
    auto extension = info.completeSuffix();
    extension.remove("*");
    const QList<QStringList> &keys = HighlightingRules.keys();
    auto result = std::find_if(keys.begin(), keys.end(), [&](const QStringList &extensions) {
        return extensions.contains(extension);
    });
    if (result != keys.end()) {
        CustomMessage::print("Extension " + extension + "supported");
        currentHR = HighlightingRules[*result];
        if (MultilineHighlightingRules.contains(*result)) {
            currentMR = MultilineHighlightingRules[*result];
        }
        isExtensionHighlightable = true;
    }
    else {
        CustomMessage::print("Extension " + extension + " not supported");
        isExtensionHighlightable = false;
    }
}
