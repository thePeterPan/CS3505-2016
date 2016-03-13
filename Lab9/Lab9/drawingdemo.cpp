#include "drawingdemo.h"
#include "ui_drawingdemo.h"

DrawingDemo::DrawingDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingDemo)
{
    ui->setupUi(this);

    // populate the combo box
    ui->shapeComboBox->addItem("Rectangle");
    ui->shapeComboBox->addItem("Ellipse");

    // put limits on the pen width
    ui->penWidthSpinBox->setRange(0, 20);

    connect(ui->shapeComboBox, SIGNAL(activated(int)), this, SLOT(valuesChanged()));
    connect(ui->penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(valuesChanged()));
}

DrawingDemo::~DrawingDemo()
{
    delete ui;
}

// Override the default paintEvent with drawing of the shape
void DrawingDemo::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);
    QPen pen(Qt::black);
    int penWidth = ui->penWidthSpinBox->value();
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QRect rect(10, 20, 80, 60);
    int shapeNum = ui->shapeComboBox->currentIndex();
    switch (shapeNum) {
    case 0:
        painter.drawRect(rect);
        break;
    case 1:
        painter.drawEllipse(rect);
        break;
    }
}

void DrawingDemo::valuesChanged()
{
    update();
}
