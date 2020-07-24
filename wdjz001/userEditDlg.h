#ifndef USEREDITDLG_H
#define USEREDITDLG_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class userEditDlg;
}

class userEditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit userEditDlg(QWidget *parent = nullptr);
    ~userEditDlg();

private slots:
    void on_addUserBtn_clicked();

    void on_userClass_selectionChanged();

private:
    Ui::userEditDlg *ui;
};

#endif // USEREDITDLG_H
