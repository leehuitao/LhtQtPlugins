#ifndef ADD_LINE_DIALOG_H
#define ADD_LINE_DIALOG_H

#include <QDialog>

namespace Ui {
class AddLineDialog;
}

class AddLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineDialog(QWidget *parent = nullptr);
    ~AddLineDialog();

     int getDidtance();

     int getSize();
private:
    Ui::AddLineDialog *ui;
};

#endif // ADD_LINE_DIALOG_H
