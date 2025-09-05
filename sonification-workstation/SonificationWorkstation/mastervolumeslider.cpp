#include "mastervolumeslider.h"

namespace sow {

MasterVolumeSlider::MasterVolumeSlider(QWidget *parent) : QSlider(parent)
{

}

void sow::MasterVolumeSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QMouseEvent* e2 = new QMouseEvent(QEvent::MouseButtonRelease,
                                          QPointF(event->position()),
                                          QPointF(event->globalPosition()),
                                          Qt::MouseButton::MiddleButton,
                                          Qt::MouseButton::MiddleButton,
                                          Qt::KeyboardModifier::NoModifier);
        QSlider::mousePressEvent(e2);
    }
}

} // End namespace sow.
