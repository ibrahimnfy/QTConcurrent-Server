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
    qintptr desc = clientSocket->socketDescriptor();
    clientSocket->deleteLater();
    QtConcurrent::run([desc](){
        qDebug()<< "sass";

        ClientHandler handler(desc, "asdfg");
        handler.start();
    });
}

