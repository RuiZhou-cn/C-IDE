#include "changestyle.h"

ChangeStyle::ChangeStyle()
{

}

void ChangeStyle::ChangeWhite(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog)
{
    mainwindow->setStyleSheet("background-color: rgb(245,245,245);");
    ui->tabWidget_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->tabWidget_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->treeMenu->setStyleSheet("background-color: rgb(245,245,245);");
    ui->menuBar->setStyleSheet("background-color: rgb(245, 245, 245); selection-background-color:#808080;");
    ui->mainToolBar->setStyleSheet("background-color: rgb(245,245,245);");
    findwindow->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Previous->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Next->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_all->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_replace->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_replace_all->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_back->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);");

    ui->action_tool_new->setIcon(QIcon(":/img/newFile.png"));
    ui->action_tool_save->setIcon(QIcon(":/img/saveFile.png"));
    ui->action_tool_copy->setIcon(QIcon(":/img/copy.png"));
    ui->action_tool_cut->setIcon(QIcon(":/img/cut.png"));
    ui->action_tool_paste->setIcon(QIcon(":/img/paste.png"));
    ui->action_tool_open->setIcon(QIcon(":/img/openFile.png"));
    ui->action_tool_close->setIcon(QIcon(":/img/closeFile.png"));
    ui->action_tool_run->setIcon(QIcon(":/img/Run.png"));
    ui->action_tool_Debug->setIcon(QIcon(":/img/Debug.png"));
}

void ChangeStyle::ChangePink(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog)
{
    mainwindow->setStyleSheet("background-color:#FFE7EC;");
    ui->tabWidget_1->setStyleSheet("background-color: #F2C6C4;");
    ui->tabWidget_2->setStyleSheet("background-color: #F2C6C4;");
    ui->treeMenu->setStyleSheet("background-color: #F5CECE;");
    ui->menuBar->setStyleSheet("background-color: rgb(255,192,203);selection-background-color:#D47F85;");
    ui->mainToolBar->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow->setStyleSheet("background-color: #FFE7EC;");
   // dialog->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Previous->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->btn_find_Next->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->btn_find_all->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->btn_replace->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->btn_replace_all->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->btn_back->setStyleSheet("background-color: rgb(255,192,203);");
    findwindow_ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);");

    ui->action_tool_new->setIcon(QIcon(":/img/newFile_pink.png"));
    ui->action_tool_save->setIcon(QIcon(":/img/saveFile_pink.png"));
    ui->action_tool_copy->setIcon(QIcon(":/img/copy_pink.png"));
    ui->action_tool_cut->setIcon(QIcon(":/img/cut_pink.png"));
    ui->action_tool_paste->setIcon(QIcon(":/img/paste_pink.png"));
    ui->action_tool_open->setIcon(QIcon(":/img/openFile_pink.png"));
    ui->action_tool_close->setIcon(QIcon(":/img/closeFile_pink.png"));
    ui->action_tool_run->setIcon(QIcon(":/img/Run_pink.png"));
    ui->action_tool_Debug->setIcon(QIcon(":/img/debug_pink.png"));
}

void ChangeStyle::ChangeOrange(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog)
{
    mainwindow->setStyleSheet("background-color:#E9D0B3;");
    ui->tabWidget_1->setStyleSheet("background-color: #F2CDAC;");
    ui->tabWidget_2->setStyleSheet("background-color: #F2CDAC;");
    ui->treeMenu->setStyleSheet("background-color: #F2CDAC;");
    ui->menuBar->setStyleSheet("background-color: #F2CDAC;selection-background-color:#E39372;");
    ui->mainToolBar->setStyleSheet("background-color: #F2CDAC;");
    findwindow->setStyleSheet("background-color: #E9D0B3;");
   // dialog->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Previous->setStyleSheet("background-color: #F2CDAC;");
    findwindow_ui->btn_find_Next->setStyleSheet("background-color: #F2CDAC;");
    findwindow_ui->btn_find_all->setStyleSheet("background-color: #F2CDAC;");
    findwindow_ui->btn_replace->setStyleSheet("background-color: #F2CDAC;");
    findwindow_ui->btn_replace_all->setStyleSheet("background-color: #F2CDAC;");
    findwindow_ui->btn_back->setStyleSheet("background-color:#F2CDAC;");
    findwindow_ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);");

    ui->action_tool_new->setIcon(QIcon(":/img/newFile_yellow.png"));
    ui->action_tool_save->setIcon(QIcon(":/img/saveFile_yellow.png"));
    ui->action_tool_copy->setIcon(QIcon(":/img/copy_yellow.png"));
    ui->action_tool_cut->setIcon(QIcon(":/img/cut_yellow.png"));
    ui->action_tool_paste->setIcon(QIcon(":/img/paste_yellow.png"));
    ui->action_tool_open->setIcon(QIcon(":/img/openFile_yellow.png"));
    ui->action_tool_close->setIcon(QIcon(":/img/closeFile_yellow.png"));
    ui->action_tool_run->setIcon(QIcon(":/img/Run_yellow.png"));
    ui->action_tool_Debug->setIcon(QIcon(":/img/debug_yellow.png"));
}

