#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlight.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QToolButton>
#include <QStatusBar>
#include <QDockWidget>
#include <QDebug>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
//文件相关操作引用的头文件
#include <QFileDialog>
#include <QFileDevice>
#include <QFile>
#include <QMessageBox>
#include <QtEvents>
#include <QTextStream>

//
#include <QTimer>
#include <QString>
#include <QColor>
#include <QTextCursor>
//
#include <QTextCodec>
//
#include "findwindow.h"
#include <QTextDocument>
//
#include <QFileInfo>
#include <treemenu.h>
#include "file_textedit.h"
#include "dialog_new.h"
#include <QTabWidget>
//
#include <QProcess>
#include <QInputDialog>
#include "changestyle.h"

int flag_isOpen = 0;
int flag_isNew = 0;
QString Last_FileName;
QString Last_FileContent;
bool debugflag=false;
//
QString k1;
int temp = 0;
QTextCodec *codec;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //新加入的
    ui->tabWidget_1->setTabsClosable(true);
    connect(ui->tabWidget_1,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    //双击目录文件显示在tab中
    connect(ui->treeMenu,SIGNAL(showTextSignal(QString,QString)),this,SLOT(showTextOnTab(QString,QString)));
    //添加新文件到目录中
    connect(this,SIGNAL(newfile()),this,SLOT(addfiletotree()));
    //菜单栏关闭
    connect(this,SIGNAL(close(int)),this,SLOT(removeSubTab(int)));

    QStatusBar* statusBar = this->statusBar();
    QLabel* timeLabel = new QLabel("时间：");
    statusBar->addWidget(timeLabel);
    QLabel* rowLabel = new QLabel("行：");
    statusBar->addWidget(rowLabel);
    QLabel* colLabel = new QLabel("列：");
    statusBar->addWidget(colLabel);


    //tab_widget2的布局
    QVBoxLayout *tab2layout = new QVBoxLayout();
        tab2layout->setContentsMargins(0,0,0,0);
        tab2layout->addWidget(ui->textEditOutput);
        ui->tab_3->setLayout(tab2layout);
        QVBoxLayout *tab3layout = new QVBoxLayout();
            tab3layout->setContentsMargins(0,0,0,0);
            tab3layout->addWidget(ui->textEditOutput_2);
            ui->tab_4->setLayout(tab3layout);


    this->findWindow = new FindWindow();
    connect(this->findWindow,&FindWindow::closeFindWindow,this,&MainWindow::closeFun);
    connect(this->findWindow,SIGNAL(sendString(QString,bool)),this,SLOT(findText(QString,bool)));
    connect(this->findWindow,SIGNAL(sendString_For_FindAll(QString)),this,SLOT(findAllText(QString)));
    connect(this->findWindow,SIGNAL(replaceString(QString,QString,int)),this,SLOT(replaceText(QString,QString,int)));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);


    codec = QTextCodec::codecForName("GBK");
    QBasicTimer * timer2 = new QBasicTimer();
    timer2->start(10,this);

    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadData()));
    connect(&m_process, SIGNAL(readyReadStandardError()) , this, SLOT(onreaderror()));
    connect(&m_process2, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadData2()));
    connect(&m_process2, SIGNAL(readyReadStandardError()) , this, SLOT(onreaderror2()));



    ui->textEditOutput->setStyleSheet("background-color:white");
    ui->textEditOutput_2->setStyleSheet("background-color:white");

    this->setStyleSheet("background-color: rgb(245,245,245);");
    ui->tabWidget_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->tabWidget_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->treeMenu->setStyleSheet("background-color: rgb(245,245,245);");
    ui->menuBar->setStyleSheet("background-color: rgb(245, 245, 245); selection-background-color:#808080;");
    ui->mainToolBar->setStyleSheet("background-color: rgb(245,245,245);");
    this->findWindow->setStyleSheet("background-color: rgb(245,245,245);");
    //dialog->setStyleSheet("background-color: rgb(245,245,245);");
    //dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_find_Previous->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_find_Next->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_find_all->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_replace->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_replace_all->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->btn_back->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);");
    this->findWindow->ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::EditOutput()
{
    if(flag1 == 0){
        ui->tabWidget_2->show();

        flag1 = 1;
    }
    else{
        ui->tabWidget_2->hide();
        flag1 = 0;
    }
}

void MainWindow::FileView()
{
    if(flag2 == 0){
        ui->treeMenu->show();
        flag2 = 1;
    }
    else{
        ui->treeMenu->hide();
        flag2 = 0;
    }
}

