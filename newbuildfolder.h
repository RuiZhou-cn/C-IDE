#ifndef NEWBUILDFOLDER_H
#define NEWBUILDFOLDER_H
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>

// 创建文件夹时弹出的窗体
class NewBuildfolder : public QDialog
{
    Q_OBJECT
public:
    NewBuildfolder(QWidget *parent=0);
    QLineEdit *fileNameEdit;
    QPushButton *okButton;
    QPushButton *cancalButton;
};

#endif // NEWBUILDFOLDER_H
