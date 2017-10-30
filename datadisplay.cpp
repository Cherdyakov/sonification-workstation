#include "datadisplay.h"

DataDisplay::DataDisplay(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    spinBox = new QDoubleSpinBox;
//    label = new QLabel;
    // set up data display
    spinBox->setReadOnly(true);
    spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
//    label->setText("");
//    layout->addWidget(label);
    layout->addWidget(spinBox);
    this->setLayout(layout);
}
