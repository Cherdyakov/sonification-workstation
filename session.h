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

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* root, QObject *parent = nullptr);

private:
    void write();

    QObject* qmlRoot;
    std::vector<double> dataset;
    QString sessionFile;
    QString datasetFile;
    bool interpolate;
    int speed;

signals:
    void newDatasetFile(QString datasetFile, std::vector<double>* dataset);
    void interpolateChanged(bool interpolate);
    void speedChanged(int speed);

public slots:
    void on_save();
    void on_saveAs();
    void on_open();
    void on_importDatasetFile();
    void on_interpolateChanged(bool interpolate);
    void on_speedChanged(int speed);
};

#endif // SESSION_H
