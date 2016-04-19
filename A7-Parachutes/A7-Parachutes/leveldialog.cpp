#include "leveldialog.h"
#include "ui_leveldialog.h"

levelDialog::levelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::levelDialog)
{
    ui->setupUi(this);

    connect(ui->level1Button, SIGNAL(clicked()), this, SLOT(showGameWindow()));
}

levelDialog::~levelDialog()
{
    delete ui;
}

void levelDialog::showGameWindow() {
    this->close();
    game.show();
}
