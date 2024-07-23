#ifndef EXPORTEXCEL_H
#define EXPORTEXCEL_H

#include <QObject>
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

struct TableData{
    int col;//列数
    int row;//行数
    QString title;
    QString path;//存储路径
    QMap<int, int>  colWidth;
    QMap<int,QString>   colName;
    QMap<int,QMap<int,QString>>    data;
};

class ExportExcel : public QThread
{
    Q_OBJECT
public:
    explicit ExportExcel(QObject *parent = nullptr);

    void Table2ExcelByHtml(QTableView *table, QString title);
    ~ExportExcel();
signals:
    void signExcelExportState(int);
public slots:


    void init();
private:

    void table2ExcelByHtml(TableData);
private:
    QAxObject *excel = nullptr;
    QAxObject *workbooks;
    QAxObject *workbook ;
    QAxObject *worksheet;
    bool        m_initState=0;
    QMutex          m_dataMutex;
    QWaitCondition  m_waitCondition;
    QVector<TableData>  m_taskList;
    bool m_stoped;
    // QThread interface
protected:
    void run();
};

#endif // EXPORTEXCEL_H
