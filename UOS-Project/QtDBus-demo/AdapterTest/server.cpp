#include "server.h"

server::server(int value)
{
    m_value = value;
}

int server::maxValue()
{
    return 100;
}
int server::minValue()
{
    return 0;
}
int server::value()
{
    return m_value;
}