void MainWindow::addfiletotree()
{
    ui->treeMenu->clear();
    ui->treeMenu->CreateTopItem(fatherpath);

}

void MainWindow::showTextOnTab(QString path, QString name)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    File_textedit *new_widget = new File_textedit();
    ui->tabWidget_1->addTab(new_widget,name);
    QTextStream textStream(&file);  //浣跨敤QTextStream璇诲彇鏂囦欢
    textStream.setCodec("utf-8");
    while(!textStream.atEnd())
    {
        new_widget->text->setPlainText(textStream.readAll());
    }
    new_widget->text->show();
    file.close();
    QFileInfo fileInfo;
    fileInfo = QFileInfo(path);
    flag_isOpen = 1;
    flag_isNew = 0;
    Last_FileName = path;

}

void MainWindow::on_action_tool_new_triggered() //menubar中的创建新文件
{
    flag_isNew = 1;
    flag_isOpen = 1;
    Dialog_new * dialog_new = new Dialog_new(this);
    dialog_new->show();
}

void MainWindow::on_actionNewFile_triggered()   //menubar中的创建新文件
{
    flag_isNew = 1;
    flag_isOpen = 1;
    Dialog_new * dialog_new = new Dialog_new(this);
    dialog_new->show();
}

void MainWindow::on_actionOpenFile_triggered()  //menubar中的打开文件
{
    QString fileName, filePath;
    QFileInfo fileInfo;
    fileName = QFileDialog::getOpenFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;C++ File(*.cpp)");
    fileInfo = QFileInfo(fileName);
    filePath = fileInfo.absolutePath();
    ui->treeMenu->clear();
    ui->treeMenu->CreateTopItem(filePath);
    extern QString fatherpath;
    fatherpath = filePath;
    if(fileName == "")  //用户如果直接关闭文件浏览对话框则文件名为空值，直接返回
    {
        return ;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","打开文件错误!");
            return;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","此文件不可读!");
            else
            {
                File_textedit *new_widget = new File_textedit();
                ui->tabWidget_1->addTab(new_widget,fileInfo.fileName());
                QTextStream textStream(&file);  //使用QTextStream读取文件
                textStream.setCodec("utf-8");
                while(!textStream.atEnd())
                {
                    new_widget->text->setText(textStream.readAll());
                }
                new_widget->text->show();
                file.close();
                flag_isOpen = 1;
                flag_isNew = 0;
                Last_FileName = fileName;
            }
        }

    }
}

void MainWindow::on_actionSaveFileAs_triggered()    //menubar中的另存为
{
    //获取当前tab的textedit
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    QFileDialog fileDialog;

    QString fileName = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;CPP File(*.cpp)");
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"error","打开文件失败!");
        return;
    }
    else
    {
        QTextStream textStream(&file);
        textStream.setCodec("utf-8");
        QString str = tt->toPlainText();
        textStream<<str;
        QMessageBox::warning(this,"tip","成功保存!");
        Last_FileContent = str;
        Last_FileName = fileName;
        flag_isNew = 0;
        file.close();
    }
}

void MainWindow::on_actionSaveFile_triggered()  //menubar中的保存文件
{
    //获取当前tab的textedit
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    if(flag_isNew)  //如果新文件标记位为1，则弹出保存文件对话框
    {
        if(tt->toPlainText()=="")
        {
            QMessageBox::warning(this,"error","内容不能为空!",QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;C++ File(*.cpp)");
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","打开文件错误!");
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                textStream.setCodec("utf-8");
                QString str = tt->toPlainText();
                textStream << str;
                Last_FileContent =str;
            }
            QMessageBox::information(this,"Save File","成功保存",QMessageBox::Ok);
            filename.close();
            flag_isNew = 0; //鏂版枃浠舵爣璁颁綅涓?
            Last_FileName = str;    //淇濆瓨鏂囦欢鍐呭
        }
    }
    else    //鍚﹀垯鏂版枃浠舵爣璁颁綅鏄?锛屼唬琛ㄦ棫鏂囦欢锛岄粯璁ょ洿鎺ヤ繚瀛樿鐩栨簮鏂囦欢
    {
        if(flag_isOpen) //鍒ゆ柇鏄惁鎵撳紑鎴栧垱寤轰簡涓€涓枃浠?
        {
            QFile file(Last_FileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","打开文件错误");
                return;
            }
            else
            {
                QTextStream textString(&file);              
                textString.setCodec("utf-8");
                QString str = tt->toPlainText();
                textString << str;
                Last_FileContent = str;
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,"Warning","请新建或打开文件");
            return;
        }

    }
}

