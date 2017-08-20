#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QVariant>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* tree, QObject *parent = nullptr);

private:
    void write();
    void saveAs();

    QObject* synthTree;
    QString filename;
    QString dataset;
    QJsonDocument treeDocument;
    QJsonDocument sessionDocument;

signals:
    void SessionOpened(QJsonDocument treeDocument);

public slots:
    void save();
    void open();
};

#endif // SESSION_H
