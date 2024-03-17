#include "table_header.h"
const int HEADER_BORDER = 3;

static const QStringList HeaderString{
    QStringLiteral("测试1"),
            QStringLiteral("测试2"),
            QStringLiteral("测试3"),
            QStringLiteral("测试4"),
            QStringLiteral("测试5"),
            QStringLiteral("测试6"),
            QStringLiteral("测试7")
};
TableHeader::TableHeader(QWidget *parent):QHeaderView(Qt::Horizontal , parent)
{
    setSectionsMovable(1);
    setSectionsClickable(1);
    setStretchLastSection(1);
    setObjectName("CustomHorizontalHeaderView");
    connect(this,&QHeaderView::sectionResized,this,&TableHeader::handleSectionResized);
    connect(this,&QHeaderView::sectionMoved,this,&TableHeader::handleSectionMoved);
}

TableHeader::~TableHeader()
{
    for(auto item : m_tableFilterList){
        delete item;
        item = nullptr;
    }
}

void TableHeader::paintSection(QPainter *painter, const QRect &rect, int logicIndex) const
{
    Q_UNUSED(rect);
    painter->save();
    QHeaderView::paintSection(painter,QRect(),logicIndex);
    painter->restore();
    auto tableFiler = m_tableFilterList[logicIndex];
    tableFiler->setGeometry(sectionViewportPosition(logicIndex),0
                            ,sectionSize(logicIndex)-HEADER_BORDER,height());
    tableFiler->show();
    int m_startShowIndex = visualIndexAt(0);
    for(int i =0 ; i < m_startShowIndex ; i++){
        m_tableFilterList[i]->hide();
    }
}

void TableHeader::resizeEvent(QResizeEvent *event)
{
    QHeaderView::resizeEvent(event);
    fixSectionPosstions();
}

void TableHeader::handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex)
{
    Q_UNUSED(logical);
    Q_UNUSED(oldVisualIndex);
    Q_UNUSED(newVisualIndex);
    fixSectionPosstions();
}

void TableHeader::handleSectionResized(int i, int oldSizem, int newSize)
{
    Q_UNUSED(i);
    Q_UNUSED(oldSizem);
    Q_UNUSED(newSize);
    fixSectionPosstions();
    colWidthChange(i,newSize);
}

void TableHeader::setModel(QAbstractItemModel *model)
{
    QHeaderView::setModel(model);
    int len = count();
    int indexOfList = 0;
    for(int index = 0; index < len; index++){
        auto tableFilter = new SingleCellHeader(indexOfList,this);
        tableFilter->setTitle(HeaderString.at(index));
        tableFilter->show();
        m_tableFilterList[index] = tableFilter;

        connect(tableFilter,&SingleCellHeader::sortUp,[=] (int index_) {
            sortUp(index_);
            for(int i = 0 ; i < m_tableFilterList.size();i++){
                if(i == index_){continue;}
                m_tableFilterList[index_]->clearSortStatus();
            }
        });
        connect(tableFilter,&SingleCellHeader::sortDown,[=] (int index_) {
            sortDown(index_);
            for(int i = 0 ; i < m_tableFilterList.size();i++){
                if(i == index_){continue;}
                m_tableFilterList[index_]->clearSortStatus();
            }
        });
        connect(tableFilter,&SingleCellHeader::filter,[=] (int index_,QString msg) {
            if(m_tableFilterList[index_]->getFilterName().trimmed().isEmpty()){
                m_tableFilterList[index_]->clearFilterStatus();
            }
            filter(index_,msg);
        });
    }
}

void TableHeader::headerDataChanged(Qt::Orientation orientation, int logicalFrist, int logicalLast)
{
    if(logicalFrist < 0|| logicalLast > m_tableFilterList.size()){return;}
    if(orientation == Qt::Horizontal){
        for(int i = logicalFrist ; i < logicalLast ; i++){
            m_tableFilterList[i]->setTitle(HeaderString.at(i));
        }
    }
}

void TableHeader::fixSectionPosstions()
{
    for (int i =0; i < m_tableFilterList.size();i++) {
        m_tableFilterList[i]->setGeometry(sectionViewportPosition(i),0
                                          ,sectionSize(i)-HEADER_BORDER,height());
    }

}
