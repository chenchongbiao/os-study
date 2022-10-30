#include <QtDBus/QDBusConnection>

#include "qdbusserver.h"
#include "ui_qdbusserver.h"
#include "minfointerfaceinterface.h"

QDBusServer::QDBusServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDBusServer)
{
    ui->setupUi(this);
    MinfoInterfaceInterface* info = new MinfoInterfaceInterface("com.bluesky.MInfoInterface", "/MInfo",
        QDBusConnection::sessionBus(),this);
    QThread::usleep(1);
    QDBusPendingReply<> re =  info->Connect("123123");
    QDBusError e = re.error();
}

QDBusServer::~QDBusServer()
{
    delete ui;
}
