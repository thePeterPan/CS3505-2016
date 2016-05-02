#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QEvent>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "networking.h"

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(Networking * client_, QWidget *parent = 0);
    ~RegistrationDialog();

private slots:
    void enableTeacherName();
    void disableTeacherName();
    void showMainwindow();
    void checkInput();

public slots:
    void getNameAvailable(bool available);
    void getIsTeacher(bool teacher);
    void getRegisterSuccess(bool success);

private:
    Ui::RegistrationDialog *ui;
    Networking * client;

};

#endif // REGISTRATIONDIALOG_H
