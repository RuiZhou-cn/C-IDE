#include "findwindow.h"
#include "ui_findwindow.h"

FindWindow::FindWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindWindow)
{
    ui->setupUi(this);
}

FindWindow::~FindWindow()
{
    delete ui;
}


void FindWindow::on_btn_back_clicked()
{
    this->close();
}



void FindWindow::on_btn_find_all_clicked()
{
    QString str = ui->lineEdit_find->text();
    emit sendString_For_FindAll(str);
}

void FindWindow::on_btn_find_Next_clicked()
{
    QString str = ui->lineEdit_find->text();
    emit sendString(str,true);//传输true代表查找后一个
}

void FindWindow::on_btn_find_Previous_clicked()
{
    QString str = ui->lineEdit_find->text();
    emit sendString(str,false);
}

void FindWindow::on_btn_replace_clicked()
{
    QString originalString = ui->lineEdit_find->text();
    QString updateString = ui->lineEdit_replace->text();
    emit replaceString(originalString,updateString,1);//mode=1代表逐个替换
}

void FindWindow::on_btn_replace_all_clicked()
{
    QString originalString = ui->lineEdit_find->text();
    QString updateString = ui->lineEdit_replace->text();
    emit replaceString(originalString,updateString,2);//mode=2代表全部替换
}

void FindWindow::closeEvent(QCloseEvent *event)
{
    emit closeFindWindow();
}
