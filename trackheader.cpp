#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{
    QPalette* pal = new QPalette;

    // set black background
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    //set up track label
    trackLabel = new QLabel;
    trackLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    trackLabel->setContentsMargins(0,0,0,0);
    trackLabel->setMaximumHeight(20);
    trackLabel->setStyleSheet("background: dark grey");

    dataValueLabel = new QLabel;
    dataValueReadout = new QLabel;
    dataProcessingLabel = new QLabel;


    QHBoxLayout *dataLayout = new QHBoxLayout;
    dataLayout->addWidget(dataValueReadout);
    dataLayout->addWidget(dataValueLabel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(trackLabel);
    mainLayout->addItem(dataLayout);
    mainLayout->addWidget(dataProcessingLabel);
    this->setLayout(mainLayout);

    this->setFixedWidth(120);

}

void TrackHeader::setTrackNumber(uint num)
{
    QString label;
    label = "Dimension " + QString::number(num);
    trackLabel->setText(label);
}
