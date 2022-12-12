#include "highlight.h"
#include <mainwindow.h>
Highlighter::Highlighter(QTextDocument *parent)//构造函数，主要是对词语的高亮
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;//高亮规则


    keywordFormat.setForeground(Qt::darkBlue);//设定关键词的高亮样式(如int)
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;//关键词集合,关键都以正则表达式表示

    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";
    foreach (const QString &pattern, keywordPatterns)//添加各个关键词到高亮规则中
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    keyFormat.setForeground(Qt::red);//设定关键词的高亮样式
    keyFormat.setFontWeight(QFont::Normal);
    QStringList keywordPatterns1;//关键词集合,关键都以正则表达式表示
    keywordPatterns1 << "\\*"<< "\\("<< "\\)"<< "\\{"<< "\\}"<< "\\["<< "\\]"<<";"<<","<<"\\+"<<"-"<<"=";
    foreach (const QString &pattern, keywordPatterns1)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keyFormat;
        highlightingRules.append(rule);
    }


    keyFormat1.setForeground(QColor(0,180,0));
    keyFormat1.setFontWeight(QFont::Normal);
    QStringList keywordPatterns2;
    keywordPatterns2 << "\\#"<< "\\binclude\\b";
    foreach (const QString &pattern, keywordPatterns2)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keyFormat1;
        highlightingRules.append(rule);
    } 


    numFormat.setForeground(QColor(150,0,128));
    numFormat.setFontWeight(QFont::Normal);
    QStringList keywordPatterns3;
    keywordPatterns3 << "0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9";
    foreach (const QString &pattern, keywordPatterns3)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = numFormat;
        highlightingRules.append(rule);
    }


    singleLineFormat.setForeground(Qt::darkGreen);//单行注释
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineFormat;
    highlightingRules.append(rule);

    multiLineFormat.setForeground(Qt::darkGreen);//多行注释，只设定了样式，具体匹配在highlightBlock中设置

    stringFormat.setForeground(Qt::darkGreen);//字符串
    rule.pattern = QRegExp("\".*\"");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);//函数
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");//多行注释的匹配正则表达式
    commentEndExpression = QRegExp("\\*/");
}


void Highlighter::highlightBlock(const QString &text)//应用高亮规则，也用于区块的高亮，比如多行注释
{
    foreach (const HighlightingRule &rule, highlightingRules)//文本采用高亮规则
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }


    setCurrentBlockState(0);//以下是多行注释的匹配


    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);


    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

//used in editor
void MainWindow::setupEditor()
{
}