void MainWindow::on_actionQuit_triggered()  //menubar中的关闭文件
{
    int index = ui->tabWidget_1->currentIndex();
    emit close(index);
}

void MainWindow::closeEvent(QCloseEvent* event) //关闭窗口时弹出的提醒
{
    int count = ui->tabWidget_1->count();
    int ret = QMessageBox::warning(this, tr("IDE"), tr("是否保存对文档的修改?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
    if (ret == QMessageBox::Save)
    {
        // 接受了 要关闭这个窗口的事件. accept和ignore只是作为一个标志.
        for(int i = 0; i < count; i++)
        {
            QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
            QTextEdit *tt = textlist.takeAt(1);
            if(flag_isNew)  //如果新文件标记位为1，则弹出保存文件对话框
            {
                if(tt->toPlainText()=="")
                {
                    QMessageBox::warning(this,"error","内容不能为空!",QMessageBox::Ok);
                }
                else
                {
                    QFileDialog fileDialog;
                    QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;C++ File(*.cpp)");
                    if(str == "")
                    {
                        return;
                    }
                    QFile filename(str);
                    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"error","打开错误!");
                        return;
                    }
                    else
                    {
                        QTextStream textStream(&filename);
                        textStream.setCodec("utf-8");
                        QString str = tt->toPlainText();
                        textStream << str;
                        Last_FileContent =str;
                    }
                    QMessageBox::information(this,"Ssve File","成功保存",QMessageBox::Ok);
                    filename.close();
                    flag_isNew = 0; //新文件标记位为0
                    Last_FileName = str;    //保存文件内容
                }
            }
            else    //否则新文件标记位是0，代表旧文件，默认直接保存覆盖源文件
            {
                if(flag_isOpen) //判断是否打开或创建了一个文件
                {
                    QFile file(Last_FileName);
                    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"error","打开错误");
                        return;
                    }
                    else
                    {
                        QTextStream textString(&file);
                        textString.setCodec("utf-8");
                        QString str = tt->toPlainText();
                        textString << str;
                        Last_FileContent = str;
                        file.close();
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Warning","请新建或打开文件");
                    return;
                }

            }
            event->accept();
        }

    }
    else if (ret == QMessageBox::Discard)
    {
        //忽略了 要关闭这个窗口的事件.当前窗口就不会被关闭.
        exit(0);
    }
    else if (ret == QMessageBox::Cancel)
    {
        event->ignore();
    }
}

void MainWindow::on_action_tool_close_triggered()   //maintoolbar中的关闭
{
    int index = ui->tabWidget_1->currentIndex();
    emit close(index);
}

void MainWindow::on_action_tool_open_triggered()    //maintoolbar中的打开文件
{
    QString fileName, filePath;
    QFileInfo fileInfo;
    fileName = QFileDialog::getOpenFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;C++ File(*.cpp)");
    fileInfo = QFileInfo(fileName);
    filePath = fileInfo.absolutePath();
    ui->treeMenu->clear();
    ui->treeMenu->CreateTopItem(filePath);
    if(fileName == "")  //用户如果直接关闭文件浏览对话框则文件名为空值，直接返回
    {
        return ;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","打开错误!");
            return;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","此文件不可读!");
            else
            {
                File_textedit *new_widget = new File_textedit();
                ui->tabWidget_1->addTab(new_widget,fileInfo.fileName());
                QTextStream textStream(&file);  //使用QTextStream读取文件
                textStream.setCodec("utf-8");
                while(!textStream.atEnd())
                {
                    new_widget->text->setPlainText(textStream.readAll());
                }
                new_widget->text->show();
                file.close();
                flag_isOpen = 1;
                Last_FileName = fileName;
            }
        }

    }
}

void MainWindow::on_action_tool_copy_triggered()    //maintoolbar中的粘贴
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    tt->copy();
}

void MainWindow::on_action_tool_cut_triggered()     //maintoolbar中的剪切
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    tt->cut();
}

void MainWindow::on_actionCopy_triggered()  //menubar中的复制
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    tt->copy();
}

void MainWindow::on_actionPaste_triggered() //menubar中的粘贴
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    tt->paste();
}

void MainWindow::on_actionCut_triggered()   //menubar中的剪切
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    tt->cut();
}

void MainWindow::on_actionReverse_triggered()   //menubar中的撤销
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    qDebug()<<"used";
    tt->undo();
}


