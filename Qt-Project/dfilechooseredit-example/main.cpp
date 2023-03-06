#include <DApplication>
#include <DWidgetUtil>
#include <DMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <DFileChooserEdit>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DMainWindow win;

    // 创建一个widget容器
    QWidget widget;
    // 创建带有选择文件按钮的文本编辑框
    DFileChooserEdit dialog;

    // 给widget设置水平布局
    QHBoxLayout hLayout(&widget);

    dialog.setFileMode(QFileDialog::Directory);  // 指定选择的模式，选择目录。
    dialog.setDirectoryUrl(QUrl("file:///home"));  // 设置文件选择器打开路径为home目录

    // 将dialogn放入到widget中
    hLayout.addWidget(&dialog);
    // widget放入主窗口
    win.setCentralWidget(&widget);

    win.resize(300,200);
    win.show();
    // 移动窗口到屏幕中心
    Dtk::Widget::moveToCenter(&win);
    return a.exec();
}
