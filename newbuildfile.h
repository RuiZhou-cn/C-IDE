#ifndef NEWBUILDFILE_H
#define NEWBUILDFILE_H
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
// 创建文件时 弹出的窗体
class NewBulidFile : public QDialog{
    Q_OBJECT
public:
    NewBulidFile(QWidget *parent=0);
    QLineEdit *fileNameEdit;
    QComboBox *fileNameTypeBox;
    QPushButton *okButton;
    QPushButton *cancalButton;
};

#endif // NEWBUILDFILE_H
