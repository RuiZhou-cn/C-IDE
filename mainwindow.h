#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "findwindow.h"
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
#include <QKeySequence>
#include <QTextDocument>
#include "dialog_new.h"
#include <treemenu.h>
#include <file_textedit.h>
#include <QProcess>


extern QString k1;
extern int temp;

class Dialog_new;
class File_textedit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int flag1 = 0;
    int flag2 = 0;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void EditOutput();
    void FileView();


    FindWindow * findWindow = NULL;
    void closeFun();

    void setupEditor();
    QTextEdit *editor;
    Highlighter *highlighter;

private:
    QProcess m_process;
    QProcess m_process2;


signals:
    //void add();//检测到加入括号，发出添加括号信号
    void newfile();//添加了新文件，需要显示在目录里
    void close(int index);
public slots:
    void findText(QString str,bool next);//next=true代表查找后一个
    void findAllText(QString str);//执行全部查找
    void replaceText(QString originalString , QString updateString , int mode);//执行替换操作
    void addfiletotree();    //添加新文件到目录中

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void showTextOnTab(QString path,QString name);
    void on_action_tool_new_triggered();
    void on_actionNewFile_triggered();
    void on_actionOpenFile_triggered();
    void on_actionSaveFileAs_triggered();
    void on_actionSaveFile_triggered();
    void on_actionQuit_triggered();
    void on_action_tool_open_triggered();
    void on_action_tool_close_triggered();
    void on_action_tool_copy_triggered();
    void on_action_tool_cut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionReverse_triggered();
    void removeSubTab(int index);
    void on_actiontext_view_triggered();
    void on_actionedit_view_triggered();
    void on_actionsearch_triggered();
    void on_action_tool_save_triggered();

//    void change();//文本内容改变了
//    void addBracket();//加括号
 //   void Color();//给括号加颜色

    void on_actionChangeWhite_triggered();

    void on_actionChangePink_triggered();

    void on_actionChangeOrange_triggered();

    void on_actionChangeColorful_triggered();

    void on_actionChangeDarkBlue_triggered();

    //void on_action_tool_run_triggered();

    void on_action_edit_triggered();

    void on_action_run_triggered();

    void on_action_edit_run_triggered();

    void onReadData();

    void onReadData2();

    void onreaderror();

    void onreaderror2();

    void on_action_debug_triggered();

    void on_action_addbreakpoint_triggered();

    void on_action_delete_triggered();

    void on_action_check_triggered();

    void on_action_tool_singleRun_triggered();

    void on_action_tool_processRun_triggered();

    void on_action_tool_RunWhileDebug_triggered();

    void on_action_tool_search_triggered();

    void on_action_tool_Exit_triggered();

    void on_action_tool_run_triggered();

public:
    Ui::MainWindow *ui;
    Dialog_new *dlg_dialog;

};

#endif // MAINWINDOW_H
