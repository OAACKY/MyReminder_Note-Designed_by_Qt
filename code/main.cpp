#include "mybasewindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if (!db.open())
     {
         qDebug() << "Error: Failed to connect database." << db.lastError();
     }
     else
     {
         qDebug() << "Succeed to connect database." ;
     }

//        QSqlQuery sql_query;
//        QString create_sql = "create table note(id int primary key,tab varchar(20),content varchar(200))";
//        if(!sql_query.exec(create_sql))
//        {
//            qDebug() << "Error: Fail to create table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table created!";
//        }
//            QString insert_sql = "insert into user values(?,?)";
//            sql_query.prepare(insert_sql);
//            sql_query.addBindValue(1);
//            sql_query.addBindValue("2");
//            if(!sql_query.exec())
//            {
//                qDebug() << sql_query.lastError();
//            }
//            else
//            {
//                qDebug() << "inserted number";
//            }

    login w;
    w.show();

    return a.exec();
}
