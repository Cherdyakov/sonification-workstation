#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);
    void setTrackNumber(uint num);

private:
    uint trackNumber;
    QLabel *trackLabel;
    QDoubleSpinBox *dataDisplay;
    QLabel *dataLabel;
    QLabel *dataProcessingLabel;


signals:

public slots:

};

#endif // TRACKHEADER_H
