#include "server.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QNetworkInterface>
Server::Server(QObject *parent)
    : QObject{parent}
{
    this->udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 3333);
    getip();
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Server::readPendingDatagrams);
    // connect(udpSocket, &QUdpSocket::bytesWritten,
    //         this, &Server::readPendingDatagrams);
}
void Server::ReRequestNextSend()
{
    QNetworkDatagram datagram;
    datagram.setData("ReSend");
    udpSocket->writeDatagram(datagram);
    qDebug() << "Server ReRequestNextSend";
}
void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        emit newDataReceived(datagram.data());
    }
}

void Server::getip()
{
    QList<QHostAddress> interfaces = QNetworkInterface::allAddresses();
    for (const QHostAddress &interface : interfaces)
    {
        // 过滤掉回环接口和未启用的接口
        qDebug() << interface.toString();
    }
}