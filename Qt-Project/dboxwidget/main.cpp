#include <DApplication>
#include <DWidgetUtil>
#include <DMainWindow>
#include <QBoxLayout>
#include <dboxwidget.h>
#include <DLineEdit>
#include <DPushButton>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DMainWindow win;

    // 设置水平方向 从左到右排列
    QBoxLayout::Direction direction = QBoxLayout::LeftToRight;

    // 创建DBoxWidget对象
    DBoxWidget box(direction, &win);

    // 添加一个DLineEdit控件，和一个按钮，可以看到控件水平放置
    box.addWidget(new DLineEdit());
    box.addWidget(new DPushButton("按钮"));

    // 设置外边距为30px
    box.layout()->setMargin(30);

    // widget放入主窗口
    win.setCentralWidget(&box);

    win.resize(300,200);
    win.show();
    // 移动窗口到屏幕中心
    Dtk::Widget::moveToCenter(&win);
    return a.exec();
}
