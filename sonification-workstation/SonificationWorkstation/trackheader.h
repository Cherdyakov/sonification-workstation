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
#include "enums.h"

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

private:

    uint trackNumber_;
    QComboBox *procComboBox_;
    QSpinBox *alphaSpinBox_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:
    void processingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type);
    void nValChanged(uint track, uint n);
    void alphaChanged(uint track, float alpha);

public slots:

private slots:
    void onProcessingTypeChanged(int idx);
    void onNvalChanged(int n);
    void onAlphaChanged(float alpha);

};

#endif // TRACKHEADER_H