void MainWindow::removeSubTab(int index)
{
    //获取当前tab的textedit
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit *tt = textlist.takeAt(1);
    //当文档内容被修改时.
    if (tt->document()->isModified())
    {
        int ret = QMessageBox::warning(this, tr("IDE"), tr("是否保存对文件的修改?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
        if (ret == QMessageBox::Save)
        {
            // 接受了 要关闭这个窗口的事件. accept和ignore只是作为一个标志.
            if(flag_isNew)  //如果新文件标记位为1，则弹出保存文件对话框
            {
                if(tt->toPlainText()=="")
                {
                    QMessageBox::warning(this,"error","文件内容不能为空!",QMessageBox::Ok);
                }
                else
                {
                    QFileDialog fileDialog;
                    QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt);;C File(*.c);;C++ File(*.cpp)");
                    if(str == "")
                    {
                        return;
                    }
                    QFile filename(str);
                    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"error","打开文件错误!");
                        return;
                    }
                    else
                    {
                        QTextStream textStream(&filename);
                        textStream.setCodec("utf-8");
                        QString str = tt->toPlainText();
                        textStream << str;
                        Last_FileContent =str;
                    }
                    QMessageBox::information(this,"Ssve File","成功保存",QMessageBox::Ok);
                    filename.close();
                    flag_isNew = 0; //新文件标记位为0
                    Last_FileName = str;    //保存文件内容
                    emit newfile();
                }
            }
            else    //否则新文件标记位是0，代表旧文件，默认直接保存覆盖源文件
            {
                if(flag_isOpen) //判断是否打开或创建了一个文件
                {
                    qDebug()<<Last_FileName;
                    QFile file(Last_FileName);
                    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"error","打开错误");
                        return;
                    }
                    else
                    {
                        QTextStream textString(&file);
                        textString.setCodec("utf-8");
                        QString str = tt->toPlainText();
                        textString << str;
                        Last_FileContent = str;
                        file.close();
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Warning","请新建或打开文件");
                    return;
                }

            }
            ui->tabWidget_1->removeTab(index);
        }
        else if (ret == QMessageBox::Discard)
        {
            ui->tabWidget_1->removeTab(index);
        }
        else if (ret == QMessageBox::Cancel)
        {
            return;
        }
    }
    else
    {
        ui->tabWidget_1->removeTab(index);
    }

}

void MainWindow::on_actiontext_view_triggered()
{
    this->FileView();
    qDebug()<<"file view";
}

void MainWindow::on_actionedit_view_triggered()
{
    this->EditOutput();
    qDebug()<<"please edit";
}


void MainWindow::on_action_tool_save_triggered()
{

}



void MainWindow::on_actionsearch_triggered()
{
    this->findWindow->show();
}

//实现逐个查找
void MainWindow::findText(QString str, bool next)
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit * textedit = textlist.takeAt(1);

    //有1个问题
    //向前查找不能连续两个而且中间有换行
    if(str.isEmpty()==true){
        QMessageBox::information(this,"提示","没有输入文字",QMessageBox::Ok);
        return ;
    }

    QTextDocument::FindFlags flags;
    if ( next==false ){
        qDebug()<<"false";
        flags |= QTextDocument::FindBackward;
    }


    QTextDocument * document = textedit->document();
    QTextCursor textCursor = textedit->textCursor();

    do
    {
        textCursor = document->find( str , textCursor , flags);


        if ( textCursor.isNull() )//如果没找到字符
        {
            //如果next=true即查找下一个，则将光标移动到开头
            //如果next=false即查找上一个，则将光标移动到结尾
            textedit->moveCursor( next ? QTextCursor::Start : QTextCursor::End, QTextCursor::MoveAnchor );

            //更新textCursor
            textCursor = textedit->textCursor();

            //继续查找
            textCursor = document->find( str , textCursor , flags);
        }


        if ( textCursor.hasSelection() )//如果找到了
        {
            //将文本的光标放在相应的位置
            textedit->setTextCursor( textCursor );
            QPalette palette = textedit->palette();
            palette.setColor(QPalette::Highlight,QColor("yellow"));
            //palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
            textedit->setPalette(palette);
            //暂停查找
            break;
        }
        else{
            //执行到这一步说明真的没有找到
            //QMessageBox::information(this,"结果",QString("没有找到字符串'%1'").arg(str),QMessageBox::Ok);
        }

    } while ( !textCursor.isNull() );

    textedit->ensureCursorVisible();
    textedit->setFocus();

}

