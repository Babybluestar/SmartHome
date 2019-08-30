#ifndef SMARTPROTOCOL_H
#define SMARTPROTOCOL_H
#include "userinformation.h"
#include <QJsonObject>

class SmartProtocol
{
public:
    enum{
      USER_REGISTER = 1,
      USER_LOGIN    = 2,
      USER_DEVICE_CONTROL = 3,
      USER_FIND   =4,
    };
    SmartProtocol(const UserInformation &user);
    SmartProtocol(const QByteArray &jsonData);
    SmartProtocol(const QString &username,const QString &password);

    SmartProtocol(const QString &username,const QString &telphone,const QString &email);

    SmartProtocol(const QString &clientId,int deviceId,int statu);
    void addFunctionId(int id);
    QByteArray toProtocolData(void);
    bool getSmartProtocolStatu();
    int getSmartProtocolFunctionId(void);
    QString getSmartProtocolError();
    QString getSmartProtocolClientId(void);

    QString getSmartProtocolUsername();
    QString getSmartProtocolPassword();

private:
    QJsonObject content;
};

#endif // SMARTPROTOCOL_H
