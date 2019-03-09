#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QVariant>
#include <vector>

#include "transportwidget.h"

namespace sow {

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* root, QObject *parent = nullptr);

private:
    void write();

    QObject* qmlRoot_;
    Dataset dataset_;
    QString sessionfile_;
    QString datafile_;
    bool interpolate_;
    int speed_;

signals:
    void newDatafile(QString datafile, sow::Dataset* dataset);
    void interpolateChanged(bool interpolate);
    void speedChanged(int speed);

public slots:
    void on_save();
    void on_saveAs();
    void on_open();
    void on_importDatasetFile();
    void on_interpolateChanged(bool interpolate_);
    void on_speedChanged(int speed_);
};

} // End namespace sow.

#endif // SESSION_H
