#ifndef MINFOINTERFACEINTERFACE_H
#define MINFOINTERFACEINTERFACE_H

#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

class MinfoInterfaceInterface : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char* staticInterfaceName() { return "org.example.Examples.MInfoInterface"; }
public:
    MinfoInterfaceInterface(const QString& service, const QString& path, const QDBusConnection& connection, QObject* parent = nullptr);;

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Connect(const QString &strCmmand)
    {
        QVariantList l; l.push_back(strCmmand);
        return asyncCallWithArgumentList("Connect",l);
    }
    inline QDBusPendingReply<> Connect()
    {
        QVariantList l;
        return asyncCallWithArgumentList("onConnect", l);
    }
};

#endif // MINFOINTERFACEINTERFACE_H
