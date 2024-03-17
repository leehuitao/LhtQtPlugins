#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QTableView>
#include <QItemDelegate>
#include "table_header.h"
#include <QSortFilterProxyModel>

class TableView;
class TableItemModel;

class Table : public QWidget
{
    Q_OBJECT
public:
    Table(QWidget * parent = nullptr);
    virtual ~Table();

    void init();

    void updateTable();

private slots :
    void onFilter(int index, QString msg);
    void slotRightClicked(const QModelIndex& model,unsigned);
    void slotRightClicked(QPoint, bool);
private:
    TableHeader *       m_tableHeader;
    TableView   *       m_tableView;
    TableItemModel *    m_tableItemModel;
    QSortFilterProxyModel * m_proxy;
    QModelIndex         m_index;
    int                 m_currentIndex ;
};


class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget * parent = nullptr);
    virtual ~TableView();
    void setIsAction(bool is){isAction = is;}
protected slots:
    virtual void mouseReleaseEvent(QMouseEvent * event);
    void slotOnClicked(const QModelIndex &);
signals:
    void signRightClicked(const QModelIndex& model,unsigned);
    void signRightClicked(QPoint, bool);
private:
    bool isAction;
};


class TableItemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableItemModel(int ,int, QObject * parent = nullptr);
    virtual ~TableItemModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index,int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index,const QVariant & value, int role = Qt::EditRole) override;
    QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;
private:
    unsigned rowFrom;
    unsigned rowTo;
};

class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ItemDelegate(QTableView * parent = nullptr);
    virtual ~ItemDelegate();

protected:
    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

class ReadOnlyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyItemDelegate(QTableView * parent = nullptr);
    virtual ~ReadOnlyItemDelegate();
protected:
    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
#endif // TABLE_H
