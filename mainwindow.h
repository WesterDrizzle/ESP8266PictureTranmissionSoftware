#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void processData(const QByteArray &data);
private slots:
    void on_pBconnect_clicked();

    void on_pBsend_clicked();

private:
    Ui::MainWindow *ui;
    Server *MyServer;
};
#endif // MAINWINDOW_H
