#include "minfointerfaceinterface.h"

MinfoInterfaceInterface::MinfoInterfaceInterface(const QString& service, const QString& path, const QDBusConnection& connection, QObject* parent /*= nullptr*/)
    :QDBusAbstractInterface(service,path, staticInterfaceName(), connection,parent)
{

}
