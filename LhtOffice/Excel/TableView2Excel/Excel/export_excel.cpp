#include "export_excel.h"
#include <QDebug>
#include "qt_windows.h"
ExportExcel::ExportExcel(QObject *parent) : QThread(parent)
{

}

//第一个参数是页面上的表格，第二个是导出文件的表头数据
void ExportExcel::Table2ExcelByHtml(QTableView*table,QString title)
{

    QString fileName = QFileDialog::getSaveFileName(table, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                                    ,QString::fromLocal8Bit("Excel 文件(*.xls *.xlsx)"));
    if (fileName!="")
    {
        QMutexLocker lock(&m_dataMutex);
        TableData data;
        data.title = title;
        data.path = fileName;
        //QTableView 获取列数
        data.col=table->model()->columnCount();
        //QTableView 获取行数
        data.row=table->model()->rowCount();

        for(int i=0;i<data.col;i++)
        {
            data.colWidth[i] = table->columnWidth(i);
            data.colName[i] = table->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
        }

        //QTableView 获取表格数据部分
        for(int i=0;i<data.row;i++) //行数
        {
            QMap<int,QString> colData;
            for (int j=0;j<data.col;j++)   //列数
            {
                QModelIndex index = table->model()->index(i, j);
                colData[j] = table->model()->data(index).toString();

            }
            data.data[i]= colData;
        }
        m_taskList.append(data);
        m_waitCondition.wakeOne();
    }
}

ExportExcel::~ExportExcel()
{
    m_stoped = true;
    m_waitCondition.wakeOne();
    quit();
    wait();
    m_stoped = true;
}

void ExportExcel::init()
{

    if(excel){
        delete excel;
        excel = nullptr;
    }
    excel = new QAxObject;
    if (excel->setControl("Excel.Application")) //连接Excel控件
    {
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Add");//新建一个工作簿
        workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        worksheet = workbook->querySubObject("Worksheets(int)", 1);
        m_initState = 1;

    }
    else
    {
        qDebug()<<QString::fromLocal8Bit("未能创建 Excel 对象，请安装 Microsoft Excel。");
    }
}

void ExportExcel::table2ExcelByHtml(TableData data)
{
    init();
    int i,j;
    //QTableView 获取列数
    int colcount=data.col;
    //QTableView 获取行数
    int rowcount=data.row;

    QAxObject *cell,*col;
    //标题行
    cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
    cell->dynamicCall("SetValue(const QString&)", data.title);
    cell->querySubObject("Font")->setProperty("Size", 18);
    //调整行高
    worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
    //合并标题行
    QString cellTitle;
    cellTitle.append("A1:");
    cellTitle.append(QChar(colcount - 1 + 'A'));
    cellTitle.append(QString::number(1));
    QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
    range->setProperty("WrapText", true);
    range->setProperty("MergeCells", true);
    range->setProperty("HorizontalAlignment", -4108);//xlCenter
    range->setProperty("VerticalAlignment", -4108);//xlCenter
    //列标题
    for(i=0;i<colcount;i++)
    {
        QString columnName;
        columnName.append(QChar(i  + 'A'));
        columnName.append(":");
        columnName.append(QChar(i + 'A'));
        col = worksheet->querySubObject("Columns(const QString&)", columnName);
        col->setProperty("ColumnWidth", data.colWidth[i]/6);
        cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
        //QTableView 获取表格头部文字信息
        columnName=data.colName[i];
        cell->dynamicCall("SetValue(const QString&)", columnName);
        cell->querySubObject("Font")->setProperty("Bold", true);
        cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
        cell->setProperty("HorizontalAlignment", -4108);//xlCenter
        cell->setProperty("VerticalAlignment", -4108);//xlCenter
    }

    //数据区


    //QTableView 获取表格数据部分
    for(i=0;i<rowcount;i++) //行数
    {
        for (j=0;j<colcount;j++)   //列数
        {
            QString strdata=data.data[i][j];
            worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", strdata);
        }
    }


    //画框线
    QString lrange;
    lrange.append("A2:");
    lrange.append(colcount - 1 + 'A');
    lrange.append(QString::number(data.row + 2));
    range = worksheet->querySubObject("Range(const QString&)", lrange);
    range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
    range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
    //调整数据区行高
    QString rowsName;
    rowsName.append("2:");
    rowsName.append(QString::number(data.row + 2));
    range = worksheet->querySubObject("Range(const QString&)", rowsName);
    range->setProperty("RowHeight", 20);
    workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(data.path));//保存至fileName
    workbook->dynamicCall("Close()");//关闭工作簿
    excel->dynamicCall("Quit()");//关闭excel
    delete excel;
    excel=nullptr;

//    if (QMessageBox::question(NULL,QString::fromLocal8Bit("完成"),
//                              QString::fromLocal8Bit("文件已经导出，是否现在打开？"),
//                              QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
//    {
//        QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(data.path)));
//    }
    qDebug()<<QString::fromLocal8Bit("文件已经导出");
    init();
}

void ExportExcel::run()
{
    m_stoped = false;
    HRESULT r = OleInitialize(0);
    if(r!=S_OK  && r!= S_FALSE){
        qDebug()<<" can not init ole!";
        return;
    }
    init();
    while(1){
        QMutexLocker lock(&m_dataMutex);
        if(m_taskList.isEmpty()){
            signExcelExportState(1);
            m_waitCondition.wait(&m_dataMutex);
        }
        else{
            signExcelExportState(0);
            auto data = m_taskList.takeFirst();
            lock.unlock();
            table2ExcelByHtml(data);
        }

        if(m_stoped){
            OleUninitialize();
            break;
        }
    }
}
