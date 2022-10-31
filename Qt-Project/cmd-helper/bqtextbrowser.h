#ifndef BQTEXTBROWSER_H
#define BQTEXTBROWSER_H

#include <QWidget>
#include <QTextBrowser>

namespace Ui {
class BQTextBrowser;
}

class BQTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    explicit BQTextBrowser(QWidget *parent = nullptr);
    ~BQTextBrowser();

private:
    Ui::BQTextBrowser *ui;
};

#endif // BQTEXTBROWSER_H
