#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include "dataprocessor.h"

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

private:
    uint trackNumber;
    QDoubleSpinBox *display;
    QPushButton *procButton;
    DataProcessor *processor;

signals:

public slots:

private slots:
    void ShowProcessing();

};

#endif // TRACKHEADER_H
