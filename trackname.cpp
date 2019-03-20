#include "trackname.h"

namespace sow {

TrackName::TrackName(QWidget *parent) : QWidget(parent)
{
    // set label properties
    label_ = new QLabel;
    label_->setContentsMargins(2,2,2,2);
    label_->setFixedHeight(20);
    label_->setStyleSheet("font: 16pt");

    // set dark background for this widget
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Background, QColor("gray"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // create layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label_);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
}

void TrackName::setNumber(unsigned int num)
{
    std::string alpha = utility::intToAlpha(num);
    QString name = QString::fromStdString(alpha);
    label_->setText(name);
}

void TrackName::setText(const QString name)
{
    label_->setText(name);
}

QString TrackName::text() const
{
    return text_;
}

} // namespace sow
