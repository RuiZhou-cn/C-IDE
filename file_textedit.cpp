#include "file_textedit.h"
#include "dialog_new.h"
#include "ui_dialog_new.h"
#include <QDebug>
#include <QScrollBar>
#include <QFontMetrics>
#include "highlight.h"
#include <QTimer>
#include <QTextDocument>


File_textedit::File_textedit(QWidget *parent) : QWidget(parent)
{
    text = new TextEdit();
    text->setLineWrapMode(QTextEdit::NoWrap);
    text->setStyleSheet("background-color:white");


    lineNumber = new QTextEdit();
    lineNumber->setStyleSheet("background-color:#fafafa;");
    lineNumber->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumber->horizontalScrollBar()->hide();
    lineNumber->insertPlainText(QStringLiteral("1\n"));
    lineNumber->setFocusPolicy(Qt::NoFocus);
    //lineNumber->setContextMenuPolicy(Qt::DefaultContextMenu);
    connect(text->verticalScrollBar(),&QScrollBar::valueChanged,[&](int value)
    {
        lineNumber->verticalScrollBar()->setValue(value);
    });

    QHBoxLayout *textlayout = new QHBoxLayout();
    textlayout->setContentsMargins(0,0,0,0);
    textlayout->setSpacing(0);
    textlayout->addWidget(lineNumber);
    textlayout->addWidget(text);

    this->setLayout(textlayout);

    QTimer * timer = new QTimer();
    connect(text,&QTextEdit::textChanged,this,&File_textedit::onTextChange);
    connect(text,&QTextEdit::cursorPositionChanged,this,&File_textedit::onCursorPositionChanged);
    connect(timer,&QTimer::timeout,this,&File_textedit::Color);

    timer->start(10);

    font.setPixelSize(15);
    font.setFamily("微软雅黑");
    lineNumber->setFont(font);
    text->setFont(font);
    lineNumber->setFixedWidth(lineNumber->font().pixelSize());
    lastLine = 1;

    //安装鼠标滚轮事件过滤器
    lineNumber->verticalScrollBar()->installEventFilter(this);
    text->verticalScrollBar()->installEventFilter(this);
    //折叠与展开
    connect(text,&QTextEdit::textChanged,this,&File_textedit::scanBrackets);
    //connect(text,&QTextEdit::cursorPositionChanged,this,&File_textedit::unfold);
    connect(lineNumber,&QTextEdit::cursorPositionChanged,this,&File_textedit::fold);
    //自动补全
    connect(text,&QTextEdit::textChanged,this,&File_textedit::change);
    connect(this,&File_textedit::add,this,&File_textedit::addBracket);


    //代码自动补全相关代码
    completer = new QCompleter();
    completer->setModel(modelFromFile(":/resource/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    text->setCompleter(completer);

    //高亮相关代码
    highlighter = new Highlighter(text->document());

    QBasicTimer * timer1  = new QBasicTimer();
    timer1->start(10,this);
}




void File_textedit::onTextChange()
{
    int Row = text->document()->lineCount();
    if(Row == lastLine)
        return;

    lineNumber->blockSignals(true);
    text->blockSignals(true);

    //方法1
    int countOfRow = 0;
    int temp = Row;
    while(temp != 0)
    {
        temp = temp/10;
        ++countOfRow;
    }
    lineNumber->setFixedWidth(lineNumber->font().pixelSize() * countOfRow );
    //lineNumber->setFixedWidth(50);
    //方法2
    lineNumber->clear();
    QString str;
    ++Row;
    for (int i = 1; i < Row-1; ++i)
    {
        str.append(QString("%1\n").arg(i));
    }
    str.append(QString::number(Row-1));
    lineNumber->setPlainText(str);
    //

    lastLine = text->document()->lineCount();

    lineNumber->verticalScrollBar()->setValue(text->verticalScrollBar()->value());
    lineNumber->blockSignals(false);
    text->blockSignals(false);
}

void File_textedit::onCursorPositionChanged()
{
    lineNumber->blockSignals(true);
    text->blockSignals(true);
    lineNumber->verticalScrollBar()->setValue(text->verticalScrollBar()->value());
    lineNumber->blockSignals(false);
    text->blockSignals(false);
}

bool File_textedit::eventFilter(QObject *obj, QEvent *event)//重写鼠标滚轮事件过滤器，实现放大缩小和平滑滚动
{
    if (obj == lineNumber->verticalScrollBar()||obj == text->verticalScrollBar())
    {
        if(event->type() == QEvent::Wheel)
        {
            QWheelEvent *event1 = static_cast<QWheelEvent *>(event);
            int cnt=event1->angleDelta().y();//鼠标滚轮的滚动角度
            int tempStep=text->verticalScrollBar()->value();//滚动条的位置
            int size=lineNumber->font().pixelSize();
            int countOfRow=0;
            int row=lineNumber->document()->lineCount();
            int temp = row;
            while(temp != 0)
            {
                temp = temp/10;
                ++countOfRow;
            }
            if(QApplication::keyboardModifiers() == Qt::ControlModifier)//在按住ctrl的情况下设置滚动条位置固定，放大缩小内容
            {
                if (cnt<0)//向下滚动
                {
                    text->verticalScrollBar()->setValue(tempStep*0.9);//使滚动条的位置相对固定
                    lineNumber->verticalScrollBar()->setValue(tempStep*0.9);//使滚动条的相对固定
                    text->verticalScrollBar()->setSingleStep(0);
                    if(size*0.9>12) size*=0.9;
                    font.setPixelSize(size);
                    lineNumber->setFont(font);
                    text->setFont(font);
                    lineNumber->setFixedWidth(lineNumber->font().pixelSize()*countOfRow);
                }
                else//向上滚动
                {
                    text->verticalScrollBar()->setValue(tempStep*1.1);//使滚动条的位置相对固定
                    lineNumber->verticalScrollBar()->setValue(tempStep*1.1);//使滚动条的位置相对固定
                    size*=1.1;
                    font.setPixelSize(size);
                    lineNumber->setFont(font);
                    text->setFont(font);
                    lineNumber->setFixedWidth(lineNumber->font().pixelSize()*countOfRow);

                }
            }
            else//在不按ctrl的情况下正常滚动
            {
                if (cnt<0)//向下滚动
                {
                    lineNumber->verticalScrollBar()->setSliderPosition(tempStep+20);//使滚动条的位置下移20
                    text->verticalScrollBar()->setSliderPosition(tempStep+20);//使滚动条的位置下移20

                }
                else//向上滚动
                {
                    lineNumber->verticalScrollBar()->setSliderPosition(tempStep-20);//使滚动条的位置上移20
                    text->verticalScrollBar()->setSliderPosition(tempStep-20);//使滚动条的位置上移20

                }
            }
            return true;
        }
    }
    //其它事件交基类处理
    return QWidget::eventFilter(obj, event);
}
//扫描全文大括号
void File_textedit::scanBrackets()
{
    bracketsList.clear();
    doc = text->document();
    cnt = lineNumber->document();
    //获取每一行的文本
    cur_block = doc->begin();
    cur_line = cnt->begin();
    QList<QString> everyLine;//每行文本的列表
    int rowCount=0;
    while (cur_block.isValid())
    {
        for (QTextBlock::iterator iter = cur_block.begin(); iter != cur_block.end(); iter++)
        {
            QTextFragment cur_fragment = iter.fragment();
            QTextFormat format = cur_fragment.charFormat();
            if (format.isCharFormat())
            {
                QString info = cur_fragment.text();
                everyLine.append(info);
                //qDebug()<<everyLine[rowCount];
                rowCount++;
            }
        }
        cur_block = cur_block.next();
        cur_line = cur_line.next();
    }
    //检测文本中的大括号，栈的思想
    QVector <int>  stack(100);
    int temp = 0;
    for(int i=0;i<rowCount;i++)
    {
        if(everyLine[i].contains("{",Qt::CaseSensitive)){
            stack[temp++]=i;
        }
        if(everyLine[i].contains("}",Qt::CaseSensitive))
        {
            QVector <int>  brack(3);
            brack[1]=i+1;
            brack[0]=stack[--temp]+1;
            bracketsList.append(brack);
        }
    }
    //输出对应行
    //    for(int i=0;i<bracketsList.size();i++)
    //    {
    //        qDebug()<<"第"<<i<<"组大括号"<<bracketsList[i][0]<<bracketsList[i][1];
    //    }
}


void File_textedit::fold()
{
    QTextCursor tc = lineNumber->textCursor();
    int tcline = tc.blockNumber() + 1;//获取光标所在行的行号
    qDebug()<<"光标位于"<<tcline;
    for(int i=0;i<bracketsList.size();i++)
    {
        qDebug()<<i;
        qDebug()<<bracketsList[i];
        qDebug()<<ishide[i];
        if(tcline == bracketsList[i][0]&&ishide[i] == 0)
        {
            // bracketsList[i][2] = 1;
            ishide[i] = 1;
            qDebug()<<bracketsList[i];
            for(int j=bracketsList[i][0];j<bracketsList[i][1]-1;j++)
            {
                cur_block = doc->findBlockByNumber(j);
                cur_block.setVisible(false);
                cur_line = cnt->findBlockByNumber(j);
                cur_line.setVisible(false);
            }
            text->viewport()->update();
            lineNumber->viewport()->update();
            doc->adjustSize();
            cnt->adjustSize();
            break;
        }
        else if(tcline == bracketsList[i][0]&&ishide[i]==1)
        {
            // bracketsList[i][2] = 0;
            ishide[i] = 0;
            qDebug()<<bracketsList[i];
            for(int j=bracketsList[i][0];j<bracketsList[i][1]-1;j++)
            {
                cur_block = doc->findBlockByNumber(j);
                cur_block.setVisible(true);
                cur_line = cnt->findBlockByNumber(j);
                cur_line.setVisible(true);
            }
            text->viewport()->update();
            lineNumber->viewport()->update();
            doc->adjustSize();
            cnt->adjustSize();
            break;
        }

    }
}

void File_textedit::change()//检测文本长度是否增加
{
    QString temp = text->toPlainText();
    if(temp.length()>strAll.length())
    {
        emit add();
    }
    temp = text->toPlainText();
    strAll = temp;
}

void File_textedit::addBracket()//如果文本长度增加，自动补全括号
{
    QTextCursor cursor(text->textCursor());
    int position=cursor.position();
    QString temp = text->toPlainText();
    if(position!=0)
    {
        if(temp.at(position-1)=="(")
        {
            cursor.insertText(")");
            cursor.setPosition(position);
            text->setTextCursor(cursor);
            // qDebug()<<"po"<<position;
            if(position-1==position2)//这个部分是和实现括号匹配相关的
                position2+=2;
        }
        else if(temp.at(position-1)=="[")
        {
            cursor.insertText("]");
            cursor.setPosition(position);
            text->setTextCursor(cursor);
            if(position-1==position2)
                position2+=2;
        }
        else if(temp.at(position-1)=="{")
        {
            cursor.insertText("}");
            cursor.setPosition(position);
            text->setTextCursor(cursor);
            if(position-1==position2)
                position2+=2;
        }
    }

}

void File_textedit::Color()//实现括号画图
{
    QTextCursor cursor(text->textCursor());
    int position = cursor.position();
    QString temp = text->toPlainText();
    int index = 0;
    cancel();
    if(temp.length()>position && temp.at(position)=="(")
    {
        //           qDebug()<<temp.length()<<position;
        if(temp.length()>position && temp.at(position)=="(")
        {
            //      qDebug()<<temp.length()<<position;
            for(int i=position+1;i<temp.length();i++)
            {
                if(temp.at(i)=="(")
                {
                    index++;
                }
                else if(temp.at(i)==")")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        setColor(position,i);
                        break;
                    }
                }
            }
        }
        else if(temp.length()>position && temp.at(position)=="{")
        {
            //      qDebug()<<temp.length()<<position;
            for(int i=position+1;i<temp.length();i++)
            {
                if(temp.at(i)=="{")
                {
                    index++;
                }
                else if(temp.at(i)=="}")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        setColor(position,i);
                        break;
                    }
                }
            }
        }
        else if(temp.length()>position && temp.at(position)=="[")
        {
            //    qDebug()<<temp.length()<<position;
            for(int i=position+1;i<temp.length();i++)
            {
                if(temp.at(i)=="[")
                {
                    index++;
                }
                else if(temp.at(i)=="]")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        setColor(position,i);
                        break;
                    }
                }
            }
        }
        else if(temp.length()>position && temp.at(position)==")")
        {
            if(position ==0 )
                cancel();
            //     qDebug()<<temp.length()<<position;
            for(int i=position-1;i>=0;i--)
            {
                if(temp.at(i)==")")
                {
                    index++;
                }
                else if(temp.at(i)=="(")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        //             qDebug()<<"i"<<i;
                        setColor(i,position);
                        break;
                    }
                }
            }
        }
        else if(temp.length()>position && temp.at(position)=="}")
        {
            if(position == 0 )
                cancel();
            //       qDebug()<<temp.length()<<position;
            for(int i=position-1;i>=0;i--)
            {
                if(temp.at(i)=="}")
                {
                    index++;
                }
                else if(temp.at(i)=="{")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        //            qDebug()<<"i"<<i;
                        setColor(i,position);
                        break;
                    }
                }
            }
        }
        else if(temp.length()>position && temp.at(position)=="]")
        {
            if(position ==0 )
                cancel();
            //    qDebug()<<temp.length()<<position;
            for(int i=position-1;i>=0;i--)
            {
                if(temp.at(i)=="]")
                {
                    index++;
                }
                else if(temp.at(i)=="[")
                {
                    if(index>0)
                    {
                        index--;
                    }
                    else
                    {
                        cancel();
                        //            qDebug()<<"i"<<i;
                        setColor(i,position);
                        break;
                    }
                }
            }
        }
    }
    else if(temp.length()>position && temp.at(position)=="[")
    {
        //    qDebug()<<temp.length()<<position;
        for(int i=position+1;i<temp.length();i++)
        {
            if(temp.at(i)=="[")
            {
                index++;
            }
            else if(temp.at(i)=="]")
            {
                if(index>0)
                {
                    index--;
                }
                else
                {
                    cancel();
                    setColor(position,i);
                    break;
                }
            }
        }
    }
    else if(temp.length()>position && temp.at(position)==")")
    {
        if(position ==0 )
            cancel();
        //     qDebug()<<temp.length()<<position;
        for(int i=position-1;i>=0;i--)
        {
            if(temp.at(i)==")")
            {
                index++;
            }
            else if(temp.at(i)=="(")
            {
                if(index>0)
                {
                    index--;
                }
                else
                {
                    cancel();
                    //             qDebug()<<"i"<<i;
                    setColor(i,position);
                    break;
                }
            }
        }
    }
    else if(temp.length()>position && temp.at(position)=="]")
    {
        if(position ==0 )
            cancel();
        //    qDebug()<<temp.length()<<position;
        for(int i=position-1;i>=0;i--)
        {
            if(temp.at(i)=="]")
            {
                index++;
            }
            else if(temp.at(i)=="[")
            {
                if(index>0)
                {
                    index--;
                }
                else
                {
                    cancel();
                    //            qDebug()<<"i"<<i;
                    setColor(i,position);
                    break;
                }
            }
        }
    }
    else
    {
        if(position1>temp.length())
            position1=0;
        if(position2>temp.length())
            position2=0;
        cancel();
    }
}

