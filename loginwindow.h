#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "registerwindow.h"
#include "serveraddressdialog.h"
#include "tcpsocket.h"
#include <findpassword.h>


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void saveLoginUser(QString username,QString password);

    void displayRemmberLoginUser();

signals:
    void showRegisterWindow(void);
    void loginUser(const QString &username,const QString &password);

private slots:
    void on_checkButton_clicked(bool checked);
    void on_registerAction_triggered();

    void on_serverAction_triggered();

    void on_loginPushButton_clicked();
    void showLoginResult(const QString &error,const QString &clientId);

    void on_forgetPasswordPushButton_clicked();

    void autofill(const QString &username);

private:
    Ui::LoginWindow *ui;
    RegisterWindow *regWin;
    ServerAddressDialog *addressDialog;
    TcpSocket *tcpSocket;
    findPassword *FindPassword;
};

#endif // LOGINWINDOW_H
