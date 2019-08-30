#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QMainWindow>

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomWindow(QWidget *parent = 0);
    ~RoomWindow();

signals:
    void controlDevice(int deviceId,int statu);

private slots:
    void on_ledPushButton1_clicked(bool checked);

    void on_ledPushButton2_clicked(bool checked);

    void on_fanPushButton_clicked(bool checked);

    void on_doorPushButton_clicked(bool checked);



private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
