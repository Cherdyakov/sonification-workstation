#ifndef TRACKNAME_H
#define TRACKNAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class TrackName : public QWidget
{
    Q_OBJECT
public:
    explicit TrackName(QWidget *parent = nullptr);
    void setTrackNumber(uint num);
    void setTrackName(QString name);

private:
    QLabel *label;

signals:

public slots:
};

#endif // TRACKNAME_H
