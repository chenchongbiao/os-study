#include <DApplication>
#include <DWidgetUtil>
#include <DDialog>
#include <DMainWindow>
#include <DPushButton>
#include <DPasswordEdit>
#include <QWidget>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DMainWindow win;

    // 将QStyle转为DStyle
    DStyle *style = qobject_cast<DStyle *>(win.style());

    // 创建一个widget容器
    QWidget widget;
    // 给widget设置水平布局
    QHBoxLayout hLayout(&widget);

    // 创建一个打开DDialog的按钮
    DPushButton createDialogBtn("打开一个DDialog", &widget);
    createDialogBtn.setFixedSize(150,40);

    // 将createDialogBtn放入到widget中
    hLayout.addWidget(&createDialogBtn);
    // widget放入主窗口
    win.setCentralWidget(&widget);

    QObject::connect(&createDialogBtn, &DPushButton::clicked, &win, [=](){
        DDialog dialog;

        // 	设置对话框图标,icon 对话框图标
        dialog.setIcon(style->standardIcon(DStyle::SP_MessageBoxWarning));

        // 设置对话框标题
        dialog.setTitle("还原当前系统需要管理员权限");

        // 添加控件到对话框内容布局
        dialog.addContent(new DPasswordEdit);

        // 添加按钮到窗口
        dialog.addButton("取消");
        dialog.addButton("授权", false, DDialog::ButtonRecommend);

        // 以模态框形式显示当前对话框
        dialog.exec();
    });

    win.resize(300,200);
    win.show();
    // 移动窗口到屏幕中心
    Dtk::Widget::moveToCenter(&win);
    return a.exec();
}