void File_textedit::setColor(int position,int i)
{
    //  qDebug()<<"1";
    QString str = text->toPlainText();
    if(str.at(position)=="("||str.at(position)=="["||str.at(position)==")"||str.at(position)=="]")
    {
        QTextCursor cursor = text->textCursor();
        cursor.setPosition(position);
        cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
        QTextCharFormat defcharfmt = text->currentCharFormat();
        QTextCharFormat newcharfmt = defcharfmt;
        //newcharfmt.setForeground(QColor("#00B2EE"));
        newcharfmt.setBackground(QColor("#FFE4E1"));
        cursor.mergeCharFormat(newcharfmt);
        position1 = position;
    }
    if(str.at(i)==")"||str.at(i)=="]"||str.at(i)=="("||str.at(i)=="[")
    {
        QTextCursor cursor1 = text->textCursor();
        cursor1.setPosition(i);
        cursor1.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
        QTextCharFormat defcharfmt = text->currentCharFormat();
        QTextCharFormat newcharfmt = defcharfmt;
        //newcharfmt.setForeground(QColor("#00B2EE"));
        newcharfmt.setBackground(QColor("#FFE4E1"));
        cursor1.mergeCharFormat(newcharfmt);
        position2 = i;
    }
}

void File_textedit::cancel()
{
    //QString str = ui->textEdit->toPlainText();
    QTextCursor cursor3(text->textCursor());

    cursor3.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    QTextCharFormat defcharfmt = text->currentCharFormat();
    QTextCharFormat newcharfmt = defcharfmt;
    newcharfmt.setBackground(QColor("#FFFFFF"));
    cursor3.mergeCharFormat(newcharfmt);
    //    qDebug()<<position1<<"p1";
    QTextCursor cursor(text->textCursor());
    cursor.setPosition(position1);
    cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    //QTextCharFormat defcharfmt = ui->textEdit->currentCharFormat();
    //QTextCharFormat newcharfmt = defcharfmt;
    newcharfmt.setBackground(QColor("#FFFFFF"));
    cursor.mergeCharFormat(newcharfmt);
    //   qDebug()<<position2<<"p2";
    QTextCursor cursor1 = text->textCursor();
    cursor1.setPosition(position2);
    cursor1.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    newcharfmt.setBackground(QColor("#FFFFFF"));
    cursor1.mergeCharFormat(newcharfmt);
}




