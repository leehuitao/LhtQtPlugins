#include "table.h"

#include <QComboBox>
#include <QMouseEvent>
#include <QVBoxLayout>

Table::Table(QWidget *parent):QWidget(parent)
{

}

Table::~Table()
{

}

void Table::init()
{
    m_tableView = new TableView(this);
    m_tableView->setIsAction(1);
    m_tableItemModel = new TableItemModel(0,100,this);

    m_tableView->setColumnWidth(ColTest1 , 50);

    m_tableView->setColumnWidth(ColTest2 , 50);

    m_tableView->setColumnWidth(ColTest3 , 50);

//    m_tableView->setColumnWidth(ColTest4 , 50);

//    m_tableView->setColumnWidth(ColTest5 , 50);

//    m_tableView->setColumnWidth(ColTest6 , 50);

//    m_tableView->setColumnWidth(ColTest7 , 50);

    m_tableView->setFrameShape(QFrame::NoFrame);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->verticalHeader()->setVisible(1);
    m_tableView->verticalHeader()->setFixedWidth(30);
    m_tableView->verticalHeader()->setHighlightSections(1);
    m_tableView->horizontalHeader()->setHighlightSections(1);
    m_tableView->horizontalHeader()->setStretchLastSection(0);
    m_tableView->horizontalHeader()->setVisible(1);
    m_tableView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_tableView->setUpdatesEnabled(1);


    m_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_tableView->setItemDelegateForColumn(ColTest1 , new ItemDelegate(m_tableView));
    m_tableView->setItemDelegateForColumn(ColTest2 , new ItemDelegate(m_tableView));
    m_tableView->setItemDelegateForColumn(ColTest3 , new ItemDelegate(m_tableView));
    m_tableView->setModel(m_tableItemModel);
    m_proxy = new QSortFilterProxyModel(m_tableView);
    m_proxy->setSourceModel(m_tableItemModel);
    m_proxy->setDynamicSortFilter(1);

    m_tableView->setModel(m_proxy);

    m_tableHeader = new TableHeader(this);
    m_tableView->setHorizontalHeader(m_tableHeader);
    connect(m_tableHeader,&TableHeader::filter,this,&Table::onFilter);
    connect(m_tableHeader,&TableHeader::sortUp,[=](int index){
        m_proxy->setFilterKeyColumn(index);
        m_proxy->sort(index,Qt::AscendingOrder);
    });
    connect(m_tableHeader,&TableHeader::sortDown,[=](int index){
        m_proxy->setFilterKeyColumn(index);
        m_proxy->sort(index,Qt::DescendingOrder);
    });

    connect(m_tableView,SIGNAL(signRightClicked(const QModelIndex& ,unsigned)),this,SLOT(slotRightClicked(const QModelIndex &, unsigned)));
    connect(m_tableView,SIGNAL(signRightClicked(QPoint, bool)),this,SLOT(slotRightClicked(QPoint, bool)));

    QVBoxLayout * vLayout = new QVBoxLayout(this);
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(2,0,5,0);
    vLayout->addWidget(m_tableView);
    setLayout(vLayout);
}

void Table::updateTable()
{

}

void Table::onFilter(int index, QString msg)
{
    m_proxy->setFilterKeyColumn(index);
    if(!msg.contains(";")){
        m_proxy->setFilterRegularExpression(msg);
        return;
    }
    QStringList list = msg.split(";");
    QString rule;
    for(int i = 0 ; i < list.size() ; i++){
        if(i != list.size() -1)
            rule.append(list.at(i)+"|");
        else
            rule.append(list.at(i));
    }
    m_proxy->setFilterRegularExpression(rule);
}

void Table::slotRightClicked(const QModelIndex &model, unsigned index)
{
    m_index = model;
    m_currentIndex = index;
}

void Table::slotRightClicked(QPoint, bool)
{

}

TableView::TableView(QWidget *parent):QTableView(parent)
{
    connect(this,&QTableView::pressed,this,&TableView::slotOnClicked);
}

TableView::~TableView()
{

}

void TableView::mouseReleaseEvent(QMouseEvent *event)
{
    QTableView::mouseReleaseEvent(event);

    if(event->button() == Qt::RightButton){
        QModelIndex index = indexAt(event->pos());
        signRightClicked(event->globalPos(),1);
    }
}

void TableView::slotOnClicked(const QModelIndex & index)
{
    auto data = model()->data(index);
    signRightClicked(index,data.toInt());
}

TableItemModel::TableItemModel(int from, int to, QObject *parent):rowFrom(from),rowTo(to)
{

}

TableItemModel::~TableItemModel()
{

}

int TableItemModel::rowCount(const QModelIndex &parent) const
{
    return rowTo-rowFrom +1;
}

int TableItemModel::columnCount(const QModelIndex &parent) const
{
    return ColCount;
}

QVariant TableItemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case ColTest1:
            return index.row();
        case ColTest2:
            return 2;
        case ColTest3:
            return QString("&&");
//        case ColTest4:
//            return 3;
//        case ColTest5:
//            return 4;
//        case ColTest6:
//            return QString("***");
//        case ColTest7:
//            return QString("----");
        default:
            return QVariant();
        }
    }
    if(role == Qt::BackgroundRole){

    }
    return QVariant();
}

bool TableItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return 1;
}

QVariant TableItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return "";
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

Qt::ItemFlags TableItemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    switch (index.column()) {
    case ColTest1:
    case ColTest2:
    case ColTest3:
        return flags | Qt::ItemIsEditable;
//    case ColTest4:
//    case ColTest5:
//    case ColTest6:
//    case ColTest7:
//        return flags;
    default:
        return Qt::NoItemFlags;
    }
}

ItemDelegate::ItemDelegate(QTableView *parent):QItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{

}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == ColTest1){
        QLineEdit *l = new QLineEdit(parent);
        return l;
    }
    if(index.column() == ColTest2){
        QComboBox *box = new QComboBox(parent);
        for(int i = 0 ; i < 100 ; i++){
            box->addItem(QString::number(i));
        }
        return box;
    }
    if(index.column() == ColTest3){
        QLineEdit *l = new QLineEdit(parent);
        return l;
    }
    return QItemDelegate::createEditor(parent,option,index);
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column()) {
    case ColTest1:
    {
        QLineEdit * line = qobject_cast<QLineEdit*>(editor);
        if(line)
            line->setText(index.data().toString());
        break;
    }

    case ColTest2:
    {
        QComboBox * line = qobject_cast<QComboBox*>(editor);
        if(line)
            line->setCurrentText(index.data().toString());
        break;
    }
    case ColTest3:
    {
        QLineEdit * line = qobject_cast<QLineEdit*>(editor);
        if(line)
            line->setText(index.data().toString());
        break;
    }
    default:
        break;
    }
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

ReadOnlyItemDelegate::ReadOnlyItemDelegate(QTableView *parent): QItemDelegate(parent)
{

}

ReadOnlyItemDelegate::~ReadOnlyItemDelegate()
{

}

QWidget *ReadOnlyItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);
    return nullptr;
}
