#include <DTitlebar>
#include <QTextCursor>
#include <DBlurEffectWidget>
#include <QTextBrowser>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bqtextbrowser.h"

MainWindow::MainWindow(DMainWindow *parent) :
    DMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DTitlebar *titlebar = this->titlebar();
    titlebar->setMenu(new QMenu(titlebar));
    titlebar->setSeparatorVisible(true);
//    titlebar->menu()->addAction("设置");   
    BQTextBrowser *text = new BQTextBrowser(ui->textBrowser);
    text->setText("111111111111");

}

MainWindow::~MainWindow()
{
    delete ui;
}
