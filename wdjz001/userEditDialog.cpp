#include "userEditDialog.h"
#include "ui_userEditDialog.h"

#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

userEditDialog::userEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userEditDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("编辑用户"));
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);

    //读取所有的名字并显示
    QString path="c://test.xml";
    QString keynode="doctor";
    QString key="姓名";
    QString readText;

    //建立QTableView的mode
    QStandardItemModel* model = new QStandardItemModel();
    QStringList labels = QObject::trUtf8(" ID, 姓名, 密码, 科室, 类别").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);

    //产生显示
    ui->userTableView->setShowGrid(true);
    ui->userTableView->setGridStyle(Qt::DotLine);
    ui->userTableView->setColumnWidth(1,200);//没用
    ui->userTableView->verticalHeader()->setVisible(false); //隐藏列表头
    ui->userTableView->setModel(model);
    ui->userTableView->show();

    //定义item
    QStandardItem* item = 0;

    //打开文件
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
        QMessageBox::about(this, "About", " <font color='blue'>    文件读取失败 !    </font>");

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::about(this, "About", " <font color='blue'>    文件数据错 !    </font>");
    }
    file.close();

    QDomElement root = doc.documentElement(); //返回根节点    

    QDomNode node = root.firstChild(); //获得第一个子节点    

    row=0;
    while (!node.isNull())
    {

        if (node.isElement() && node.nodeName() == keynode) //如果节点是DOM元素
        {
            QDomElement e = node.toElement(); //转换为元素,注意元素和节点是两个数据结构,其实差不多
            QDomNodeList list = e.childNodes();

            for (int i = 0; i<list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                //需要把list装进 QTableView *userView
                QDomNode n = list.at(i);
                readText = n.toElement().text();
                item = new QStandardItem(QString("%1").arg(readText));
                model->setItem(row,i,item);
            }
        }
        row++;
        node = node.nextSibling();
    }

    rowMax=model->rowCount();//第一次读进时候 QTableView的最大行数

}

userEditDialog::~userEditDialog()
{
    delete ui;
}

void userEditDialog::on_addUserBtn_clicked()
{
    QAbstractItemModel *model=ui->userTableView->model();
    ui->userTableView->setModel(model);
    ui->userTableView->show();
    //在所选行后新增一空白行
    int row=ui->userTableView->currentIndex().row();
    model->insertRow(row+1);
    rowMax++;

}


void userEditDialog::on_delUserBtn_clicked()
{

    QAbstractItemModel *model=ui->userTableView->model();
    ui->userTableView->setModel(model);
    ui->userTableView->show();
    //在所选行后新增一空白行
    int row=ui->userTableView->currentIndex().row();
    model->removeRow(row);
    rowMax--;

}



void userEditDialog::on_saveUserBtn_clicked()
{

    QString path="c://test.xml";
    QString verEnc="1.0";
    QString rootname="user";
    bool Information=false;
    //创建xml文件
    Information=MainWindow::creatXml(path,verEnc,rootname);
    if(Information==1)
        qDebug()<<"新建文件OK";
    //增加用户信息
    QString nodeName="doctor";
    QString name[5];
    QString val[5];
    int num=5;

    name[0]="ID";
    name[1]="姓名";
    name[2]="密码";
    name[3]="科室";
    name[4]="类别";

    val[0]="";
    val[1]="";
    val[2]="";
    val[3]="";
    val[4]="";

    //删除所有名称为nodeName的节点
    //MainWindow::removeXmlNameNode(path,nodeName);

    QAbstractItemModel *model=ui->userTableView->model();

    qDebug()<<rowMax;

    for (int row=0;row<rowMax;row++)
    {
        //获取当前行的所有信息
        for(int i = 0; i < 5; i++)
        {
            //遍历第row行的所有信息
            QModelIndex index = model->index(row,i);
            val[i] = model->data(index).toString();
            //qDebug()<<val[i];
        }

        //追加存储一个个节点
        Information=MainWindow:: addXml(path, nodeName, name,  val,  num);

    }

}

