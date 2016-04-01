#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    // Initialize UI Elements
    ui->bgColor_colorLineEdit->setPreviewColor(true);
    ui->bgColor_colorLineEdit->hide();
    ui->bgColor_label->hide();

    connectSignalsAndSlots();
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}


void NewFileDialog::connectSignalsAndSlots()
{
    connect(ui->width_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &NewFileDialog::widthSpinBox_changed);
    connect(ui->height_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &NewFileDialog::heightSpinBox_changed);
    connect(ui->bgContents_comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &NewFileDialog::bgContentsComboBox_changed);
    connect(ui->title_lineEdit, &QLineEdit::textEdited, this, &NewFileDialog::titleLineEdit_edited);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NewFileDialog::customAccept);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/**
 * Normally this is automatically connected to the accept slot, but here we are
 * intercepting it so that we can validate the data before the dialog box is
 * actually accepted.
 *
 * @brief NewFileDialog::customAccept
 */
void NewFileDialog::customAccept()
{

    if (ui->title_lineEdit->text() == "" ||
            ui->width_spinBox->value() < 2 ||
            ui->height_spinBox->value() < 2)
    {
        return;
    }
    accept();
}

//void NewFileDialog::accepted()
//{
//    qDebug() << "Accepted";
//}

//void NewFileDialog::rejected()
//{
//    qDebug() << "Rejected";
//}

void NewFileDialog::widthSpinBox_changed(int value)
{
    ui->height_spinBox->setValue(value);
}

void NewFileDialog::heightSpinBox_changed(int value)
{
    ui->width_spinBox->setValue(value);
}

void NewFileDialog::bgContentsComboBox_changed(int index)
{
    if (index == 0)
    {
        ui->bgColor_colorLineEdit->setEnabled(false);
        ui->bgColor_colorLineEdit->hide();
        ui->bgColor_label->hide();
    } else if (index == 1) {
        ui->bgColor_colorLineEdit->setEnabled(true);
        ui->bgColor_colorLineEdit->show();
        ui->bgColor_label->show();
    }
}

void NewFileDialog::titleLineEdit_edited(QString text)
{
    if (text == "")
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

QString NewFileDialog::getTitle()
{
    return ui->title_lineEdit->text();
}

int NewFileDialog::getWidth()
{
    return ui->width_spinBox->value();
}

int NewFileDialog::getHeight()
{
    return ui->height_spinBox->value();
}

QColor NewFileDialog::getBgColor()
{
    return ui->bgColor_colorLineEdit->color();
}
