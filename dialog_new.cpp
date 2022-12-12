#include "dialog_new.h"
#include "ui_dialog_new.h"
#include "file_textedit.h"
#include "mainwindow.h"

Dialog_new::Dialog_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_new)
{
    ui->setupUi(this);
    m_parent = static_cast<MainWindow*>(parent);
    setWindowTitle("新建");
    setModal(true);
    //if_flag = false;
}

Dialog_new::~Dialog_new()
{
    delete ui;
}

void Dialog_new::on_buttonBox_accepted()
{
    //if_flag = true;
    filename = ui->lineEdit_1->text();
    text_E = new File_textedit();

    m_parent->ui->tabWidget_1->addTab(text_E,filename);
}

void Dialog_new::on_buttonBox_rejected()
{
    //if_flag = false;
    return;
}

