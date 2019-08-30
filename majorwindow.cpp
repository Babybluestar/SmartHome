#include "majorwindow.h"
#include "ui_majorwindow.h"
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QJsonParseError>
#include <QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>

//Game * game;

MajorWindow::MajorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MajorWindow)
{
    ui->setupUi(this);

    room = new RoomWindow;
    connect(room,SIGNAL(controlDevice(int,int)),this,SLOT(controlDeviceSlot(int,int)));

    tcp = new TcpSocket;

    networkManager= new QNetworkAccessManager;
    QString httpUrl = "http://www.tianqiapi.com/api/";
    QNetworkRequest request(httpUrl);
    request.setRawHeader("version","v1");
    networkReply = networkManager->get(request);
    connect(networkReply,SIGNAL(finished()),this,SLOT(displayReplyData()));

    widght = new Widget;

    gameChoose = new GameChoose;

    this->startTimer(1000);
}

MajorWindow::~MajorWindow()
{
    delete ui;
}

void MajorWindow::timerEvent(QTimerEvent *event)
{
   QTime time = QTime::currentTime();
   //1
   ui->timeLabel->setText(time.toString("hh:mm:ss"));

   QDate date = QDate::currentDate();
   ui->dateLabel->setText(date.toString("yyyy-MM-dd dddd"));
}

void MajorWindow::on_devicePushButton_clicked()
{
    room->show();
}

void MajorWindow::controlDeviceSlot(int deviceId, int statu)
{
    //通过tcp发出控制指令
    tcp->controlDeviceByTcp(deviceId,statu,clientId);
}

void MajorWindow:: MajorWindow::displayReplyData()
{
    QByteArray jsonData = networkReply->readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
    if(jsonDoc.isEmpty() || jsonError.error != QJsonParseError::NoError){
        qDebug() << "fail to from json"  << jsonError.errorString();
        return;
}
    QJsonObject jsonObject=jsonDoc.object();
    QJsonArray dataArray = jsonObject["data"].toArray();
    QJsonObject firstObject=dataArray[0].toObject();
    int humidity=firstObject["humidity"].toInt();
    QString tem = firstObject["tem"].toString();
    QString wea = firstObject["wea"].toString();

    //继续...
    QString temText=QString("%1:%2").arg(ui->temLabel->text()).arg(tem);
    ui->temLabel->setText(temText);
    QString humidityText=QString("%1:%2").arg(ui->humidityLabel->text()).arg(humidity);
    ui->humidityLabel->setText(humidityText);
    QString sunText=QString("%1:%2").arg(ui->sunLabel->text()).arg(wea);
    ui->sunLabel->setText(sunText);

}
QString MajorWindow::getClientId() const
{
    return clientId;
}

void MajorWindow::setClientId(const QString &value)
{
    clientId = value;
}

void MajorWindow::on_pushButton_clicked()
{
    widght->show();
}

void MajorWindow::on_pushButton_4_clicked()
{
    gameChoose->show();
    //game = new Game();
    //game->show();
    //game->displayMainMenu();

}
