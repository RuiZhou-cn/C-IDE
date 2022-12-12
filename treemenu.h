#ifndef TREEMENU_H
#define TREEMENU_H
#include <QMenu>
#include <QTreeWidget>
#include <newbuildfile.h>
#include <newbuildfolder.h>
#include <QDir>
#include <QScrollBar>
#include <QHeaderView>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
// 显示文件树的窗体
extern QString fatherpath;

class TreeMenu : public QTreeWidget{
    Q_OBJECT
public:
    TreeMenu(QWidget *parent = 0);
    void CreateTopItem(QString path);
    void FindFile(QDir *path,QTreeWidgetItem *parent);
    void buttonCollapseItem();
private:
    QTreeWidgetItem *root; //树的根
    QMenu *dirMenu;  //文件夹菜单栏
    QMenu *fileMenu;  //文件菜单栏
    QTreeWidgetItem *nowItem; //当前光标所在Item
    int nowCol; //当前所在列
    NewBulidFile *newFileWidget;
    NewBuildfolder *newDirWidget;
signals:
    void showTextSignal(QString path,QString name);
    void collapseItemSignal(const QTreeWidgetItem *item);
private slots:
    void DoubleClickpath(QTreeWidgetItem *item, int column);
    void itemPressedSlot(QTreeWidgetItem * pressedItem, int column);
    void tempActionInformation(QAction *act);
    void bulidNewFileSlot(bool flag);
    void closeBuildFileSlot(bool flag);
    void buildNewDirSlot(bool flag);
    void cancelDirSlot(bool flag);
    bool deleteFileOrFolder(const QString &strPath);  //删除文件或文件夹
};
#endif // TREEMENU_H
