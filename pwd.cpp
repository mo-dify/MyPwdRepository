#include "pwd.h"
#include "ui_pwd.h"
#include<QFile>
#include <qfile.h>
#include<QHeaderView>
#include<qheaderview.h>
Pwd::Pwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pwd)
{
    ui->setupUi(this);
  //  ui->tableWidget_Showall->verticalHeader()->(QHeaderView::Stretch);
//   QFileDialog::setStyleSheet("QTreeView::item{height: 1000px;}");
    ui->tableWidget_Showall->verticalHeader()->ResizeMode(QHeaderView::Stretch);
}

Pwd::~Pwd()
{
    delete ui;
}

void Pwd::on_pushButton_clicked()
{
    this->hide();
    emit sendmsg();
}

void Pwd::on_pushButton_typein_clicked()
{
    if(ui->lineEdit_NewPwd->text().compare(ui->lineEdit_SureNewPwd->text()))
    {
        QMessageBox::information(this,"消息","前后密码不一致！");
        return ;
    }
    QString tmp =QString("insert into MyPwd values('%1','%2','%3');").arg(ui->lineEdit_Type->text()).arg(ui->lineEdit_NewId->text()).arg(ui->lineEdit_NewPwd->text());
    qDebug()<<tmp;
    int result=sqlite3_exec(this->db,tmp.toLatin1().data(),NULL,NULL ,&errmsg );
    qDebug()<<result;
    if(result!=SQLITE_OK)
    {
       QMessageBox::information(this,"消息","信息有误，请重新输入！");
       qDebug()<<errmsg;
    }
    else
        QMessageBox::information(this,"消息","录入成功！");
}

void Pwd::on_pushButton_Search_clicked()
{
    if(ui->lineEdit_SearchType->text()=="")
    {
               QMessageBox::information(this,"消息","请输入查找信息!");
                return;
    }
    QString tmp=QString("select Uname,Upwd from MyPwd where Utype='%1';").arg(ui->lineEdit_SearchType->text());
     qDebug()<<tmp;
     qDebug()<<tmp;
     char detail[1024]="";
     //查看所有需要三个参数,db,sql语句,容器
     int result =sqlite3_exec(this->db,tmp.toLatin1().data(),search_detail,detail,&errmsg);
     if(result!=SQLITE_OK)
         qDebug()<<errmsg;
        tmp=detail;
        qDebug()<<tmp;
     //拆包
     ui->plainTextEdit_ShowType->setPlainText("");
     static int num;
     num=ui->spinBox_ShowNum->text().toInt();
     int i=0;
     ui->label_TIP->setText("账号/密码");
     QString de;
     //注意，这里的+=是用来标注每行拆几个元素,因为标志位“|”是加在
     for(i=0;i<(num*2);i+=2)
     {
         de =tmp.section('|',i,i).append("   |   ").append(tmp.section('|',i+1,i+1));
         ui->plainTextEdit_ShowType->appendPlainText(de);
     }
}

void Pwd::on_pushButton_SureDel_clicked()
{
    //判断确认删除的密码是否一致
    if(ui->lineEdit_DelPwd->text().compare(ui->lineEdit_SureDelPwd->text()))
    {
        QMessageBox::information(this,"消息","前后密码不一致！");
        return ;
    }
    //组件sql语句查找该账户
    QString tmp1 =QString("select Upwd from MyPwd where Uname='%1' and  Utype='%2';")\
            .arg(ui->lineEdit_DelId->text()).arg(ui->lineEdit_DelType->text());
    qDebug()<<tmp1;
    char pwd[100]="";
    sqlite3_exec(this->db,tmp1.toLatin1().data(),search,pwd,&errmsg );

    tmp1=pwd;
    qDebug()<<tmp1;
    if(tmp1=="")
    {
       QMessageBox::information(this,"消息","删除失败，请输入正确信息！");
       qDebug()<<errmsg;
       return;
    }
     qDebug()<<"在这里";
     QString tmp2=ui->lineEdit_DelPwd->text();
    qDebug()<<tmp1;
    qDebug()<<tmp2;
     //数据库密码与输入密码对比
    if(tmp1==tmp2)
    {
        //验证成功，删除账户
        tmp1 =QString("delete from MyPwd where Uname='%1' and  Utype='%2';")\
                .arg(ui->lineEdit_DelId->text()).arg(ui->lineEdit_DelType->text());
        qDebug()<<tmp1;
         result=sqlite3_exec(this->db,tmp1.toLatin1().data(),search,pwd,&errmsg );

        if(result==SQLITE_OK)
            QMessageBox::information(this,"消息","删除成功！");
    }
    else
    {
       QMessageBox::information(this,"消息","删除失败，请输入正确信息！");
       qDebug()<<errmsg;
    }
}
//修改密码
void Pwd::on_pushButton_modify_clicked()
{
    //判断确认删除的密码是否一致
    if(ui->lineEdit_ModifyPwd->text().compare(ui->lineEdit_SureModifyPwd->text()))
    {
        QMessageBox::information(this,"消息","前后密码不一致！");
        return ;
    }
    //组件sql语句查找该账户
    QString tmp1 =QString("select Upwd from MyPwd where Uname='%1' and  Utype='%2';")\
            .arg(ui->lineEdit_ModifyId->text()).arg(ui->lineEdit_ModifyType->text());
    qDebug()<<tmp1;
    char pwd[100]="";
    sqlite3_exec(this->db,tmp1.toLatin1().data(),search,pwd,&errmsg );

    tmp1=pwd;
    qDebug()<<tmp1;
    if(tmp1=="")
    {
       QMessageBox::information(this,"消息","删除失败，请输入正确信息！");
       qDebug()<<errmsg;
       return;
    }
     qDebug()<<"在这里";
     QString tmp2=ui->lineEdit_OldPwd->text();
    qDebug()<<tmp1;
    qDebug()<<tmp2;
     //数据库密码与输入密码对比
    if(tmp1==tmp2)
    {
        //验证成功，修改账户
        tmp1 =QString("update  MyPwd set Upwd='%1' where Uname='%2' and  Utype='%3';")\
                .arg(ui->lineEdit_ModifyPwd->text()).arg(ui->lineEdit_ModifyId->text())\
                .arg(ui->lineEdit_ModifyType->text());
        qDebug()<<tmp1;
         result=sqlite3_exec(this->db,tmp1.toLatin1().data(),NULL,NULL,&errmsg );

        if(result==SQLITE_OK)
            QMessageBox::information(this,"消息","修改成功！");
    }
    else
    {
       QMessageBox::information(this,"消息","修改失败，请输入正确信息！");
       qDebug()<<errmsg;
    }
}

