#include "leveldialog.h"
#include "ui_leveldialog.h"

levelDialog::levelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::levelDialog)
{
    ui->setupUi(this);
}

levelDialog::~levelDialog()
{
    delete ui;
}
