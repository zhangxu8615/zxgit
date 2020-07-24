#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGroupBox>
#include <QTableView>
#include <QLabel>
#include <QFile>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <logindlg.h>
#include <userEditDlg.h>
#include <userEditDialog.h>

#include <QtNumeric>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addUserBtn_triggered();
    void on_editUserBtn_triggered();
    void on_action_Q_triggered();
    void on_action_X_triggered();

private:
    Ui::MainWindow *ui;
    QDialog *dialogAddUser;
    QDialog *dialogEditUser;
    QDialog *logindlg;


public:
    static bool creatXml(const QString& path, const QString& verEnc, const QString& rootname);

    static bool addXml(const QString& path, const QString& nodeName,
                const QString name[], const QString val[], const int num);
    static QString readXml(const QString& path, const QString& keynode, const QString& key);

    static bool removeXmlNode(const QString& path, const QString& key, const QString& val);

    static bool removeXmlNameNode(const QString& path, const QString& name);


};
#endif // MAINWINDOW_H
