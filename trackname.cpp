#include "trackname.h"

TrackName::TrackName(QWidget *parent) : QWidget(parent)
{
    // set label properties
    label = new QLabel;
    label->setContentsMargins(2,2,2,2);
    label->setFixedHeight(20);
    label->setStyleSheet("font: 16pt");

    // set dark background for this widget
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Background, QColor("gray"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // create layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
}

void TrackName::setTrackNumber(uint num)
{
    QString name = "Dimension " + QString::number(num);
    label->setText(name);
}

void TrackName::setTrackName(QString name)
{
    label->setText(name);
}
