#include "session.h"

Session::Session(QObject *rootObj, QObject *parent) : QObject(parent)
{
    qmlRoot = rootObj;
    sessionFile = QString();
    datasetFile = QString();
}

void Session::write()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(qmlRoot, "readTree",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, datasetFile));
    QJsonDocument jsonDocument = QJsonDocument::fromJson(returnedValue.toString().toUtf8());

    QFile file(sessionFile);
    file.open(QFile::WriteOnly);
    file.write(jsonDocument.toJson());
}

void Session::on_save()
{
    if(sessionFile == NULL) {
        on_saveAs();
    }
    else {
        write();
    }
}

void Session::on_saveAs()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    sessionFile = QFileDialog::getSaveFileName((QWidget*)this->parent(), tr(("Save Session")), documents, ("JSON(*.json)"));
    if(!sessionFile.isEmpty()) {
        write();
    }
}

void Session::on_open()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString filename = QFileDialog::getOpenFileName((QWidget*)this->parent(), tr(("Open Session")), documents, ("JSON(*.json)"));

    if(!filename.isEmpty()) {
        QFile file(filename);
        file.open(QFile::ReadOnly);
        QString input = file.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(input.toUtf8());
        QJsonObject jsonObject = jsonDocument.object();

        // load the new dataset
        QJsonValue value = jsonObject.value("dataset");
        datasetFile = value.toString();
        emit newDatasetFile(datasetFile, &dataset);

        // get the synthItems and send it to QML as
        // a string, to reconstruct it
        value = jsonObject.value("synthItems");
        QVariant synthItems = value.toVariant();
        QMetaObject::invokeMethod(qmlRoot, "createTree",
                                  Q_ARG(QVariant, synthItems));
    }

}

void Session::on_importDatasetFile()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    datasetFile = QFileDialog::getOpenFileName((QWidget*)this->parent(), tr("Import Dataset"), documents, ("csv File(*.csv)"));

    if(!datasetFile.isEmpty())
    {
        emit newDatasetFile(datasetFile, &dataset);
    }
}


