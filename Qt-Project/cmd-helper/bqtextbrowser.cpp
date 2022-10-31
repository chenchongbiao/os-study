#include "bqtextbrowser.h"
#include "ui_bqtextbrowser.h"

#include <QTextBrowser>

BQTextBrowser::BQTextBrowser(QWidget *parent) :
    QTextBrowser(parent),
    ui(new Ui::BQTextBrowser)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(1,40,73,130);");
    this->setTextColor(Qt::yellow);
}

BQTextBrowser::~BQTextBrowser()
{
    delete ui;
}
