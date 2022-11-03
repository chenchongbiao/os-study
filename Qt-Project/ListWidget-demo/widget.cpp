#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    initUI();
}

widget::~widget()
{
    delete ui;
}

void widget::initUI()
{

}
