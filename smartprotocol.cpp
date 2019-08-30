#include "smartprotocol.h"
#include <QJsonDocument>
#include <QDebug>
#include <QJsonParseError>

SmartProtocol::SmartProtocol(const UserInformation &user)
{
    content.insert("username",user.getName());
    content.insert("password",user.getPassword());
    content.insert("email",user.getEmail());
    //content.insert("telphone",user.getTelphone());
    content["telphone"] = user.getTelphone();
}

SmartProtocol::SmartProtocol(const QByteArray &jsonData)
{
   QJsonParseError jsonError;
   QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
   if(jsonDoc.isEmpty() || jsonError.error != QJsonParseError::NoError){
       qDebug() << "fail to from json"  << jsonError.errorString();
       return;
   }
   content = jsonDoc.object();
}

SmartProtocol::SmartProtocol(const QString &username, const QString &password)
{
    content.insert("username",username);
    content.insert("password",password);
}

SmartProtocol::SmartProtocol(const QString &username, const QString &telphone, const QString &email)
{
    content.insert("username",username);
    content.insert("telphone",telphone);
    content.insert("email",email);

}

SmartProtocol::SmartProtocol(const QString &clientId, int deviceId, int statu)
{
    content["clientId"] = clientId;
    content["deviceId"] = deviceId;
    content["controlStatu"] = statu;
}

void SmartProtocol::addFunctionId(int id)
{
    content["functionId"] = id;
}


QByteArray SmartProtocol::toProtocolData()
{
    QJsonDocument jsonDoc(content);

    return jsonDoc.toJson();
}

bool SmartProtocol::getSmartProtocolStatu()
{
    int ret = content["statu"].toInt();
    if(ret != 0){
        return false;
    }

    return true;
}

int SmartProtocol::getSmartProtocolFunctionId()
{
    return content["functionId"].toInt();
}

QString SmartProtocol::getSmartProtocolError()
{
    QString errorString = content["error"].toString();
    return errorString;
}

QString SmartProtocol::getSmartProtocolClientId()
{
    return content["clientId"].toString();
}

QString SmartProtocol::getSmartProtocolUsername()
{
     qDebug()<<"1111";
     qDebug()<< content["username"].toString();
     return content["username"].toString();
}

QString SmartProtocol::getSmartProtocolPassword()
{

  return content["password"].toString();
}
