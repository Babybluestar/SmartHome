#include "tcpsocket.h"
#include <QHostAddress>
#include "serveraddressdialog.h"
#include "smartprotocol.h"
#include <QMessageBox>
#include <QDebug>
#include <smartprotocol.h>

TcpSocket::TcpSocket()
{
    tcp = new QTcpSocket;
    connect(tcp,SIGNAL(readyRead()),this,SLOT(recvTcpData()));
}
TcpSocket::~TcpSocket()
{
    delete tcp;
}

void TcpSocket::recvTcpData()
{
   QString errorString;
   QByteArray tcpData = tcp->readAll();

   SmartProtocol smartProtocol(tcpData);

   if(smartProtocol.getSmartProtocolStatu() == true){
       errorString = "";
    // qDebug()<<"hello";

   }else{
       errorString = smartProtocol.getSmartProtocolError();
   }

   switch(smartProtocol.getSmartProtocolFunctionId()){
   case SmartProtocol::USER_REGISTER:
       emit registerStatu(errorString);
       break;

   case SmartProtocol::USER_LOGIN:
       emit loginStatu(errorString,smartProtocol.getSmartProtocolClientId());
       break;

   case SmartProtocol::USER_FIND:
         emit findStatu(errorString,smartProtocol.getSmartProtocolUsername(),smartProtocol.getSmartProtocolPassword());

      // qDebug()<<smartProtocol.getSmartProtocolUsername();
       break;
       }
   return;
}

void TcpSocket::registerUserByTcp(const UserInformation &user)
{
    QString serverIp   = ServerAddressDialog::getServerIP();
    short   serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再注册",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    if(tcp->state() == QTcpSocket::UnconnectedState){
       tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    SmartProtocol smartProtocol(user);
    smartProtocol.addFunctionId(SmartProtocol::USER_REGISTER);
    tcp->write(smartProtocol.toProtocolData());

    return;
}

void TcpSocket::loginUserByTcp(const QString &username, const QString &password)
{
    QString serverIp   = ServerAddressDialog::getServerIP();
    short   serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再登录",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    if(tcp->state() == QTcpSocket::UnconnectedState){
       tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    SmartProtocol smartProtocol(username,password);
    smartProtocol.addFunctionId(SmartProtocol::USER_LOGIN);
    tcp->write(smartProtocol.toProtocolData());

    return;
}


void TcpSocket::findUserByTcp(const QString &username, const QString &telphone, const QString &email)
{


    QString serverIp   = ServerAddressDialog::getServerIP();
    short   serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再登录",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    if(tcp->state() == QTcpSocket::UnconnectedState){
       tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

   // SmartProtocol smartProtocol(username,password);
    SmartProtocol smartProtocol(username,telphone,email);


    smartProtocol.addFunctionId(SmartProtocol::USER_FIND);

    tcp->write(smartProtocol.toProtocolData());

    return;


}

void TcpSocket::controlDeviceByTcp(int deviceId, int statu,const QString &clientId)
{
    QString serverIp   = ServerAddressDialog::getServerIP();
    short   serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再登录",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    if(tcp->state() == QTcpSocket::UnconnectedState){
       tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    SmartProtocol smartProtocol(clientId,deviceId,statu);
    smartProtocol.addFunctionId(SmartProtocol::USER_DEVICE_CONTROL);
    tcp->write(smartProtocol.toProtocolData());

    return;
}
