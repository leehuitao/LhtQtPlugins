#include "single_cell_header.h"
#include "ui_single_cell_header.h"

SingleCellHeader::SingleCellHeader(int index,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleCellHeader),m_index(index),m_filterDialog(new FilterDialog)
{
    ui->setupUi(this);
    this->setObjectName("SingleHeaderView");
    m_filterDialog->hide();
    //过滤信号
    connect(m_filterDialog,&FilterDialog::filter,[=](QString msg){
        ui->filter_btn->show();
        if(!msg.isEmpty()){
            m_show = 1;
        }else{
            m_show = 0;
            ui->filter_btn->setChecked(false);
        }
        this->filter(m_index,msg);
    });
    ui->widget->installEventFilter(this);
    ui->title_label->installEventFilter(this);
    ui->sortup_btn->installEventFilter(this);
    ui->sortdown_btn->installEventFilter(this);
    ui->filter_btn->installEventFilter(this);
}

SingleCellHeader::~SingleCellHeader()
{
    delete ui;
    if(m_filterDialog != nullptr){
        delete  m_filterDialog;
        m_filterDialog = nullptr;
    }
}

void SingleCellHeader::setTitle(QString text)
{
    ui->title_label->setText(text);
}

void SingleCellHeader::setAlignment(Qt::Alignment align)
{
    ui->title_label->setAlignment(align);
}

void SingleCellHeader::clearSortStatus()
{
    ui->sortup_btn->setChecked(false);
    ui->sortdown_btn->setChecked(false);
}

void SingleCellHeader::clearFilterStatus()
{
    ui->filter_btn->setChecked(false);
}

QString SingleCellHeader::getFilterName()
{
    return m_filterDialog->filterMsg();
}

bool SingleCellHeader::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->filter_btn || obj == ui->title_label || obj == ui->sortup_btn
            ||obj == ui->sortdown_btn||obj == ui->filter_btn||obj == ui->widget)
    {
        setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(obj,event);
}

void SingleCellHeader::on_filter_btn_clicked()
{
    ui->sortup_btn->setChecked(0);
    ui->sortdown_btn->setChecked(0);
    ui->filter_btn->setChecked(1);
    auto zero = this->mapToGlobal(QPoint(ui->title_label->pos().x(),ui->title_label->pos().y()));
    m_filterDialog->move(zero.x(),zero.y());
    m_filterDialog->resize(size() + QSize(5,0));
    m_filterDialog->show();
}

void SingleCellHeader::on_sortup_btn_clicked()
{
    ui->sortup_btn->setChecked(1);
    ui->sortdown_btn->setChecked(0);
    ui->filter_btn->setChecked(0);
    this->sortUp(m_index);
}

void SingleCellHeader::on_sortdown_btn_clicked()
{
    ui->sortup_btn->setChecked(0);
    ui->sortdown_btn->setChecked(1);
    ui->filter_btn->setChecked(0);
    this->sortDown(m_index);
}

FilterDialog::FilterDialog(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    auto layout = new QHBoxLayout;
    m_lineEdit = new QLineEdit;
    m_btn = new QPushButton;
    m_btn->setText("确定");
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_btn);
    m_lineEdit->setFixedWidth(50);
    m_btn->setFixedWidth(30);
    setLayout(layout);
    setWindowModality(Qt::ApplicationModal);
    connect(m_btn,&QPushButton::clicked , [=] {
        filter(filterMsg());
        close();
    });
}
