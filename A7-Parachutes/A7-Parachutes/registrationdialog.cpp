#include "registrationdialog.h"
#include "ui_registrationDialog.h"

RegistrationDialog::RegistrationDialog(Networking * client_, QWidget *parent)
    : client(client_), QDialog(parent), ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);

    connect(ui->studentRadioButton, &QRadioButton::toggled, this, &RegistrationDialog::enableTeacherName);
    connect(ui->teacherRadioButton, &QRadioButton::toggled, this, &RegistrationDialog::disableTeacherName);
    connect(ui->OKButton, &QPushButton::clicked, this, &RegistrationDialog::checkInput);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RegistrationDialog::showMainwindow);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::enableTeacherName()
{
    ui->teacberNameLabel->setEnabled(true);
    ui->teachersName->setEnabled(true);
}

void RegistrationDialog::disableTeacherName()
{
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);
    ui->teachersName->setText("");
}

void RegistrationDialog::showMainwindow()
{
    this->close();
}

void RegistrationDialog::checkInput()
{
    if(ui->username->text().count() > 0
            &&ui->password->text().count() > 0
            &&ui->confirmPassword->text().count() > 0 && ui->firstName->text().count()>0&&ui->lastName->text().count()>0)
    {
        if(ui->password->text().compare(ui->confirmPassword->text(), Qt::CaseSensitive)!= 0)
        {
               ui->warningLabel->setText("Password does not match");
        }
        else if(ui->teacherRadioButton->isChecked())
        {
            client->requestNameAvailable(ui->username->text());
        }
        else if(ui->studentRadioButton->isChecked()&&ui->teachersName->text().count() > 0)
        {
            client->requestIsTeacher(ui->teachersName->text());
        }
        else
        {
            ui->warningLabel->setText("Select Student or Teacher and fill the blank.");
        }
    }
    else
    {
        ui->warningLabel->setText("Username,Realname or password cannot be empty");
    }
}

void RegistrationDialog::getNameAvailable(bool available)
{
    if(!available)
        ui->warningLabel->setText("This name is already taken");
    else
    {
        client->requestWriteNewUser(ui->username->text(),ui->firstName->text(),ui->lastName->text(), ui->password->text(),ui->teachersName->text());
        this->close();
    }
}

void RegistrationDialog::getIsTeacher(bool teacher)
{
    if(!teacher)
        ui->warningLabel->setText(ui->teachersName->text() + " is not a teacher");
    else
    {
        client->requestNameAvailable(ui->username->text());
    }
}

void RegistrationDialog::getRegisterSuccess(bool success)
{
    if(!success)
        ui->warningLabel->setText("Something happened with your registration. Please try again");
    else
    {
        //login and start game
        QMessageBox msgBox;
        msgBox.setMinimumSize(150,75);
        QString s = "Successfully created your account. Please log in.";
        msgBox.setText(s);
        msgBox.exec();
        client->requestCurrentHighScore(ui->username->text());
    }

}
