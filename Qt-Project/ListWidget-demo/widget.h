#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLabel>
#include <DPushButton>
#include <QRadioButton>
#include <DLabel>

DWIDGET_USE_NAMESPACE

namespace Ui {
class widget;
}

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
    void initUI();

private:
    Ui::widget *ui;
    QWidget *conBtnWidget;               // 容器界面的操作按钮
    QWidget *columnWidget;               // 列名
    QHBoxLayout *conBtnLayout;           // 按钮的布局
    QHBoxLayout *columnLayout;           // 列名的布局
    DPushButton *startBtn;               // 启动容器
    DPushButton *stopBtn;                // 停止容器
    DPushButton *restartBtn;             // 重启容器
    DPushButton *deleteBtn;              // 删除容器
    DPushButton *cteateBtn;              // 创建容器
    QRadioButton *checkAllBtn;           // 全选按钮
    DLabel *name;                        // 容器名称
    DLabel *status;                      // 容器状态
    DLabel *address;                     // 容器监控
    DLabel *image;                       // 容器镜像
    DLabel *port;                        // 容器端口
    DLabel *ip;                          // 容器ip
};

#endif // WIDGET_H
