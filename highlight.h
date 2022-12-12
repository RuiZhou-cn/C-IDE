#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H
#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter//继承自QSyntaxHightliaghter
{
    Q_OBJECT


public:
    Highlighter(QTextDocument *parent = 0);//构造函数，传递一个QTextDocument对象给其父类


protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;//块高亮使用的函数，自动调用

private:
    struct HighlightingRule//语法规则结构体，包含正则表达式模式串和匹配的样式
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;//规则集，可定义多个高亮规则

    QRegExp commentStartExpression;//注释的高亮，使用highliangBlock()匹配
    QRegExp commentEndExpression;
    //关键词的高亮
    QTextCharFormat keywordFormat;
    QTextCharFormat keyFormat;
    QTextCharFormat keyFormat1;
    QTextCharFormat numFormat;//数字
    QTextCharFormat singleLineFormat;//单行注释
    QTextCharFormat multiLineFormat;//多行注释
    QTextCharFormat stringFormat;//字符串
    QTextCharFormat functionFormat;//函数
};

#endif // HIGHLIGHT_H
