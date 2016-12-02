#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"pwd.h"
extern "C"
{
    #include"sqlite3/sqlite3.h"
    #include"sqlite3/sqlite_fun.h"
    #include"stdlib.h"
    #include"string.h"
    #include"unistd.h"
}


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private slots:
    void show_login();
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    sqlite3 *db;
    char *sql;
    char *errmsg;
    int result;
private:
    Ui::Widget *ui;
    Pwd *mypwd;
};

#endif // WIDGET_H