//实现全部查找
void MainWindow::findAllText(QString str)
{
    int count = 0;
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit * textedit = textlist.takeAt(1);
    textedit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor); //将光标置于开始位置
    while(textedit->find(str)){
        count++;
    }
    QMessageBox::information(this,"结果",QString("一共找到'%1'个字符串'%2'").arg(count).arg(str),QMessageBox::Ok);
}

//实现替换与全部替换
void MainWindow::replaceText(QString originalString, QString updateString, int mode)
{
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit * textedit = textlist.takeAt(1);
    if(mode==1){//mode=1代表逐个替换

        QTextCursor textCursor = textedit->textCursor();
        if ( textCursor.hasSelection() ){
            textCursor.insertText( updateString );
        }

        //findText(originalString,true);
    }
    else if(mode==2){//mode=2代表全部替换
        textedit->moveCursor( QTextCursor::Start, QTextCursor::MoveAnchor );

        findText(originalString,true);

        textedit->textCursor().beginEditBlock();
        while ( textedit->textCursor().hasSelection() )
        {
            textedit->textCursor().insertText( updateString );
            findText(originalString,true);
        }
        textedit->textCursor().endEditBlock();
    }
}

//设置查询页面关闭的相应函数，在查询页面关闭后响应
void MainWindow::closeFun(){
    QList<QTextEdit*> textlist = ui->tabWidget_1->currentWidget()->findChildren<QTextEdit*>();
    QTextEdit * textedit = textlist.takeAt(1);

    //将滑动选择的填充颜色改为之前的颜色
    QPalette palette = textedit->palette();
    palette.setColor(QPalette::Highlight,QColor(0,120,215));//之前系统默认的选中的颜色
    textedit->setPalette(palette);
}





void MainWindow::on_actionChangeWhite_triggered()
{
    ChangeStyle::ChangeWhite(this->ui,this,this->findWindow->ui,this->findWindow,this->dlg_dialog->ui,this->dlg_dialog);
}

void MainWindow::on_actionChangePink_triggered()
{
    //换肤接口
    ChangeStyle::ChangePink(this->ui,this,this->findWindow->ui,this->findWindow,this->dlg_dialog->ui,this->dlg_dialog);
}

void MainWindow::on_actionChangeOrange_triggered()
{
    //换肤接口
    ChangeStyle::ChangeOrange(this->ui,this,this->findWindow->ui,this->findWindow,this->dlg_dialog->ui,this->dlg_dialog);
}

void MainWindow::on_actionChangeColorful_triggered()
{
    //换肤接口
    ChangeStyle::ChangeColorful(this->ui,this,this->findWindow->ui,this->findWindow,this->dlg_dialog->ui,this->dlg_dialog);
}

void MainWindow::on_actionChangeDarkBlue_triggered()
{
    //换肤接口
    ChangeStyle::ChangeDarkBlue(this->ui,this,this->findWindow->ui,this->findWindow,this->dlg_dialog->ui,this->dlg_dialog);
}

//运行
/*void MainWindow::on_action_tool_run_triggered()
{
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        ui->textEditOutput->setText("edit Successfully");
        QString target = QString("cmd /k %1").arg(demo);
        system(codec->fromUnicode(target).data());
    }
    else
    {
        cmd = QString("cmd /k gcc %1 -o %2").arg(Last_FileName).arg(demo);
        system(codec->fromUnicode(cmd).data());
        ui->textEditOutput->setText("edit Successfully");
        return;
    }
}

void MainWindow::on_action_tool_Debug_triggered()
{
    this->EditOutput();
    qDebug()<<"please edit";

    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }

    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        ui->textEditOutput->setText("edit Successfully");
    }
    else
    {
        cmd = QString("cmd /k gcc %1 -o %2").arg(Last_FileName).arg(demo);
        system(codec->fromUnicode(cmd).data());
        ui->textEditOutput->setText("edit false");
        return;
    }
}*/


//----------------------------------------运行debug部分--------------------------------//

void MainWindow::onReadData()
{

}

void MainWindow::onReadData2()
{
    QString s1;
    s1=codec->QTextCodec::toUnicode (m_process2.readAllStandardOutput());
    ui->textEditOutput_2->insertPlainText(s1);
}

void MainWindow::onreaderror()
{
    QString s1;
    s1=codec->QTextCodec::toUnicode (m_process.readAllStandardError());
    s1=s1+"\n";
    ui->textEditOutput->insertPlainText(s1);
}

