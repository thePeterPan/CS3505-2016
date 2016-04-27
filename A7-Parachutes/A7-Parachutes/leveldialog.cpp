#include "leveldialog.h"
#include "ui_leveldialog.h"

LevelSelectionDialog::LevelSelectionDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LevelSelectionDialog)
{
    ui->setupUi(this);
    connect(ui->level1Button, &QPushButton::clicked, this, &LevelSelectionDialog::showGameWindow);
}

LevelSelectionDialog::~LevelSelectionDialog()
{
    delete ui;
}

void LevelSelectionDialog::showGameWindow()
{
    emit showGameWindowSignal();
}
