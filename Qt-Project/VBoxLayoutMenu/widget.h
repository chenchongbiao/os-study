#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    QList<MenuButton *> topMenuList;
    QList<MenuButton *> leftMenuList;
    QWidget *topMenuWidget;
    QHBoxLayout *topMenuWidgetLayout;
    QWidget *leftMenuWidget;
    QVBoxLayout *leftMenuWidgetLayout;
    MenuButton *btn1,*btn2,*btn3,*btn4;
    MenuButton *menuDocker,*menuFtp,*menuHome,*menuProgram,*menuSetting,*menuSoftware,*menuSql;

};

#endif // WIDGET_H
