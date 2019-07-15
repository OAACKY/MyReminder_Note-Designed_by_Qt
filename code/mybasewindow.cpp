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
   pencolor[0]->setText(QStringLiteral("��ɫ"));
   pencolor[0]->setIcon(QIcon(":/images/black"));
   pencolor[1]->setText(QStringLiteral("��ɫ"));
   pencolor[1]->setIcon(QIcon(":/images/red"));
   pencolor[2]->setText(QStringLiteral("��ɫ"));
   pencolor[2]->setIcon(QIcon(":/images/green"));
   pencolor[3]->setText(QStringLiteral("��ɫ"));
   pencolor[3]->setIcon(QIcon(":/images/blue"));
   for(int i=0;i<4;i++)
   {
   colorMenu->addAction(pencolor[i]);
   }
  ui->toolButton->setMenu(colorMenu);                         // ��Ӳ˵�
  ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup); // ���õ���ģʽ




  QSqlQuery sql_query;
  QSqlQuery sql_query2;
  QString select_sql = "select id,passport from user";
  QString mytemnum;
  int tt;
  sql_query.exec(select_sql);
  sql_query.first();
  sql_query.next();
  mytemnum=sql_query.value(1).toString();
  tt=mytemnum.toInt();                              //�ȴ����ݿ�user��õ�ǰ��ǩ����(Ĭ��Ϊ2��)
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

         sql_query2.next();//���ܻ��������
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
     remindti->stop();     //���ùر�
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
   ui->tabWidget->addTab(mytextt[tabnum],QStringLiteral("�½���ǩ"));

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
  ui->tabWidget->setTabText(curtab,tempstr2);  //����tab������

  QString tempnum=QString::number(tabnum);    //ת����QString��

  QSqlQuery sql_query;
  QString update_sql ="update user set passport=:passport where id=:id";
  sql_query.prepare(update_sql);
  sql_query.bindValue(":passport",tempnum);
  sql_query.bindValue(":id",1);                //����user����1������(��ǩ����)

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
    newpass=mypass->temp1;    //��ȡ��������Ի���������ı�

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
        qDebug() << "updated!";     //�ж��Ƿ���³ɹ�������ʾ��Ϣ
    }
}

void Mybasewindow::on_actiont_3_triggered()      //�������ѹ��ܵĲۺ���
{
     Remind* myremind=new Remind();

     myremind->exec();

     QString myhou1=myremind->myhour;
     QString mymin1=myremind->myminu;

     remindti=new QTimer;
      connect(remindti,SIGNAL(timeout()),this,SLOT(time_update())); //���òۺ���
     int myhou2=myhou1.toInt();
     int mymin2=mymin1.toInt();

     myhou2=myhou2*3600000;
     mymin2=mymin2*6000;
     myhou2+=mymin2;

     remindti->start(myhou2);

}
