#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

#include <QDebug>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = 0);
    ~NewFileDialog();

    QString getTitle();
    int getWidth();
    int getHeight();
    QColor getBgColor();

signals:
//    void accepted();
//    void rejected();

private:
    Ui::NewFileDialog *ui;

    void connectSignalsAndSlots();

private slots:
    void widthSpinBox_changed(int value);
    void heightSpinBox_changed(int value);
    void bgContentsComboBox_changed(int index);
    void titleLineEdit_edited(QString text);

    void customAccept();
};

#endif // NEWFILEDIALOG_H
