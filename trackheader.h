#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

private:
    uint trackNumber;
    QDoubleSpinBox *display;
    QPushButton *procButton;

signals:

public slots:

};

#endif // TRACKHEADER_H
