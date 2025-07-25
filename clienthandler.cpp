#include "clienthandler.h"



ClientHandler::ClientHandler(qintptr socketdesc, QString str)
    : m_str {str}
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketdesc);
    socket->open(QIODeviceBase::WriteOnly);
    //connect(socket, &QTcpSocket::readyRead,this,&ClientHandler::okumayahazir);
    socket->write(m_str.toUtf8());
}

void ClientHandler::start()
{
    QEventLoop loop;
    loop.exec();
}

void ClientHandler::okumayahazir()
{
    QByteArray data = socket->readAll();
    qDebug() << "Client verisi geldi:" << data << "Thread:" << QThread::currentThreadId();
}
