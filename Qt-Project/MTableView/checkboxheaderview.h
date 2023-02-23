#ifndef CHECKBOXHEADERVIEW_H
#define CHECKBOXHEADERVIEW_H

#include <QtGui>
#include <QPainter>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>
#include <QCheckBox>
#include <QEvent>
#include <QStyleFactory>

class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    /**
     * @brief CHeaderView 构造函数
     * @param orientation 方向
     * @param parent 父类对象
     */
    explicit CheckBoxHeaderView(QPoint point, QSize boxSize, Qt::Orientation orientation, QWidget *parent = nullptr);

    /**
     * @brief setColumnCheckable 设置复选框状态
     * @param state 复选框状态
     */
    void setCheckState(bool state);

protected:
    /**
     * @brief paintSection 绘制复选框
     * @param painter 绘制对象
     * @param rect 绘制区域
     * @param logicalIndex 当前索引位置
     */
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    /**
     * @brief  鼠标从表头释放，发送信号，更新model数据
     * @param event 绘制对象
     */
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint  point;          // 勾选框起始屏幕坐标
    QSize   boxSize;        // 复选框大小
    bool    isChecked;      // 勾选框状态

signals:
    void onCheckStateChanged(bool state);   // 勾选状态发生改变信号
};

#endif // CHECKBOXHEADERVIEW_H

