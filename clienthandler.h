#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QEventLoop>
#include <QThread>

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    ClientHandler(qintptr socketdesc, QString str);
    void start();
private:
    QTcpSocket *socket;
    QString m_str;
private slots:
    void okumayahazir();
};

#endif // CLIENTHANDLER_H
