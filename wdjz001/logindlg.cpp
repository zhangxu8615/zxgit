#include "logindlg.h"
#include "ui_logindlg.h"

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登录界面"));
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);

    //读取所有的名字并显示
    QString path="c://test.xml";
    QString keynode="doctor";
    QString key="姓名";
    QString readText;

    //打开文件
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
        QMessageBox::about(this, "About", " <font color='blue'>    文件读取失败 !    </font>");

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
    }
    file.close();

    QDomElement root = doc.documentElement(); //返回根节点
    qDebug() << root.nodeName();

    QDomNode node = root.firstChild(); //获得第一个子节点
    qDebug() << node.nodeName();

    while (!node.isNull())
    {
        if (node.isElement() && node.nodeName() == keynode) //如果节点是DOM元素
        {

            QDomElement e = node.toElement(); //转换为元素,注意元素和节点是两个数据结构,其实差不多
            QDomNodeList list = e.childNodes();

            for (int i = 0; i<list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n = list.at(i);
                if (node.isElement())
                {
                    if (n.nodeName() == key)
                    {
                        readText = n.toElement().text();
                        ui->loginUserBox->addItem(readText) ;
                    }
                }
            }
        }

        node = node.nextSibling();

    }
}

loginDlg::~loginDlg()
{
    delete ui;
}

void loginDlg::on_loginBtn_clicked()
{

    //根据姓名读出密码并进行比较
    doctor doc001;
    QString path="c://test.xml";
    QString keynode="doctor";
    QString key="姓名";
    QString readText;
    QString password;


    QFile file(path);
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::about(this, "About", " <font color='blue'>    读取文件失败 !    </font>");
    }
    file.close();

    QDomElement root = doc.documentElement();

    QDomNode node = root.firstChild();

    while (!node.isNull())
    {
        if (node.isElement() && node.nodeName() == keynode)
        {

            QDomElement e = node.toElement();
            QDomNodeList list = e.childNodes();

            for (int i = 0; i<list.count(); i++)
            {
                QDomNode n = list.at(i);
                if (node.isElement())
                {
                    if (n.nodeName() == "ID")
                    {
                        doc001.id = n.toElement().text();
                    }
                    if (n.nodeName() == "姓名")
                    {
                        doc001.Name = n.toElement().text();
                    }
                    if (n.nodeName() == "密码")
                    {
                        doc001.Password = n.toElement().text();
                    }
                    if (n.nodeName() == "科室")
                    {
                        doc001.Unit = n.toElement().text();
                    }
                    if (n.nodeName() == "类别")
                    {
                        doc001.Class = n.toElement().text();
                    }
                }
            }

            if(doc001.Name==ui->loginUserBox->currentText())
                password=doc001.Password;

        }
        node = node.nextSibling();
    }

    if(password==ui->loginPasswordEdit->text())
        accept();
    else {        
        QMessageBox::about(this, " ", " <font size='5' color='blue'>    密码错误 !    </font>");
    }

}
