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

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* tree, QObject *parent = nullptr);

private:
    void write();

    QObject* synthTree;
    std::vector<double> dataset;
    QString sessionFile;
    QString datasetFile;
    QJsonDocument treeDocument;
    QJsonDocument sessionDocument;

signals:
    void newDatasetFile(QString datasetFile, std::vector<double>* dataset);

public slots:
    void on_save();
    void on_saveAs();
    void on_open();
    void on_importDatasetFile();
};

#endif // SESSION_H
