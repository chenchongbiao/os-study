#ifndef QDBUSSERVER_H
#define QDBUSSERVER_H

#include <QWidget>

namespace Ui {
class QDBusServer;
}

class QDBusServer : public QWidget
{
    Q_OBJECT

public:
    explicit QDBusServer(QWidget *parent = nullptr);
    ~QDBusServer();

private:
    Ui::QDBusServer *ui;
};

#endif // QDBUSSERVER_H
