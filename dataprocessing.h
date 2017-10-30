#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWindow>

class DataProcessing : public QWidget
{
    Q_OBJECT
public:
    explicit DataProcessing(QWidget *parent = nullptr);

private:
    QPushButton *button;

signals:

public slots:
};

#endif // DATAPROCESSING_H
