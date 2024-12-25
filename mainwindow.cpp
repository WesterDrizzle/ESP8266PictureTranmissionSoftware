#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>

/*

*/
static int header;
static int length;
static int packIdx;
static int picID;
static int Timestamp;
static int currentpackIdx = 0;
static int shouldpackIdx = 0;
static QString body;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyServer = new Server(this);
    disconnect(MyServer, &Server::newDataReceived, this, &MainWindow::processData);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::processData(const QByteArray &data)
{
    ui->tEReceive->append(data);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    header = jsonObj.value("header").toInt();
    length = jsonObj.value("length").toInt();
    packIdx = jsonObj.value("packIdx").toInt();
    picID = jsonObj.value("picID").toInt();
    Timestamp = jsonObj.value("Timestamp").toInt();
    body = jsonObj.value("body").toString();
    if (header == 0)
    {
        shouldpackIdx = length;
    }
    else if (header == 1)
    {
        currentpackIdx++;
        ui->tESend->append(body);
    }
    else if (header == 2)
    {
        // 19

        if (shouldpackIdx == currentpackIdx)
        {
            qDebug() << "Pack Receive Successful";
            auto txt = ui->tESend->toPlainText();
            ui->tESend->clear();
            ui->lBdisplay->clear();
            QImage image;
            // 注意必须用QByteArray形式才行
            if (!image.loadFromData(QByteArray::fromHex(txt.toUtf8()), "JPEG"))
            {
                qDebug() << "Failed to load image from data";
            }
            // 显示图像
            ui->lBdisplay->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            qDebug() << "Pack Receive False";
            qDebug() << "ReReqest For Next Send";
        }
        currentpackIdx = 0;
    }
}
void MainWindow::on_pBconnect_clicked()
{
    if (ui->pBconnect->text() == "断开")
    {
        disconnect(MyServer, &Server::newDataReceived, this, &MainWindow::processData);
        ui->pBconnect->setText("连接");
    }
    else
    {
        connect(MyServer, &Server::newDataReceived, this, &MainWindow::processData);
        ui->pBconnect->setText("断开");
    }
}

void MainWindow::on_pBsend_clicked()
{
    auto txt = ui->tESend->toPlainText();
    ui->lBdisplay->clear();
    ui->tESend->clear();
    txt.remove(' ');
    ui->tESend->setText(txt);
    QImage image;
    // 注意必须用QByteArray形式才行
    if (!image.loadFromData(QByteArray::fromHex(txt.toUtf8()), "JPEG"))
    {
        qDebug() << "Failed to load image from data";
    }
    // 显示图像
    ui->lBdisplay->setPixmap(QPixmap::fromImage(image));
}
