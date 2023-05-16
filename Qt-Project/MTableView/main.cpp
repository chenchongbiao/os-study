#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>
#include <QTableWidget>

#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>

#include "mtableview.h"
#include "checkboxheaderview.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("dtk-application");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon(":/images/logo.svg"));
    a.setProductName("Dtk Application");
    a.setApplicationDescription("This is a dtk template application.");

    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DTK Application"));

    // 保存程序的窗口主题设置
    DApplicationSettings as;
    Q_UNUSED(as)

    DMainWindow w;
    w.titlebar()->setIcon(QIcon(":/images/logo.svg"));
    w.titlebar()->setTitle("Hello dtk");
    // 设置标题，宽度不够会隐藏标题文字
    w.setMinimumSize(QSize(600, 200));

//    QWidget *cw = new QWidget(&w);
//    QVBoxLayout *layout = new QVBoxLayout(cw);
//    MTableView *table = new MTableView(&w);

    QTableWidget *table = new QTableWidget(&w);
    CheckBoxHeaderView *header = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);
    header->setCheckState(true);

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "" << "按钮" << "操作" );
    table->setHorizontalHeader(header);
    table->setColumnWidth(0,20);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->setRowCount(1);


    QCheckBox *box = new QCheckBox();
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(box);
    // 设置水平居中
    layout->setAlignment(box, Qt::AlignCenter);
    // 设置部件边距
    layout->setMargin(0);
    // 添加布局
    widget->setLayout(layout);

    // table->setCellWidget(0, 0, widget);
    // table->setCellWidget(0, 1, new QPushButton("测试"));

//    QDate today = QDate::currentDate();
//    DProgressBar *yearProgressBar = new DProgressBar();
//    yearProgressBar->setMaximum(today.daysInYear());
//    // 绑定字体大小
//    DFontSizeManager::instance()->bind(yearProgressBar, DFontSizeManager::T1);

//    yearProgressBar->setAlignment(Qt::AlignCenter);
//    QObject::connect(yearProgressBar, &DProgressBar::valueChanged, yearProgressBar, [yearProgressBar](int value){
//        yearProgressBar->setFormat(QString("您的 %1 使用进度： %2%").arg(QDate::currentDate().year())
//                                   .arg(value * 100 / yearProgressBar->maximum()));
//    });

//    layout->addWidget(yearProgressBar);
    w.setCentralWidget(table);
    w.show();

//    auto animation = new QPropertyAnimation(yearProgressBar, "value");
//    animation->setDuration(5000);
//    animation->setStartValue(0);
//    animation->setEndValue(today.dayOfYear());
//    animation->start();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
