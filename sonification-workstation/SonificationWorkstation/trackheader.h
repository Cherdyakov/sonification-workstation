#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include "enums.h"

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

    void setNumber(uint num);

private:

    uint trackNumber_;
    uint n_;
    bool interpolate_ = false;
    QPushButton *interpolateButton_;
    QComboBox *procComboBox_;
    QSpinBox *nuSpinBox;


protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void processingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type);
    void nValChanged(uint track, uint n);
    void onInterpolateChanged(uint track, bool interpolate);

public slots:

private slots:
    void onProcessingTypeChanged(int idx);
    void onNvalChanged(int n);
    void onInterpolateClicked();

};

#endif // TRACKHEADER_H