void Pwd::on_pushButton_FuzzySearch_clicked()
{
    if(ui->lineEdit_SearchType->text()=="")
    {
               QMessageBox::information(this,"消息","请输入查找信息!");
                return;
    }
     QString tmp=QString("select * from MyPwd where Utype like '%%1%';").arg(ui->lineEdit_SearchType->text());
     qDebug()<<tmp;
     qDebug()<<tmp;
     char detail[1024]="";
     //查看所有需要三个参数,db,sql语句,容器
     int result =sqlite3_exec(this->db,tmp.toLatin1().data(),search_detail,detail,&errmsg);
     if(result!=SQLITE_OK)
         qDebug()<<errmsg;
        tmp=detail;
        qDebug()<<tmp;
     //拆包
     ui->plainTextEdit_ShowType->setPlainText("");
     static int num;
     num=ui->spinBox_ShowNum->text().toInt();
     int i=0;
     ui->label_TIP->setText("类型/账号/密码");
     QString de;
     //注意，这里的+=是用来标注每行拆几个元素,因为标志位“|”是加在
     for(i=0;i<(num*2);i+=3)
     {
         de =tmp.section('|',i,i).append("   |   ").append(tmp.section('|',i+1,i+1))\
                 .append("   |   ").append(tmp.section('|',i+2,i+2));
         ui->plainTextEdit_ShowType->appendPlainText(de);
     }
}

void Pwd::on_pushButton_ShowAll_clicked()
{
    if(ui->lineEdit_SuperPwd->text()!="166829")
     return;
    QString tmp="select * from MyPwd;";
    qDebug()<<tmp;
    char detail[1024]="";
    int result =sqlite3_exec(this->db,tmp.toLatin1().data(),search_detail,detail,&errmsg);
    if(result!=SQLITE_OK)
        qDebug()<<errmsg;
    tmp=detail;
    qDebug()<<tmp;
    int i=0,j=0;
    ui->label_TIP->setText("类型/账号/密码");
    //注意，这里的+=是用来标注每行拆几个元素,因为标志位“|”是加在
    for(i=0;;i++)
    {
        //追加行数
        ui->tableWidget_Showall->setRowCount(i+1);
        //在一行添加数据
        for(j=0;j<3;j++)
        ui->tableWidget_Showall->setItem(i,j,new QTableWidgetItem(tmp.section('|',(i*3)+j,(i*3)+j)));
        if(tmp.section('|',(i*3)+j,(i*3)+j)=="")
        return;
    }
}

void Pwd::on_pushButton_Import_clicked()
{
    //源路劲目标路径
    QString origin = "/data/data/org.qtproject.example.MyPwdRepository/files/MyPwd.db";
    QString target = "/sdcard/MyPwd.db";
    //  ui->lineEdit_Import->setText(str);
    //执行拷贝
    QFile::copy(origin, target);
    //判断拷贝是否成功
    QFile ori("/sdcard/MyPwd.db");
     if(ori.exists())
       QMessageBox::information(this,"消息","导出成功!");
       else
       QMessageBox::information(this,"消息","导出失败!");
}

void Pwd::on_pushButton_Export_clicked()
{
     QString origin = "/sdcard/MyPwd.db";
    QString target = "/data/data/org.qtproject.example.MyPwdRepository/files/MyPwd.db";
    QFile ori("/sdcard/MyPwd.db");
     //  ui->lineEdit_Import->setText(str);
     qDebug()<<"lalallallal";
     if(!ori.exists())
     {
         QMessageBox::information(this,"消息","文件不存在!");
         return;
     }
     QFile::copy(origin, target);
    QMessageBox::information(this,"消息","导入成功!");
}
