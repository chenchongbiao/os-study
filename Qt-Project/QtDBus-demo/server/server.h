#ifndef SERVER_H
#define SERVER_H
#include <QObject>

class server: public QObject
{
    Q_OBJECT
     //定义Interface名称为com.bluesky.test.value
    Q_CLASSINFO("D-Bus Interface", "com.bluesky.test.value")
public:
    server(int value);
public slots:
    int maxValue();
    int minValue();
    int value();
private:
    int m_value;
};

#endif // SERVER_H
