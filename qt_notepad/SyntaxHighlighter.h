#pragma once
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QDebug>

class SyntaxHighlighter : public QSyntaxHighlighter {
Q_OBJECT

private:
    struct Rule {
        QRegularExpression pattern;
        QTextCharFormat     format;
    };
    struct MultilineRule {
        QRegularExpression BeginPattern;
        QRegularExpression   EndPattern;
        QTextCharFormat          format;
    };

    QMap<QStringList, QList<Rule>>   HighlightingRules;
    QMap<QStringList, MultilineRule> MultilineHighlightingRules;

    MultilineRule currentMR;
    QList<Rule>   currentHR;

    bool isExtensionHighlightable = false;

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);
    void ReadRules();

public slots:
    void SetExtension(const QString& file = QString());

protected:
    void highlightBlock(const QString& text) override;
};
