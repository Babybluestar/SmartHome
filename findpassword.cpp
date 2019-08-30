#include "findpassword.h"
#include "ui_findpassword.h"
#include <QMessageBox>
#include <QDebug>

#include <tcpsocket.h>
#include <loginwindow.h>


findPassword::findPassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::findPassword)
{
    ui->setupUi(this);
    tcpSocket = new TcpSocket;

    connect(tcpSocket,SIGNAL(findStatu(QString,QString,QString)),this,SLOT(showFindResult(QString,QString,QString)));
    connect(this,SIGNAL(findpassword(QString,QString,QString)),tcpSocket,SLOT(findUserByTcp(QString,QString,QString)));
}

findPassword::~findPassword()
{
    delete ui;
}

void findPassword::showFindResult(const QString &error, const QString &username, const QString &password)
{
    qDebug()<<"yyyyyyyyyy\n";
    qDebug()<< (!error.isEmpty());
     qDebug()<<"yyyyyyyyyy\n";
    if(!error.isEmpty())
    {
        QString str = QString("输入信息有误,请重新输入:\n%1").arg(error);
        QMessageBox::warning(NULL,"查找错误",str,QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    else
    {
        QString information = "";
        QString serverAdd = "smtp.qq.com";
        QString sen = "87831498@qq.com";
        QString serverPassword = "gvwmcietemyybhaa";
        QString rec = "344206489@qq.com";
        QString tip = QString("找回密码：%1").arg(error);
        QString mention = QString("您的密码是: %1").arg(error)+password;

        sendmail = new Smtp(serverAdd,sen,serverPassword);
        if(sendmail->Send(rec,tip,mention))
                           {
                               if(sendmail->PutSendLine())
                               {
                                   information += QString("已向您发送邮件，请注意查收!!!%1").arg(error);
                                   QMessageBox::information(NULL,"查找结果",information,QMessageBox::Yes,QMessageBox::Yes);

                                 //LoginWindow loginwindow = new LoginWindow;
                                   emit autoshow(username);
                                  //loginWindow->show();
                                  this->close();

                               }
                               else
                               {

                                   information += QString("邮件发送失败，请重试...:%1").arg(error);
                                   QMessageBox::information(NULL,"查找结果",information,QMessageBox::Yes,QMessageBox::Yes);
                                   qDebug() << "发送失败.";
                               }
            }
    }


     return;


}
void findPassword::on_findPushButton_clicked()
{
    QString errorString;
    QString username = ui->usernameLineEdit->text();
    if(username.isEmpty()){
        errorString += "1.请输入用户名\n";
    }

    QString telphone = ui->telphoneLineEdit->text();
    if(telphone.isEmpty()){
        errorString += "2.请输入密码\n";
    }
    QString email = ui->emailLineEdit->text();
    if(email.isEmpty()){
        errorString += "3.请输入邮箱\n";
    }

    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL,"找回密码",errorString,QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    else{
       emit findpassword(username,telphone,email);

       qDebug()<<("find password");// emit loginUser(username,password);
    }
}

