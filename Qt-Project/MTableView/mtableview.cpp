#include "mtableview.h"

CheckHeaderView::CheckHeaderView(int checkColumnIndex, QPoint topLeft, QSize checkSize, Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent)
{
    m_checkColumnIndex = checkColumnIndex;
    m_topLeft = topLeft;
    m_checkSize = checkSize;
    m_isChecked = false;
}

void CheckHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == m_checkColumnIndex)
    {
        QStyleOptionButton option;
        int width = 10;
        for (int i=0; i < logicalIndex; i++)
        {
            width += sectionSize(i);
        }
        option.rect = QRect(m_topLeft.x(), m_topLeft.y(), m_checkSize.width(), m_checkSize.height());

        if (m_isChecked)
        {
            option.state = QStyle::State_On;
        } else {
            option.state = QStyle::State_Off;
        }
        QCheckBox *check = new QCheckBox();
        check->setVisible(false);
        QString sheet = QString("QCheckBox::indicator {width: %1px;  height: %2px;}")
                .arg(m_checkSize.width()).arg(m_checkSize.height());
        check->setStyleSheet(sheet);
        this->style()->drawControl(QStyle::CE_CheckBox, &option, painter, check);
    }
}

void CheckHeaderView::mousePressEvent(QMouseEvent *event)
{
    if (visualIndexAt(event->pos().x() == m_checkColumnIndex))
    {
        m_isChecked = !m_isChecked;
        this->updateSection(m_checkColumnIndex);
        emit checkStatusChange(m_isChecked);
    }
    QHeaderView::mousePressEvent(event);
}

MTableView::MTableView(QWidget *parent) :
    QWidget(parent)
{
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 禁止编辑
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setColumnCount(5);
    tableWidget->setRowCount(0);

    CheckHeaderView *header = new CheckHeaderView(0, QPoint(50 , 13),QSize(50 , 50 ), Qt::Horizontal, tableWidget);
    header->setObjectName(QStringLiteral("m_checkHeaderView"));

    tableWidget->setHorizontalHeader(header);
    connect(header, &CheckHeaderView::checkStatusChange, this, &MTableView::SlotCheckBoxStateChange);

    header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignCenter);

    tableWidget->setStyleSheet("QTableWidget::indicator {width: 40px;height: 40px;}"); //QTableWidget::indicator:unchecked {image: url(:/icon/unchecked.png);}QTableWidget::indicator:checked {image: url(:/icon/checked.png);}");
    tableWidget->horizontalHeader()->setMinimumHeight(80);
    tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一列自动充满
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{border:0px solid rgb(218, 222, 226);background-color: rgb(204, 217, 230);font: 11pt '微软雅黑'}");

    //设置表头
    QStringList mheader;
    mheader << tr("") << tr("检测对象") << tr("检测项目") << tr("状态描述");
    tableWidget->setHorizontalHeaderLabels(mheader);
    QStringList list ;
    list << "" << "对象" << "项目" << "描述";// << <<;
    for (int i = 0; i < 10; i++) {
        InsertTable(list);
    }
}

void MTableView::InsertTable(QStringList &listInfo)
{
    int nRowCount =tableWidget->rowCount();
    tableWidget->setRowCount(nRowCount + 1);

    QTableWidgetItem* item;// = new QTableWidgetItem(QString("%1").arg(nRowCount + 1));
    for(int i = 0; i < listInfo.size(); i++)
    {
        item = new QTableWidgetItem(listInfo.at(i));
        item->setTextAlignment(Qt::AlignCenter);
        if(i == 0)
        {
            QCheckBox* pCheckBox = setCheckBox(tableWidget,nRowCount, 0, false);
            bool b = connect(pCheckBox, &QCheckBox::stateChanged, this, &MTableView::SlotSetChecked);
            int i = 1;
            // item->setCheckState(Qt::Unchecked);
            // tableWidget->setItem(nRowCount, i, item);
            //SetCheckbox(nRowCount);
        } else {
             tableWidget->setItem(nRowCount, i, item);
        }
    }
}

QCheckBox* MTableView::getCheckBox(QTableWidget *table,int row ,int column)
{
    QWidget* pWidget = nullptr;
    pWidget = table->cellWidget(row,column); //找到单元格
    QCheckBox *pCheckBox = nullptr;
    bool bNew = true;
    if(pWidget != nullptr) //
    {
        bNew = false;
    }
    if(bNew)
    {
        pWidget = new QWidget(table); //创建一个widget
        QHBoxLayout *hLayout = new QHBoxLayout(pWidget); //创建布局
        pCheckBox = new QCheckBox(pWidget);
        // 根据objectName ,去拆解所属的tableWidget 、行、列
        pCheckBox->setObjectName(QString("%1_%2_%3_Itme").arg(table->objectName()).arg(row).arg(column));
        pCheckBox->setChecked(false);
        pCheckBox->setFont(table->font());
        pCheckBox->setFocusPolicy(Qt::NoFocus);
        pCheckBox->setStyle(QStyleFactory::create("fusion"));
        pCheckBox->setStyleSheet(QString(".QCheckBox {margin:3px;border:0px;}QCheckBox::indicator {width: %1px; height: %1px; }").arg(50));
        hLayout->addWidget(pCheckBox); //添加
        hLayout->setMargin(0); //设置边缘距离
        pWidget->setLayout(hLayout); //设置widget的布局
        table->setCellWidget(row,column,pWidget);
    }
    QList<QCheckBox *> allCheckBoxs =  pWidget->findChildren<QCheckBox *>();
    if(allCheckBoxs.size() > 0)
        pCheckBox = allCheckBoxs.first();
    return pCheckBox;
}

QCheckBox* MTableView::setCheckBox(QTableWidget*table,int row ,int column,bool checkd)
{
    QCheckBox *check = getCheckBox(table,row,column);
    if(check != 0) //
    {
        check->setChecked(checkd);
    }
    QCheckBox::connect(check,&QCheckBox::stateChanged,[=]{
        QString objectName = check->objectName();
        QStringList nameList = objectName.split("_");//拆解
        if(nameList.count() == 4)
        {
            QString tableName = nameList.at(0);//表格名称
            int row = nameList.at(1).toInt();//行
            int column = nameList.at(2).toInt();//列
            bool checked = check->isChecked();//是否被选中
            //知道了表格、行、列，就可以执行我们所需要的操作了。。。
            qDebug() << QString("%1表第%2行第%3列是否被选中：%4")
                        .arg(tableName).arg(row).arg(column).arg(checked?"是":"否");
        }
    });
    return check;
}

void MTableView::SlotSetChecked(int nState)
{
    QCheckBox *senderObj = qobject_cast<QCheckBox*>(sender());
    if (senderObj == nullptr)
    {
        return;
    }
    qDebug() << senderObj->frameGeometry().x() << senderObj->frameGeometry().y() << "-------------------";
    QModelIndex idx = tableWidget->indexAt(QPoint(senderObj->parentWidget()->frameGeometry().x(), senderObj->parentWidget()->frameGeometry().y()));
    int row = idx.row();
    bool enable = senderObj->isChecked();
    qDebug() << row << enable <<"+++++++++++++++++++++";
}

void MTableView::SlotCheckBoxStateChange(bool state)
{
    // 如果（不）勾选了表头复选框，遍历表格，做相应操作；如果勾选表格中复选框，对表头做相应操作，要注意表头的三态。
    int i = 1;
}

MTableView::~MTableView()
{
//    delete ui;
}
