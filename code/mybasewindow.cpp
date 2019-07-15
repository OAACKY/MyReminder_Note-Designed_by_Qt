#include "mybasewindow.h"
#include "ui_mybasewindow.h"
#include "setpasdialog.h"
#include "remind.h"
#include "remindbox.h"
#include<about.h>
#include<QDebug>
#include<QString>
#include<QSignalMapper>
#include<QColorDialog>

Mybasewindow::Mybasewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mybasewindow)
{
    ui->setupUi(this);
   ui->statusBar->hide();
   tabnum=2;
   curtab=0;

   mytextt[2]=ui->textEdit;
   mytextt[1]=ui->textEdit_2;
   QMenu *colorMenu = new QMenu(this);
   QAction *pencolor[4];
   QSignalMapper* signalMapper = new QSignalMapper;
   for(int i=0;i<4;i++)
   {
    pencolor[i]=new QAction;
    connect(pencolor[i],SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(pencolor[i],i);
   }
   connect(signalMapper, SIGNAL(mapped( int )),this, SLOT(clickcolor(int)));
   pencolor[0]->setText(QStringLiteral("黑色"));
   pencolor[0]->setIcon(QIcon(":/images/black"));
   pencolor[1]->setText(QStringLiteral("红色"));
   pencolor[1]->setIcon(QIcon(":/images/red"));
   pencolor[2]->setText(QStringLiteral("绿色"));
   pencolor[2]->setIcon(QIcon(":/images/green"));
   pencolor[3]->setText(QStringLiteral("蓝色"));
   pencolor[3]->setIcon(QIcon(":/images/blue"));
   for(int i=0;i<4;i++)
   {
   colorMenu->addAction(pencolor[i]);
   }
  ui->toolButton->setMenu(colorMenu);                         // 添加菜单
  ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup); // 设置弹出模式




  QSqlQuery sql_query;
  QSqlQuery sql_query2;
  QString select_sql = "select id,passport from user";
  QString mytemnum;
  int tt;
  sql_query.exec(select_sql);
  sql_query.first();
  sql_query.next();
  mytemnum=sql_query.value(1).toString();
  tt=mytemnum.toInt();                              //先从数据库user获得当前便签个数(默认为2个)
  tabnum=tt;

  QString select_sql2 = "select id,tab,content from note";
  sql_query2.exec(select_sql2);
  sql_query2.first();
  for(int i=1;i<=tt;i++)
  {
      if(i<3)
      { QString tempcont;
        QString temptab;
        temptab=sql_query2.value(1).toString();
        tempcont=sql_query2.value(2).toString();
        ui->tabWidget->setTabText(i-1,temptab);
        mytextt[i]->setHtml(tempcont);
        sql_query2.next();
      }
      else {
          QString tempcont;
          QString temptab;
          temptab=sql_query2.value(1).toString();
          tempcont=sql_query2.value(2).toString();
           mywidget[i]=new QWidget;
           mytextt[i]=new QTextEdit(mywidget[i]);
           mytextt[i]->setGeometry(0,0,247,431);
            QString mystring;
           ui->tabWidget->addTab(mytextt[i],temptab);
          mytextt[i]->setHtml(tempcont);

         sql_query2.next();//可能会崩溃。。
      }
  }
}


Mybasewindow::~Mybasewindow()
{
    delete ui;
}

void Mybasewindow::time_update()
{
    Remindbox *myremindbox=new Remindbox;
     myremindbox->show();
     remindti->stop();     //设置关闭
}


void Mybasewindow::clickcolor(int t)
{   QColor Color;
    if(t==0)
    Color= QColorDialog::getColor(Qt::black, this);
    else if (t==1) {
         Color = QColorDialog::getColor(Qt::red, this);
    }
    else if (t==2) {
        Color = QColorDialog::getColor(Qt::green, this);
    }
    else if (t==3) {
          Color = QColorDialog::getColor(Qt::blue, this);
    }

        if(Color.isValid())
        {

            QTextCharFormat tcf;
            tcf.setForeground(Color);
              mytextt[curtab+1]->mergeCurrentCharFormat(tcf);
        }

}

void Mybasewindow::on_action12_2_triggered()
{
    About *myabout=new About;
    myabout->show();

}