void MainWindow::onreaderror2()
{
    QString s1;
    s1=codec->QTextCodec::toUnicode (m_process2.readAllStandardError());
    s1=s1+"\n";
    ui->textEditOutput->insertPlainText(s1);
}

void MainWindow::on_action_edit_triggered()
{
    this->EditOutput();
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        ui->textEditOutput->setText("edit Successfully\n");
    }
    else
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        m_process.start(cmd);
    }
}

void MainWindow::on_action_run_triggered()
{
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        ui->textEditOutput->insertPlainText("edit Successfully\n");
        QString target = QString("cmd /k %1").arg(demo);
        system(codec->fromUnicode(target).data());
    }
    else
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        QString cmd = QString("cmd /c gcc %1 -o %2").arg(Last_FileName).arg(demo);
        m_process.start(cmd);
    }
}

void MainWindow::on_action_edit_run_triggered()
{
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        ui->textEditOutput->insertPlainText("edit Successfully\n");
        QString target = QString("cmd /k %1").arg(demo);
        system(codec->fromUnicode(target).data());
    }
    else
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        QString cmd = QString("cmd /c gcc %1 -o %2").arg(Last_FileName).arg(demo);
        m_process.start(cmd);
    }
}

void MainWindow::on_action_debug_triggered()
{
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc -gstabs -o %1 %2").arg(demo).arg(Last_FileName);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        ui->textEditOutput->insertPlainText("edit Successfully\n");
        QString target2 = QString("cmd /c gdb %1").arg(demo);
        m_process2.start(target2);
        m_process2.write("l 0\n");\
        debugflag = true;
    }
    else
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        QString cmd = QString("cmd /c gcc %1 -o %2").arg(Last_FileName).arg(demo);
        m_process.start(cmd);
    }
}

void MainWindow::on_action_addbreakpoint_triggered()
{
    if(debugflag)
    {
        QString s = QInputDialog::getText(this,tr("Input breakpoint"),tr("breakpoint line/function:"),QLineEdit::Normal,tr("1"),&debugflag);
        QString s2 = QString("b %1\n").arg(s);
        QByteArray a = s2.toLatin1();
        m_process2.write(a.data());
    }
}

void MainWindow::on_action_delete_triggered()
{
    if(debugflag)
    {
        QString s = QInputDialog::getText(this,tr("Input breakpoint"),tr("breakpoint number:"),QLineEdit::Normal,tr("1"),&debugflag);
        QString s2 = QString("d %1\n").arg(s);
        QByteArray a = s2.toLatin1();
        m_process2.write(a.data());
    }
}

void MainWindow::on_action_check_triggered()
{
    if(debugflag)
    {
        m_process2.write("info b\n");
    }
}

void MainWindow::on_action_tool_singleRun_triggered()
{
    if(debugflag)
    {
        m_process2.write("n\n");
    }
}

void MainWindow::on_action_tool_processRun_triggered()
{
    if(debugflag)
    {
        m_process2.write("s\n");
    }
}

void MainWindow::on_action_tool_RunWhileDebug_triggered()
{
    if(debugflag)
    {
        m_process2.write("r\n");
    }
}

void MainWindow::on_action_tool_search_triggered()
{
    if(debugflag)
    {
        QString s = QInputDialog::getText(this,tr("Input variable name"),tr("variable name:"),QLineEdit::Normal,tr("1"),&debugflag);
        QString s2 = QString("p %1\n").arg(s);
        QByteArray a = s2.toLatin1();
        m_process2.write(a.data());
    }
}

void MainWindow::on_action_tool_Exit_triggered()
{
    if(debugflag)
    {
        m_process2.write("q\n");
        m_process2.close();
        ui->textEditOutput_2->clear();
    }
}

void MainWindow::on_action_tool_run_triggered()
{
    if(Last_FileName=="")
    {
        this->on_actionSaveFileAs_triggered();
    }
    QString demo = Last_FileName;
    demo.replace(".c", "");
    QString cmd = QString("gcc %1 -o %2").arg(Last_FileName).arg(demo);
    int ret = system(codec->fromUnicode(cmd).data());
    if(ret==0)
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        ui->textEditOutput->insertPlainText("edit Successfully\n");
        QString target = QString("cmd /k %1").arg(demo);
        system(codec->fromUnicode(target).data());
    }
    else
    {
        QString s1;
        s1="-------------------------------------------------------\n";
        ui->textEditOutput->insertPlainText(s1);
        QString cmd = QString("cmd /c gcc %1 -o %2").arg(Last_FileName).arg(demo);
        m_process.start(cmd);
    }
}
