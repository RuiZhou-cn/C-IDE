#include <QApplication>
#include <QLabel>
#include <newbuildfile.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
NewBulidFile::NewBulidFile(QWidget *parent):QDialog(parent){
    QLabel *fileNameLabel = new QLabel("文件名");
    QLabel *fileNameTypeLabel = new QLabel("文件类型");
    fileNameEdit = new QLineEdit();
    fileNameTypeBox = new QComboBox();
    fileNameTypeBox->addItem(".txt"); //这里可以多加几个Item,方法类似，用于新建文件时指定文件的类型
    fileNameTypeBox->addItem(".c"); //这里可以多加几个Item,方法类似，用于新建文件时指定文件的类型
    fileNameTypeBox->addItem(".cpp"); //这里可以多加几个Item,方法类似，用于新建文件时指定文件的类型
    QString surrfix = fileNameTypeBox->currentText();
    okButton = new QPushButton("确定");
    cancalButton = new QPushButton("取消");

    QString fullfilename = fileNameEdit->text() + surrfix;
    qDebug()<<fullfilename;
    QFile file(fileNameEdit->text());
    if(file.exists())
    {
        qDebug()<<"文件存在";
    }
    else
    {
        qDebug()<<"文件不存在,正在新建文件.";
        file.open( QIODevice::ReadWrite | QIODevice::Text );
        file.close();
    }
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    Hlayout1->addWidget(fileNameLabel);
    Hlayout1->addWidget(fileNameEdit);
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    Hlayout2->addWidget(fileNameTypeLabel);
    Hlayout2->addWidget(fileNameTypeBox);
    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    Hlayout3->addWidget(okButton);
    Hlayout3->addWidget(cancalButton);
    QVBoxLayout *MainVlayout = new QVBoxLayout(this); //布局使用嵌套布局
    MainVlayout->addLayout(Hlayout1);
    MainVlayout->addLayout(Hlayout2);
    MainVlayout->addLayout(Hlayout3);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}
