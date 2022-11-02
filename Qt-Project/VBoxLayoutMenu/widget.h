#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "menubutton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void buttonClick();

private:
    void initUI();

private:
    Ui::Widget *ui;
    QList<MenuButton *> menuList;
    QWidget *menuWidget;
    QHBoxLayout *menuWidgetLayout;
    MenuButton *btn1;
    MenuButton *btn2;
    MenuButton *btn3;
    MenuButton *btn4;
};

#endif // WIDGET_H
