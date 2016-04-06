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

    // Accessor methods:
    QString getTitle();
    int getWidth();
    int getHeight();
    QColor getBgColor();
    bool hasBgColor();

signals:

private:
    Ui::NewFileDialog *ui;
    bool bgColorExists;

    void connectSignalsAndSlots();

private slots:
    void bgContentsComboBox_changed(int index);
    void titleLineEdit_edited(QString text);

    void customAccept();
};

#endif // NEWFILEDIALOG_H
