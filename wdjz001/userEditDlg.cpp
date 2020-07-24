#include "userEditDlg.h"
#include "ui_userEditDlg.h"

userEditDlg::userEditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userEditDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("新增用户"));
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
}

userEditDlg::~userEditDlg()
{
    delete ui;
}

void userEditDlg::on_addUserBtn_clicked()
{

    QString path="c://test.xml";
    QString verEnc="1.0";
    QString rootname="user";
    bool Information=false;
    //创建xml文件
    //Information=MainWindow::creatXml(path,verEnc,rootname);

    //增加用户信息
    QString nodeName="doctor";
    QString name[5];
    QString val[5];
    int num=5;

    name[0]=ui->label_ID->text();
    name[1]=ui->label_Name->text();
    name[2]=ui->label_Password->text();
    name[3]=ui->label_Unit->text();
    name[4]=ui->label_Class->text();
    val[0]=ui->userID->text();
    val[1]=ui->userName->text();
    val[2]=ui->userPassword->text();
    val[3]=ui->userUnit->text();
    val[4]=ui->userClass->text();

    Information=MainWindow:: addXml(path, nodeName, name,  val,  num);

    if(Information==true)
        qDebug("1");
    else
        qDebug("0");


}

void userEditDlg::on_userClass_selectionChanged()
{
    QMessageBox::about(this, " ", " <font size='5' color='blue'> 选择改变 !    </font>");
}
