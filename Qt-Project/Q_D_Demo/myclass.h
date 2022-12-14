#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtCore/QObject>

class MyClassPrivate;
class MyClass: public QObject
{
      Q_OBJECT
public:
      MyClass(QObject *parent = nullptr);
      virtual ~MyClass();
      void dummyFunc();

signals:
      void dummySignal();

private:
      MyClassPrivate * const d_ptr = nullptr;
      Q_DECLARE_PRIVATE(MyClass)
      Q_DISABLE_COPY(MyClass)              //防止指针d_ptr的二次释放
};
#endif // MYCLASS_H
