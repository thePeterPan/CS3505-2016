#include "levelselection.h"
#include "ui_levelselection.h"

levelSelection::levelSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::levelSelection)
{
    ui->setupUi(this);
}

levelSelection::~levelSelection()
{
    delete ui;
}
