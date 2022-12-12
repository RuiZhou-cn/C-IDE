#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class FindWindow;
}

class FindWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindWindow(QWidget *parent = 0);
    ~FindWindow();

public:
    Ui::FindWindow *ui;

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_btn_back_clicked();

    void on_btn_find_all_clicked();

    void on_btn_find_Next_clicked();

    void on_btn_find_Previous_clicked();

    void on_btn_replace_clicked();

    void on_btn_replace_all_clicked();

signals:
    void sendString(QString,bool);
    void sendString_For_FindAll(QString);
    void replaceString(QString,QString,int);
    void closeFindWindow();
};

#endif // FINDWINDOW_H
