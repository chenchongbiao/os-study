#include "myclass.h"

class MyClassPrivate : public QObject
{
public:
    MyClassPrivate(MyClass *parent)
    : q_ptr(parent)
    {
    }
    void foobar()
    {
        Q_Q(MyClass);
        emit q->dummySignal();
    }
private:
    MyClass * const q_ptr = nullptr;
    Q_DECLARE_PUBLIC(MyClass)

};

MyClass::MyClass(QObject *parent)
  : QObject(parent)
  , d_ptr(new MyClassPrivate(this))
{

}

MyClass::~MyClass()
{
    Q_D(MyClass);
    delete d;
}

void MyClass::dummyFunc()
{
    Q_D(MyClass);
    d->foobar();
}
