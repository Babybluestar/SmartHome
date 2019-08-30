#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include <QMainWindow>

#include <QString>
#include <tcpsocket.h>
#include "smtp.h"

namespace Ui {
class findPassword;
}

class findPassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit findPassword(QWidget *parent = 0);
    ~findPassword();

signals:
    void findpassword(const QString &username,const QString &telphone,const QString &email);
    void autoshow(const QString &username);

private slots:
    void showFindResult(const QString &error, const QString &username, const QString &password);


private slots:
    void on_findPushButton_clicked();

private:
    Ui::findPassword *ui;
    TcpSocket *tcpSocket;
    Smtp *sendmail;
};

#endif // FINDPASSWORD_H
