#ifndef DIALOG_NEW_H
#define DIALOG_NEW_H
#include "file_textedit.h"
#include <QDialog>
#include <QString>
#include <QAbstractButton>
#include <QDebug>

class MainWindow;
class File_textedit;
namespace Ui {
class Dialog_new;
}

class Dialog_new : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_new(QWidget *parent = 0);
    ~Dialog_new();
    QString filename;
    bool if_flag;
    File_textedit *text_E;
private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

public:
    Ui::Dialog_new *ui;
    MainWindow *m_parent;
};

#endif // DIALOG_NEW_H
