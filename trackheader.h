#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "dataprocessing.h"
#include "datadisplay.h"

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

private:
    uint trackNumber;
    DataDisplay *display;
    DataProcessing *processing;

signals:

public slots:

};

#endif // TRACKHEADER_H
