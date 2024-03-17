#ifndef SINGLE_CELL_HEADER_H
#define SINGLE_CELL_HEADER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
namespace Ui {
class SingleCellHeader;
}
class FilterDialog;
class SingleCellHeader : public QWidget
{
    Q_OBJECT

public:
    explicit SingleCellHeader(int index,QWidget *parent = nullptr);
    ~SingleCellHeader();

    void setTitle(QString text);

    void setAlignment(Qt::Alignment align);

    void clearSortStatus();

    void clearFilterStatus();

    QString getFilterName();

    bool eventFilter(QObject * obj,QEvent *event);
signals:
    void sortUp(int index);

    void sortDown(int index);

    void filter(int index, QString msg);

    void signHideAllStatus();

private slots:
    void on_filter_btn_clicked();

    void on_sortup_btn_clicked();

    void on_sortdown_btn_clicked();

private:
    Ui::SingleCellHeader *ui;

    int             m_index = 0;

    FilterDialog *  m_filterDialog = nullptr;

    bool            m_show = false;
};
class FilterDialog : public QWidget
{
  Q_OBJECT
public:
    FilterDialog(QWidget *parent = nullptr);

    QString filterMsg(){
        return m_lineEdit->text().trimmed();
    }
signals:
    void filter(QString msg);

private:
    QPushButton * m_btn;
    QLineEdit   * m_lineEdit;
};
#endif // SINGLE_CELL_HEADER_H
