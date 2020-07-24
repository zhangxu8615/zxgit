#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include <QStandardItemModel>

namespace Ui {
class userEditDialog;
}

class userEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userEditDialog(QWidget *parent = nullptr);
    ~userEditDialog();



private slots:
    void on_addUserBtn_clicked();

    void on_saveUserBtn_clicked();

    void on_delUserBtn_clicked();

private:
    QStandardItemModel *model;
    int row;
    int rowMax;

private:
    Ui::userEditDialog *ui;

};

#endif // USEREDITDIALOG_H
