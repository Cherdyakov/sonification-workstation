#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class DataDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit DataDisplay(QWidget *parent = nullptr);

private:
    QLabel *label;
    QDoubleSpinBox *spinBox;

signals:

public slots:
};

#endif // DATADISPLAY_H