void ChangeStyle::ChangeDarkBlue(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog)
{

    mainwindow->setStyleSheet("background-color:#7284AB;");
    ui->tabWidget_1->setStyleSheet("background-color: #48536B;");
    ui->tabWidget_2->setStyleSheet("background-color: #48536B;");
    ui->treeMenu->setStyleSheet("background-color: #9DB6EB;");
    ui->menuBar->setStyleSheet("background-color: #9DB6EB;selection-background-color:#404A5F;");
    ui->mainToolBar->setStyleSheet("background-color: #939EBF;");
    findwindow->setStyleSheet("background-color: #7284AB;");
   // dialog->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Previous->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->btn_find_Next->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->btn_find_all->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->btn_replace->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->btn_replace_all->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->btn_back->setStyleSheet("background-color: #404A5F;color:rgb(255,255,255)");
    findwindow_ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);color:rgb(255,255,255)");
    findwindow_ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);color:rgb(255,255,255)");

    ui->action_tool_new->setIcon(QIcon(":/img/newFile_blue.png"));
    ui->action_tool_save->setIcon(QIcon(":/img/saveFile_blue.png"));
    ui->action_tool_copy->setIcon(QIcon(":/img/copy_blue.png"));
    ui->action_tool_cut->setIcon(QIcon(":/img/cut_blue.png"));
    ui->action_tool_paste->setIcon(QIcon(":/img/paste_blue.png"));
    ui->action_tool_open->setIcon(QIcon(":/img/openFile_blue.png"));
    ui->action_tool_close->setIcon(QIcon(":/img/closeFile_blue.png"));
    ui->action_tool_run->setIcon(QIcon(":/img/Run_blue.png"));
    ui->action_tool_Debug->setIcon(QIcon(":/img/debug_blue.png"));
}

void ChangeStyle::ChangeColorful(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog)
{
    mainwindow->setStyleSheet("background-color:#AECFBA;");
    ui->tabWidget_1->setStyleSheet("background-color: #FFDACC;");
    ui->tabWidget_2->setStyleSheet("background-color: #FFDACC;");
    ui->treeMenu->setStyleSheet("background-color: #FFF3C2;");
    ui->menuBar->setStyleSheet("background-color: #AEDFF2;selection-background-color:#599DD9;");
    ui->mainToolBar->setStyleSheet("background-color: #AEDFF2;");
    findwindow->setStyleSheet("background-color: #AECFBA;");
   // dialog->setStyleSheet("background-color: rgb(245,245,245);");
   // dialog_ui->buttonBox->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->btn_find_Previous->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->btn_find_Next->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->btn_find_all->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->btn_replace->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->btn_replace_all->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->btn_back->setStyleSheet("background-color: #8EBD9F;");
    findwindow_ui->lineEdit_find->setStyleSheet("background-color: rgb(255,255,255);");
    findwindow_ui->lineEdit_replace->setStyleSheet("background-color: rgb(255,255,255);");

    ui->action_tool_new->setIcon(QIcon(":/img/newFile.png"));
    ui->action_tool_save->setIcon(QIcon(":/img/saveFile.png"));
    ui->action_tool_copy->setIcon(QIcon(":/img/copy.png"));
    ui->action_tool_cut->setIcon(QIcon(":/img/cut.png"));
    ui->action_tool_paste->setIcon(QIcon(":/img/paste.png"));
    ui->action_tool_open->setIcon(QIcon(":/img/openFile.png"));
    ui->action_tool_close->setIcon(QIcon(":/img/closeFile.png"));
    ui->action_tool_run->setIcon(QIcon(":/img/Run.png"));
    ui->action_tool_Debug->setIcon(QIcon(":/img/Debug.png"));
}


