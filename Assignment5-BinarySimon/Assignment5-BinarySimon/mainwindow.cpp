#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProgressBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // I think this should always be first.
    ui->setupUi(this);

    // Disallow resizing of the window.
    ui->statusBar->setSizeGripEnabled(false);

    // syntax for default slots is on_NAMEOFTHEWIDGET_NAMEOFTHESIGNAL
    // if you want to use a generic name for the slot, you can make the connection manually like so:
//    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_start_clicked()));
//    connect(ui->pushButton_blue, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_blue_clicked()));
//    connect(ui->pushButton_red, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_red_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("open File"), "", tr("JPEG(*.jpg *.jpeg);;PNG(*.png)"));
}

void MainWindow::on_pushButton_blue_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("open File"), "", tr("JPEG(*.jpg *.jpeg);;PNG(*.png)"));
}

void MainWindow::on_pushButton_red_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("open File"), "", tr("JPEG(*.jpg *.jpeg);;PNG(*.png)"));
}
