#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include "majorwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <findpassword.h>


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    regWin = new RegisterWindow;

    connect(this,SIGNAL(showRegisterWindow()),regWin,SLOT(registerWindowShow()));

    addressDialog = new ServerAddressDialog;

    tcpSocket = new TcpSocket;
    connect(this,SIGNAL(loginUser(QString,QString)),tcpSocket,SLOT(loginUserByTcp(QString,QString)));
    connect(tcpSocket,SIGNAL(loginStatu(QString,QString)),this,SLOT(showLoginResult(QString,QString)));

    FindPassword = new findPassword();
    connect(FindPassword,SIGNAL(autoshow(QString)),this,SLOT(autofill(QString)));
    bool ok = QFile::exists("user.txt");
     if(ok){
         displayRemmberLoginUser();
         ui->checkButton->setText("√");



     }
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete regWin;
    delete tcpSocket;
    delete FindPassword;
}

void LoginWindow::saveLoginUser(QString username, QString password)
{
  QFile file("user.txt");
  bool ok = file.open(QFile::WriteOnly);
  if(!ok){
      qDebug()<<"Fail to open user.txt:"<<file.errorString();
      return;
  }
  username += "\n";
  password += "\n";
  file.write(username.toUtf8());
  file.write(password.toUtf8());
  file.close();

}

void LoginWindow::displayRemmberLoginUser()
{
  QFile file("user.txt");
  bool ok = file.open(QFile::ReadOnly);
if(!ok){
    qDebug()<<"Fail to open user.txt:"<<file.errorString();
    return;
}
QString username = file.readLine();
username.remove("\n");
QString password = file.readLine();
password.remove("\n");
ui->usernameLineEdit->setText(username);
ui->passwordLineEdit->setText(password);
file.close();
return;
}

void LoginWindow::on_checkButton_clicked(bool checked)
{
    qDebug() << checked;
    if(checked  == true){
        ui->checkButton->setText("√");
       QString  username = ui->usernameLineEdit->text();
       QString password = ui->passwordLineEdit->text();
       saveLoginUser(username,password);
    }else{
        ui->checkButton->setText("");
        QFile::remove("user.txt");
    }
}

void LoginWindow::on_registerAction_triggered()
{
    qDebug() << "register action";
    emit showRegisterWindow();
}

void LoginWindow::on_serverAction_triggered()
{
    addressDialog->show();
}

void LoginWindow::on_loginPushButton_clicked()
{
    QString errorString;
    QString username = ui->usernameLineEdit->text();
    if(username.isEmpty()){
        errorString += "1.请输入用户名\n";
    }

    QString password = ui->passwordLineEdit->text();
    if(password.isEmpty()){
        errorString += "2.请输入密码\n";
    }
#if 1
    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL,"用户名和密码",errorString,QMessageBox::Yes,QMessageBox::Yes);
        return;
    }else{
        emit loginUser(username,password);
    }
#endif

    //showLoginResult("","1234");
}

void LoginWindow::showLoginResult(const QString &error, const QString &clientId)
{
    if(!error.isEmpty()){
        QString str = QString("很遗憾，登陆失败:%1").arg(error);
        QMessageBox::warning(NULL,"登录用户",str,QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    //登录成功则关闭当前界面，跳转到主界面
     MajorWindow *majorWindow = new MajorWindow;
     majorWindow->setClientId(clientId);
     majorWindow->show();

     qDebug() << "clientId : " << clientId;
     this->close();

     return;
}

void LoginWindow::on_forgetPasswordPushButton_clicked()
{
    FindPassword->show();
}

void LoginWindow::autofill(const QString &username)
{
    ui->usernameLineEdit->setText(username);

}
