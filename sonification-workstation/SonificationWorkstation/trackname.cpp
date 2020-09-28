#include "trackname.h"

namespace sow {

TrackName::TrackName(QWidget *parent) : QWidget(parent)
{
    // set label properties
    label_ = new QLabel;
    label_->setContentsMargins(2,2,2,2);
    label_->setStyleSheet("font: 16pt");
    label_->setFocusPolicy(Qt::TabFocus);

    this->setAutoFillBackground(true);
    this->setObjectName("TrackName");

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
    label_->setAccessibleName("Track " + name);
    label_->setAccessibleDescription("");
}

void TrackName::setText(const QString name)
{
    label_->setText(name);
}

QString TrackName::text() const
{
    return text_;
}

void TrackName::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

} // namespace sow
