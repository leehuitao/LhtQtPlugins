#include "add_line_dialog.h"
#include "ui_add_line_dialog.h"

AddLineDialog::AddLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog)
{
    ui->setupUi(this);
}

AddLineDialog::~AddLineDialog()
{
    delete ui;
}

int AddLineDialog::getDidtance()
{
    return ui->lineEdit->text().toInt();
}

int AddLineDialog::getSize()
{
    return ui->lineEdit_2->text().toInt();
}
