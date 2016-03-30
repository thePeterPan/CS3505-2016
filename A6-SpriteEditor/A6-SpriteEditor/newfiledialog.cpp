#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    ui->bgColor_colorLineEdit->setPreviewColor(true);
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}
