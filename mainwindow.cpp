#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::baglantidayken);
    server->listen(QHostAddress::Any, 12345);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::baglantidayken()
{
    qDebug()<< "sjss";
    QTcpSocket * clientSocket = server->nextPendingConnection();
    connect(clientSocket,&QTcpSocket::readyRead,this,[clientSocket](){
        QByteArray data = clientSocket->readAll();
        QtConcurrent::run([data, clientSocket](){
            qDebug() << "[QtConcurrent] Başlıyor";
            qDebug() << "Client verisi geldi:" << data << "Thread:" << QThread::currentThreadId();
            QMetaObject::invokeMethod(clientSocket, [clientSocket]() {
                clientSocket->write("MESAJINI ALDIM CLIENT BU DA SANA CEVABIM");
            });
        });
    });
        //qintptr desc = clientSocket->socketDescriptor();
        // clientSocket->deleteLater();
        // QTimer::singleShot(0, this, [desc]() {
        //     QtConcurrent::run([desc]() {
        //         qDebug() << "[QtConcurrent] Başlıyor";
        //         auto *handler = new ClientHandler(desc, "asdfg");
        //         handler->start();
        //         delete handler;
        //     });
        // });


}

