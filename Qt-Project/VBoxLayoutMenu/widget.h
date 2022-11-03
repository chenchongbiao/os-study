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
    void checkMenu(QPushButton *btn, bool isCheck);

private slots:
    void buttonClick();

private:
    void initUI();

private:
    Ui::Widget *ui;
    QList<MenuButton *> topMenuList;
    QList<MenuButton *> leftMenuList;
    QList<QPushButton *> rightMenuList;
    QWidget *topMenuWidget;
    QWidget *leftMenuWidget;
    QWidget *rightMenuWidget;
    QHBoxLayout *topMenuWidgetLayout;
    QVBoxLayout *leftMenuWidgetLayout;
    QVBoxLayout *rightMenuWidgetLayout;
    MenuButton *btn1,*btn2,*btn3,*btn4;
    MenuButton *menuDocker,*menuFtp,*menuHome,*menuProgram,*menuSetting,*menuSoftware,*menuSql;
    QPushButton *rbt1,*rbt2,*rbt3,*rbt4,*rbt5,*rbt6,*rbt7;

};

#endif // WIDGET_H
