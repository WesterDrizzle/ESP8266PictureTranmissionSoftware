#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

public:
    void initSocket();
    void readPendingDatagrams();
    void ReRequestNextSend();
    void getip();

private:
    QUdpSocket *udpSocket;
signals:
    void newDataReceived(const QByteArray &data);
    void ReceiveOK(void);
};

#endif // SERVER_H
