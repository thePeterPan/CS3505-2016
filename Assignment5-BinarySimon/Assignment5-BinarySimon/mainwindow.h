#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:


private:
    Ui::MainWindow *ui;

    QPushButton *pushButton_start;
    QPushButton *pushButton_red;
    QPushButton *pushButton_blue;

    QProgressBar *progressBar;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_blue_clicked();
    void on_pushButton_red_clicked();

};

#endif // MAINWINDOW_H
