#include "newfiledialog.h"
#include "ui_newfiledialog.h"

/**
 * @brief NewFileDialog::NewFileDialog Creates a new File Dialog object
 * @param parent Pointer to parent object
 */
NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    // Initialize UI Elements
    ui->bgColor_colorLineEdit->setPreviewColor(true);
    ui->bgColor_colorLineEdit->hide();
    ui->bgColor_label->hide();

    bgColorExists = false;

    connectSignalsAndSlots();
}

/**
 * @brief NewFileDialog::~NewFileDialog
 * Destructor
 */
NewFileDialog::~NewFileDialog()
{
    delete ui;
}

/**
 * @brief NewFileDialog::connectSignalsAndSlots
 */
void NewFileDialog::connectSignalsAndSlots()
{
    connect(ui->bgContents_comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &NewFileDialog::bgContentsComboBox_changed);
    connect(ui->title_lineEdit, &QLineEdit::textEdited, this, &NewFileDialog::titleLineEdit_edited);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NewFileDialog::customAccept);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/**
 * @brief NewFileDialog::customAccept
 * Normally this is automatically connected to the accept slot, but here we are
 * intercepting it so that we can validate the data before the dialog box is
 * actually accepted.
 */
void NewFileDialog::customAccept()
{

    if (ui->title_lineEdit->text() == "" ||
            ui->width_spinBox->value() < 2 ||
            ui->height_spinBox->value() < 2)
    {
        return;
    }
    accept();
}

/**
 * @brief NewFileDialog::bgContentsComboBox_changed
 * Sets the background color of the canvas.
 * @param index:
 *      0: Transparent background
 *      1: Color selector dialog appears
 */
void NewFileDialog::bgContentsComboBox_changed(int index)
{
    if (index == 0)
    {
        bgColorExists = false;
        ui->bgColor_colorLineEdit->setEnabled(false);
        ui->bgColor_colorLineEdit->hide();
        ui->bgColor_label->hide();
    }
    else if (index == 1)
    {
        bgColorExists = true;
        ui->bgColor_colorLineEdit->setEnabled(true);
        ui->bgColor_colorLineEdit->show();
        ui->bgColor_label->show();
    }
}

/**
 * @brief NewFileDialog::titleLineEdit_edited
 * Controls the sprite name. If no name is entered, a new canvas cannot be created.
 * @param text
 */
void NewFileDialog::titleLineEdit_edited(QString text)
{
    if (text == "")
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

/**
 * @brief NewFileDialog::hasBgColor Method to check if the user specified a background color.
 * @return true if a background color exists, otherwise false
 */
bool NewFileDialog::hasBgColor()
{
    return bgColorExists;
}

/**
 * @brief NewFileDialog::getTitle
 * @return the title of the sprite specified by the user
 */
QString NewFileDialog::getTitle()
{
    return ui->title_lineEdit->text();
}

/**
 * @brief NewFileDialog::getWidth
 * Gets the width specified in the spinbox.
 * @return
 */
int NewFileDialog::getWidth()
{
    return ui->width_spinBox->value();
}

/**
 * @brief NewFileDialog::getHeight
 * Gets the height specified in the spinbox.
 * @return
 */
int NewFileDialog::getHeight()
{
    return ui->height_spinBox->value();
}

/**
 * @brief NewFileDialog::getBgColor
 * Gets the background color selected by the user.
 * @return
 */
QColor NewFileDialog::getBgColor()
{
    return ui->bgColor_colorLineEdit->color();
}
