#include "leveldialog.h"
#include "ui_leveldialog.h"

LevelSelectionDialog::LevelSelectionDialog(Networking *client, QWidget *parent) : client(client),
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
