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
    QString sessionfile_;
    QString datafile_;
    bool interpolate_;
    float speed_;

signals:
    void newDatafile(QString datafile);
    void interpolateChanged(bool interpolate);
    void speedChanged(int speed);

public slots:
    void onSave();
    void onSaveAs();
    void onOpen();
    void onImportDataset();
    void onInterpolateChanged(bool interpolate_);
    void onSpeedChanged(int speed_);
};

} // End namespace sow.

#endif // SESSION_H
