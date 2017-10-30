#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *displayLayout = new QHBoxLayout;
    QVBoxLayout *processingLayout = new QVBoxLayout;
    display = new QDoubleSpinBox;
    procButton = new QPushButton;
    QPalette* pal = new QPalette;

    // set background color for header
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // data display section
    //    Qlabel *label = new QLabel;
    // set up data display
    display->setReadOnly(true);
    display->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //    label->setText("");
    //    displayLayout->addWidget(label);
    displayLayout->setContentsMargins(4,4,4,4);
    displayLayout->addWidget(display);

    // data processing section
    QLabel *procLabel = new QLabel;
    procLabel->setText("Data processing:");
    procButton->setText("None");
    processingLayout->setContentsMargins(4,4,4,4);
    processingLayout->addWidget(procLabel);
    processingLayout->addWidget(procButton);

    // add everything to main layout
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(displayLayout);
    mainLayout->addLayout(processingLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // set this track header's width
    this->setFixedWidth(120);

}
