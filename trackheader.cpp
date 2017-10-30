#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set black background
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // set up track label
    trackName = new TrackName;

    // set up data display
    dataDisplay = new QDoubleSpinBox;
    dataDisplay->setReadOnly(true);
    dataDisplay->setButtonSymbols(QAbstractSpinBox::NoButtons);
    dataLabel = new QLabel;
    dataLabel->setText("");
    QHBoxLayout *dataLayout = new QHBoxLayout;
    dataLayout->addWidget(dataDisplay);

    // set up processing display
    dataProcessingLabel = new QLabel;
    dataProcessingLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    dataProcessingLabel->setContentsMargins(0,0,0,0);
    dataProcessingLabel->setFixedHeight(20);
    dataProcessingLabel->setStyleSheet("background: dark grey");
    dataProcessingLabel->setText("Pre-processing");

    // add everything to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(trackName);
    mainLayout->addItem(dataLayout);
    mainLayout->addWidget(dataProcessingLabel);
    mainLayout->setSpacing(4);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // set this track header's width
    this->setFixedWidth(120);

}

void TrackHeader::setTrackNumber(uint num)
{
    trackName->setTrackNumber(num);
}
