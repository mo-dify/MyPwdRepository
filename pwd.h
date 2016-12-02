#ifndef PWD_H
#define PWD_H
#include <QWidget>
#include<QMessageBox>
#include<QDebug>
#include<QDialog>
#include<QFileDialog>//文件路径对话框
#include <QFile>
extern "C"
{
    #include"sqlite3/sqlite3.h"
    #include"sqlite3/sqlite_fun.h"
    #include"stdlib.h"
    #include"string.h"
    #include"unistd.h"
}
namespace Ui {
    class Pwd;
}

class Pwd : public QWidget
{
    Q_OBJECT
private slots:
     //   void logout();
        void on_pushButton_clicked();

        void on_pushButton_typein_clicked();

        void on_pushButton_Search_clicked();

        void on_pushButton_SureDel_clicked();

        void on_pushButton_modify_clicked();

        void on_pushButton_FuzzySearch_clicked();

        void on_pushButton_ShowAll_clicked();

        void on_pushButton_Import_clicked();

        void on_pushButton_Export_clicked();

public:
    explicit Pwd(QWidget *parent = 0);
    ~Pwd();
        sqlite3 *db;
        char *sql;
        char *errmsg;
        int result;
private:
    Ui::Pwd *ui;
signals:
    void sendmsg();
};

#endif // PWD_H
