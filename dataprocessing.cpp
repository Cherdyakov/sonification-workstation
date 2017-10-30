#include "dataprocessing.h"

DataProcessing::DataProcessing(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel;
    QPushButton *button = new QPushButton;
    QVBoxLayout *layout = new QVBoxLayout;

    label->setText("Data Processing:");
    button->setText("None");

    layout->addWidget(label);
    layout->addWidget(button);
    layout->addStretch();

    this->setLayout(layout);

}