void Mybasewindow::on_actiont_triggered()
{
    tabnum++;
     mywidget[tabnum]=new QWidget;
   mytextt[tabnum]=new QTextEdit(mywidget[tabnum]);

   mytextt[tabnum]->setGeometry(0,0,247,431);
    QString mystring;
   ui->tabWidget->addTab(mytextt[tabnum],QStringLiteral("新建便签"));

}

void Mybasewindow::on_actionsh_triggered()
{
    ui->tabWidget->removeTab(curtab);
    tabnum--;
}

void Mybasewindow::on_toolButton_4_clicked()
{
   QTextCharFormat fmt;
   fmt.setFontWeight(QFont::Bold);
   mytextt[curtab+1]->mergeCurrentCharFormat(fmt);

}

void Mybasewindow::on_toolButton_3_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(true);
    mytextt[curtab+1]->mergeCurrentCharFormat(fmt);
}

void Mybasewindow::on_toolButton_2_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(true);
    mytextt[curtab+1]->mergeCurrentCharFormat(fmt);
}

void Mybasewindow::on_tabWidget_tabBarClicked(int index)
{
   curtab=index;
}

void Mybasewindow::on_tabWidget_tabBarDoubleClicked(int index)
{
}

void Mybasewindow::on_actiont_2_triggered()
{
      mytextt[curtab+1]->clear();
}

void Mybasewindow::on_actionb_triggered()
{
    QString tempstr;
    tempstr=mytextt[curtab+1]->toPlainText();
    QString tempstr2=tempstr.left(6);
  ui->tabWidget->setTabText(curtab,tempstr2);  //更新tab栏名称

  QString tempnum=QString::number(tabnum);    //转换到QString型

  QSqlQuery sql_query;
  QString update_sql ="update user set passport=:passport where id=:id";
  sql_query.prepare(update_sql);
  sql_query.bindValue(":passport",tempnum);
  sql_query.bindValue(":id",1);                //更新user表单的1号数据(便签个数)

  QSqlQuery sql_query2;
  QString insert_sql = "insert into note values(?,?,?)";
  QString update_sql2 ="update note set tab=:tab,content=:content where id=:id";
//  for(int i=0;i<tabnum;i++)
//  {
//      sql_query2.prepare(insert_sql);
//      sql_query2.addBindValue(i);
//      sql_query2.addBindValue(ui->tabWidget->tabText(i));
//      sql_query2.addBindValue(mytextt[i+1]->toHtml());
//      if(!sql_query2.exec())
//      {
//          qDebug() << sql_query.lastError();
//      }
//      else
//      {
//          qDebug() << "inserted success!";
//      }
//  }



  for(int i=0;i<tabnum;i++)
  {
      sql_query2.prepare(update_sql2);
      sql_query2.bindValue(":tab",ui->tabWidget->tabText(i));
      sql_query2.bindValue(":content",mytextt[i+1]->toHtml());
      sql_query2.bindValue(":id",i);
      if(!sql_query2.exec())
      {
          qDebug() << sql_query.lastError();
      }
      else
      {
          qDebug() << "update success!";
      }
  }
}

void Mybasewindow::on_action12_triggered()
{
    QString newpass;
    Setpasdialog *mypass=new Setpasdialog(this);
    mypass->exec();
    newpass=mypass->temp1;    //获取设置密码对话框的密码文本

    QSqlQuery sql_query;
    QString update_sql ="update user set passport=:passport where id=:id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":passport",newpass);
    sql_query.bindValue(":id",0);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "updated!";     //判断是否更新成果，给提示信息
    }
}

void Mybasewindow::on_actiont_3_triggered()      //设置提醒功能的槽函数
{
     Remind* myremind=new Remind();

     myremind->exec();

     QString myhou1=myremind->myhour;
     QString mymin1=myremind->myminu;

     remindti=new QTimer;
      connect(remindti,SIGNAL(timeout()),this,SLOT(time_update())); //设置槽函数
     int myhou2=myhou1.toInt();
     int mymin2=mymin1.toInt();

     myhou2=myhou2*3600000;
     mymin2=mymin2*6000;
     myhou2+=mymin2;

     remindti->start(myhou2);

}
