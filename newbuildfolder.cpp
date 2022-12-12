#include <newbuildfolder.h>
#include <QLabel>
#include <qapplication.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
NewBuildfolder::NewBuildfolder(QWidget *parent):QDialog(parent){
    QLabel *fileNameLabel = new QLabel("新建文件夹");
    fileNameEdit = new QLineEdit();
    okButton = new QPushButton("确定");
    cancalButton = new QPushButton("取消");
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    Hlayout1->addWidget(fileNameLabel);
    Hlayout1->addWidget(fileNameEdit);
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    Hlayout2->addWidget(okButton);
    Hlayout2->addWidget(cancalButton);
    QVBoxLayout *MainVlayout = new QVBoxLayout(this);
    MainVlayout->addLayout(Hlayout1);
    MainVlayout->addLayout(Hlayout2);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}


