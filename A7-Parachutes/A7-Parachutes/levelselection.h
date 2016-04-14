#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H

#include <QDialog>

namespace Ui {
class levelSelection;
}

class levelSelection : public QDialog
{
    Q_OBJECT

public:
    explicit levelSelection(QWidget *parent = 0);
    ~levelSelection();

private:
    Ui::levelSelection *ui;
};

#endif // LEVELSELECTION_H
