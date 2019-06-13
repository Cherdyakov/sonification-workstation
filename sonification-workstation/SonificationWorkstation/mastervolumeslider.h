#ifndef MASTERVOLUMESLIDER_H
#define MASTERVOLUMESLIDER_H

#include <QObject>
#include <QSlider>
#include <QMouseEvent>

namespace sow {

class MasterVolumeSlider : public QSlider
{
public:
    MasterVolumeSlider(QWidget* parent = nullptr);

protected:
  void mousePressEvent (QMouseEvent * event);

};

} // End namespace sow.

#endif // MASTERVOLUMESLIDER_H
