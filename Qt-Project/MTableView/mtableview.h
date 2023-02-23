#ifndef MTABLEVIEW_H
#define MTABLEVIEW_H

#include <QWidget>
#include <DFrame>
#include <QHeaderView>
#include <QPainter>
#include <QRect>
#include <QCheckBox>
#include <QMouseEvent>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QStyleFactory>

//DWIDGET_USE_NAMESPACE

// 复选框表头
class CheckHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit CheckHeaderView(int checkColumnIndex, QPoint topLeft, QSize checkSize, Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);

private:
    int     m_checkColumnIndex;  // 列下标
    QPoint  m_topLeft;           // 勾选框起始坐标
    QSize   m_checkSize;         // 勾选框大小
    bool    m_isChecked;         //勾选框状态

signals:
    void checkStatusChange(bool);
};

class MTableView : public QWidget
{
    Q_OBJECT

public:
    explicit MTableView(QWidget *parent = nullptr);
    ~MTableView();

    void InsertTable(QStringList &listInfo);

    QCheckBox *getCheckBox(QTableWidget *table, int row, int column);

    QCheckBox *setCheckBox(QTableWidget *table, int row, int column, bool checkd);
protected slots:
    // 表头复选框槽函数：
    void SlotCheckBoxStateChange(bool state);

    // 行数据复选框的槽函数
    void SlotSetChecked(int nState);
private:
    QTableWidget *tableWidget = nullptr;

};

#endif // MTABLEVIEW_H
