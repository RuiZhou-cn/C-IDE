#ifndef FILE_TEXTEDIT_H
#define FILE_TEXTEDIT_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVector>
#include <QStringList>
#include <QStringListModel>
#include <QCompleter>
#include <QString>
#include <QComboBox>
#include <QAbstractItemModel>
#include <QLabel>
#include <QProgressBar>
#include "textedit.h"
#include <QMainWindow>
#include <QTextCursor>
#include "highlight.h"


class File_textedit : public QWidget
{
    Q_OBJECT

public:
    int position1=0;//前括号位置
    int position2=0;//后括号位置
    explicit File_textedit(QWidget *parent = nullptr);
    int lastLine;
    TextEdit *text;
    QTextEdit *lineNumber;
    QString strAll;

    void cancel();//删除括号颜色
    void Color();
    void setColor(int position,int i);
    void onTextChange();
    void onCursorPositionChanged();
    //字体类
    QFont font;

    void retract();
    void replaceForRetract();

public:
    bool eventFilter(QObject *obj, QEvent *event);//定义鼠标滚轮事件过滤
    void scanBrackets();//扫描全文大括号
    QList<QVector<int>> bracketsList;//大括号对应行数列表
    int ishide[100]={0};
    QTextBlock cur_block;//文本的区块
    QTextBlock cur_line;//行号的区块
    QTextDocument* doc;//文本的内容
    QTextDocument* cnt;//行号的内容
    void fold();//点击行号折叠
    void unfold();//点击行号展开

private:
    //代码补全所需要的变量
    QAbstractItemModel *modelFromFile(const QString &fileName);
    QCompleter *completer;
    //高亮类
    Highlighter *highlighter;


signals:
    void add();

public slots:
    void addBracket();
    void change();

private:
    virtual void timerEvent(QTimerEvent * event)    {        this->retract();    }
};

#endif // FILE_TEXTEDIT_H
