#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include <QObject>
#include <QHeaderView>
#include <QPainter>
#include "single_cell_header.h"
enum ColIndex{
    ColTest1,
    ColTest2,
    ColTest3,
//    ColTest4,
//    ColTest5,
//    ColTest6,
//    ColTest7,
    ColCount
};

class TableHeader : public QHeaderView
{
    Q_OBJECT
public:
    TableHeader(QWidget * parent = nullptr);
    virtual ~TableHeader() override;

signals:
    void sortUp(int index);
    void sortDown(int index);
    void filter(int index , QString msg);
    void colWidthChange(int index , unsigned wid);
protected:
    void paintSection(QPainter * painter,const QRect & rect,int logicIndex) const override;
    void resizeEvent(QResizeEvent * event) override;
    void handleSectionMoved(int logical,int oldVisualIndex,int newVisualIndex);
    void handleSectionResized(int i , int oldSizem, int newSize);
    void setModel(QAbstractItemModel * model) override;
    void headerDataChanged(Qt::Orientation orientation , int logicalFrist,int logicalLast);
    void fixSectionPosstions();
private:
    QMap<int,SingleCellHeader*> m_tableFilterList;
    QList<int>              m_hideList;
};

#endif // TABLEHEADER_H
