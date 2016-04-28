#include "leveldialog.h"
#include "ui_leveldialog.h"

<<<<<<< HEAD
LevelSelectionDialog::LevelSelectionDialog(Networking *client, QWidget *parent) : client(client),
=======

LevelSelectionDialog::LevelSelectionDialog(QWidget *parent) :
>>>>>>> refs/remotes/origin/neverland-dev
    QDialog(parent), ui(new Ui::LevelSelectionDialog)
{
    ui->setupUi(this);

    connect(ui->level1Button, &QPushButton::clicked, this, &LevelSelectionDialog::showGameWindow);
    connect(ui->wordsButton, &QPushButton::clicked, this, &LevelSelectionDialog::openFile);

}

LevelSelectionDialog::~LevelSelectionDialog()
{
    delete ui;
}

void LevelSelectionDialog::showGameWindow()
{
    emit showGameWindowSignal();
}

void LevelSelectionDialog::openFile() {


    QString file = QFileDialog::getOpenFileName(this,tr("Open File"),"$$PWD/../../","TEXT(*.txt)");

    QFile ifile(file);

    ifile.open(QIODevice::ReadOnly | QIODevice::Text);

     // read whole content
     QString content = ifile.readAll();

     // extract words
     QStringList list = content.split("\n",QString::SkipEmptyParts);

     foreach(QString s, list){

        qDebug()<<s;
     }

     emit addWordsFromFile(list);

     ifile.close();

}
