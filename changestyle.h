#ifndef CHANGESTYLE_H
#define CHANGESTYLE_H

#include <QIcon>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "findwindow.h"
#include "ui_findwindow.h"
#include "dialog_new.h"
#include "ui_dialog_new.h"


class ChangeStyle
{
public:
    ChangeStyle();

public :

    static void ChangeWhite(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog);

    static void ChangePink(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog);

    static void ChangeOrange(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog);

    static void ChangeColorful(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog);

    static void ChangeDarkBlue(Ui::MainWindow * ui , MainWindow * mainwindow , Ui::FindWindow * findwindow_ui , FindWindow * findwindow , Ui::Dialog_new * dialog_ui , Dialog_new * dialog);

};

#endif // CHANGESTYLE_H
