#ifndef GAMECHOOSE_H
#define GAMECHOOSE_H

#include <QWidget>
#include "Game.h"
#include "mainwindow.h"

namespace Ui {
class GameChoose;
}

class GameChoose : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoose(QWidget *parent = nullptr);
    ~GameChoose();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameChoose *ui;
    MainWindow *mainWindow;

};

#endif // GAMECHOOSE_H
