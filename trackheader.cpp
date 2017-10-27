#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set black background
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // set up track label
    trackLabel = new QLabel;
    trackLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    trackLabel->setContentsMargins(0,0,0,0);
    trackLabel->setFixedHeight(20);
    trackLabel->setStyleSheet("background: dark grey");

    // set up data display
    dataDisplay = new QDoubleSpinBox;
    dataDisplay->setReadOnly(true);
    dataDisplay->setButtonSymbols(QAbstractSpinBox::NoButtons);
    dataLabel = new QLabel;
    dataLabel->setText("");
    QHBoxLayout *dataLayout = new QHBoxLayout;
//    dataLayout->addWidget(dataLabel);
    dataLayout->addWidget(dataDisplay);

    // add everything to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(trackLabel);
    mainLayout->addItem(dataLayout);
//    mainLayout->addWidget(dataProcessingLabel);
    mainLayout->setSpacing(4);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // set this track header's width
    this->setFixedWidth(120);

}

void TrackHeader::setTrackNumber(uint num)
{
    QString label;
    label = "Dimension " + QString::number(num);
    trackLabel->setText(label);
}
