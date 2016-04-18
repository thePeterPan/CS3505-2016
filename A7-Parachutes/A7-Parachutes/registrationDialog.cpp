#include "registrationDialog.h"
#include "ui_registrationDialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);

    connect(ui->studentRadioButton, SIGNAL(toggled(bool)), this, SLOT(enableTeacherName()));
    connect(ui->teacherRadioButton, SIGNAL(toggled(bool)), this, SLOT(disableTeacherName()));
    connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(showMainwindow()));
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::enableTeacherName() {
    ui->teacberNameLabel->setEnabled(true);
    ui->teachersName->setEnabled(true);
}

void RegistrationDialog::disableTeacherName() {
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);
}

void RegistrationDialog::showMainwindow() {
    this->close();
}