QAbstractItemModel *File_textedit::modelFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, completer);
}


void File_textedit::retract()
{
    QTextCursor cursor=text->textCursor();
    int temp = 0;
    QString k, k1, k2;
    k = text->toPlainText();

    cursor.movePosition(QTextCursor::Start);
    while(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::Right);
        int charIndex1 = cursor.position();
        k1 = text->toPlainText().left(charIndex1);
        k2 = text->toPlainText().right(k.length()-charIndex1);

        if(k1.right(2) == "{\n")
        {
            if(k2.left(1)=="}" && k1.right(2) == "{\n"){
                cursor.deletePreviousChar();
                replaceForRetract();
            }
        }

    }
}



void File_textedit::replaceForRetract()
{
    QTextDocument::FindFlags flags;
    flags |= QTextDocument::FindBackward;

    QTextDocument * document = text->document();
    QTextCursor textCursor = text->textCursor();

    int pos = textCursor.position();
    textCursor.setPosition(pos+1);
    text->setTextCursor(textCursor);

    textCursor = text->textCursor();

    QString str = "{}";
    QString updateString = "{\n          \n}";

    do
    {
        textCursor = document->find( str , textCursor , flags);
        if ( textCursor.isNull() )//如果没找到字符
        {
            qDebug()<<"NIHAO";
        }

        if ( textCursor.hasSelection() )//如果找到了
        {
            qDebug()<<"nihao";
            textCursor.insertText( updateString.replace("\\n","\n") );
        }
        else{

        }

    } while ( !textCursor.isNull() );

    textCursor = text->textCursor();
    pos = textCursor.position();
    textCursor.setPosition(pos-2);
    text->setTextCursor(textCursor);

    text->ensureCursorVisible();
    text->setFocus();
}

