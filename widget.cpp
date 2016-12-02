#include "widget.h"
#include "ui_widget.h"
#include<QDesktopWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->mypwd=new Pwd();
    result=sqlite3_open("MyPwd.db",&this->db);

    if(result!=SQLITE_OK)
        qDebug()<<errmsg;
    result=sqlite3_exec(this->db,"CREATE TABLE MyPwd (Utype text,Uname text check(Uname>0),\
                        Upwd text check(length(Upwd)>=6));" ,NULL,NULL,&errmsg );
    if(result!=SQLITE_OK)
        qDebug()<<errmsg;
    mypwd->db=this->db;
      connect(mypwd,SIGNAL(sendmsg()),this,SLOT(show_login()));
      //获取屏幕分辨率
      QDesktopWidget *dsk = QApplication::desktop();
      qDebug()<<dsk->height()<<dsk->width();
      //调整屏幕分辨率
      this->resize(dsk->width(),dsk->height());
      this->mypwd->resize(dsk->width(),dsk->height());

}

Widget::~Widget()
{
    delete ui;
}
void Widget::show_login()
{
    this->show();
}

void Widget::on_pushButton_login_clicked()
{
    QString check_pwd=ui->lineEdit_pwd->text();
    if(ui->lineEdit_pwd->text()=="1008611")
    {
        QMessageBox::information(this,"消息","登陆成功！");
        this->hide();
        mypwd->show();
    }
    else
        QMessageBox::information(this,"消息","密码错误！！！！");
    ui->lineEdit_pwd->setText("");
}

void Widget::on_pushButton_clicked()
{
    this->close();
}
