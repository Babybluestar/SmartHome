#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include "userinformation.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();
    bool checkEmail(const QString &email);
    bool checkTelPhone(const QString &phone);

signals:
    void registerUserReady(const UserInformation &user);

private slots:
    void on_commitButton_clicked();
    void registerWindowShow();
    void showRegisterResult(const QString &error);

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
