#include "gamechoose.h"
#include "ui_gamechoose.h"


Game *game;

GameChoose::GameChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoose)
{
    ui->setupUi(this);
    mainWindow = new MainWindow;
}

GameChoose::~GameChoose()
{
    delete ui;
}

void GameChoose::on_pushButton_clicked()
{
    game = new Game();
    game->show();
    game->displayMainMenu();
}

void GameChoose::on_pushButton_2_clicked()
{
    mainWindow->show();
}
