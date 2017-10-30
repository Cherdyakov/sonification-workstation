#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *dataLayout = new QHBoxLayout;
    display = new DataDisplay;
    processing = new DataProcessing;
    QPalette* pal = new QPalette;

    // set black background
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // add everything to main layout
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(display);
    mainLayout->addWidget(processing);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // set this track header's width
    this->setFixedWidth(120);

}
