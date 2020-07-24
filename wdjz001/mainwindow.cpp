#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //状态栏设置
    QLabel *locationLabel;
    locationLabel=new QLabel(" ");
    locationLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    QLabel *aixLabel;
    aixLabel=new QLabel("F1 for help");

    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
    statusBar()->setSizeGripEnabled(true); //设置是否显示右边的大小控制点
    statusBar()->addWidget(locationLabel,40);
    statusBar()->addWidget(aixLabel, 60);

    QLabel *per1 = new QLabel("Ready1", this);
    statusBar()->addPermanentWidget(per1); //现实永久信息

    statusBar()->showMessage("Status is here...", 10000); // 显示临时信息，时间10秒钟

}

MainWindow::~MainWindow()
{
    delete ui;
}

//弹出用户新建窗口
void MainWindow::on_addUserBtn_triggered()
{
    dialogAddUser =new userEditDlg(this);
    dialogAddUser->show();
    dialogAddUser->setModal(false);
}
//弹出用户编辑窗口
void MainWindow::on_editUserBtn_triggered()
{
    dialogEditUser =new userEditDialog(this);
    dialogEditUser->setModal(false);
    dialogEditUser->show();
}
//弹出登录界面
void MainWindow::on_action_Q_triggered()
{
    logindlg=new loginDlg(this);
    logindlg->setModal(false);
    logindlg->show();
}
//退出
void MainWindow::on_action_X_triggered()
{
    close();
}




//创建一个只有根节点的xml文件
/*
参数说明：
const QString& path 【xml路径】
const QString& verEnc【版本和编码格式】
const QString& rootname【根节点名字】
*/
bool MainWindow::creatXml(const QString& path, const QString& verEnc, const QString& rootname)
{
   //打开xml文件
   QFile file(path);
   if (!file.open(QFile::WriteOnly | QFile::Truncate))
       return false;

   QDomDocument doc;

   //写入xml头部
   QDomProcessingInstruction instruction;
   instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
   doc.appendChild(instruction);

   //设置括号标签中间的值
   QDomText text;

   //添加根节点
   QDomElement root = doc.createElement(rootname);
   doc.appendChild(root);

   //输出到文件
   QTextStream out_stream(&file);
   doc.save(out_stream, 4); //缩进4格
   file.close();

   return true;
}

//Xml文件节点的添加
/*
参数说明：
const QString& path 【xml路径】,
const QString&  nodeNmae【创建节点名字】,
const QString name[]【节点元素名字集合】,
const QString val[]【节点元素值集合】,
const int num【节点元素个数】
*/
bool MainWindow::addXml(const QString& path, const QString& nodeName,
                                 const QString name[], const QString val[], const int num)
{
   //打开文件
   QFile file(path); //相对路径、绝对路径、资源路径都可以
   if (!file.open(QFile::ReadOnly))
   {
       return false;
   }


   //读入xml
   QDomDocument doc;
   if (!doc.setContent(&file))
   {
    file.close();
    qDebug("0");
    return false;
   }
   file.close();

   QDomText text; //设置括号标签中间的值

   QDomElement root = doc.documentElement();

   QDomElement node = doc.createElement(nodeName);

   for (int i = 0; i < num; i++)
   {
    QDomElement xml_id = doc.createElement(name[i]);		//创建子元素1
    text = doc.createTextNode(val[i]);
    xml_id.appendChild(text);
    node.appendChild(xml_id);
   }

   root.appendChild(node);

   if (!file.open(QFile::WriteOnly | QFile::Truncate)) //如果不用truncate就是在后面追加
    return false;

   //输出到文件
   QTextStream out_stream(&file);
   doc.save(out_stream, 4); //缩进4格
   file.close();

   return true;
}

//Xml文件节点元素值的输出
/*
参数说明：
const QString& path【路径】,
const QString& keynode【寻找节点名称】,
const QString& key【元素的名称】
*/
QString MainWindow::readXml(const QString& path, const QString& keynode, const QString& key)
{
   QString readText;
   //打开或创建文件
   QFile file(path);
   if (!file.open(QFile::ReadOnly))
    return NULL;

   QDomDocument doc;
   if (!doc.setContent(&file))
   {
    file.close();
    return NULL;
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
                    node = node.nextSibling();
                    if(node.nodeName() == keynode)
                        return	readText + " (+1)";
                    return	readText;
                }
            }
        }

    }
    node = node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
   }

   return NULL;
}

//Xml文件删除特定内容的节点
/*
参数说明：
const QString& path【路径】,
const QString& key【元素的名称】，
const QString& val【元素值】
*/
bool MainWindow::removeXmlNode(const QString& path, const QString& key, const QString& val)
{
   //打开或创建文件
   QFile file(path);
   if (!file.open(QFile::ReadOnly))
    return false;

   QDomDocument doc;
   if (!doc.setContent(&file))
   {
    file.close();
    return false;
   }
   file.close();

   QDomElement root = doc.documentElement(); //返回根节点

   QDomNode node = root.firstChild(); //获得第一个子节点

   while (!node.isNull())
   {
    if (node.isElement()) //如果节点是元素
    {

        QDomNodeList list = node.childNodes();

        for (int i = 0; i<list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
        {
            QDomNode n = list.at(i);
            if (node.isElement())
            {
                if (n.nodeName() == key && n.toElement().text() == val)
                {
                    qDebug() << n.nodeName() << ":" << n.toElement().text();
                    //node.removeChild(list.at(i)); //删除属性
                    root.removeChild(node);
                }
            }
        }

    }
    node = node.nextSibling();

   }
   if (!file.open(QFile::WriteOnly | QFile::Truncate))
    return false;
   //输出到文件
   QTextStream out_stream(&file);
   doc.save(out_stream, 4); //缩进4格
   file.close();

   return true;
}

//Xml文件按名称删除节点
/*
参数说明：
const QString& path【路径】,
const QString& key【元素的名称】，
const QString& val【元素值】
*/
bool MainWindow::removeXmlNameNode(const QString& path, const QString& name)
{
   //打开或创建文件
   QFile file(path);
   if (!file.open(QFile::ReadOnly))
    return false;

   QDomDocument doc;
   if (!doc.setContent(&file))
   {
    file.close();
    return false;
   }
   file.close();

   QDomElement root = doc.documentElement(); //返回根节点
   QDomNode node = root.firstChild(); //获得第一个子节点
   qDebug()<<node.toElement().text();

   while (!node.isNull())
   {
       if (node.isElement()) //如果节点是元素
       {

           QDomNodeList list = node.childNodes();

           for (int i = 0; i<list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
           {
               QDomNode n = list.at(i);
               if (node.isElement())
               {

                   {
                       qDebug() << n.nodeName() << ":" << n.toElement().text();
                       //node.removeChild(list.at(i)); //删除属性
                       root.removeChild(node);
                   }
               }
           }

       }
       node = node.nextSibling();

   }
   if (!file.open(QFile::WriteOnly | QFile::Truncate))
    return false;
   //输出到文件
   QTextStream out_stream(&file);
   doc.save(out_stream, 4); //缩进4格
   file.close();

   return true;
}

