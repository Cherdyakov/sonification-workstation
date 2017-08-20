#include "session.h"

Session::Session(QObject *tree, QObject *parent) : QObject(parent)
{
    synthTree = tree;
    sessionFile = QString();
    datasetFile = QString();
}

void Session::write()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(synthTree, "readTree",
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
    write();
}

void Session::on_open()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    QString filename = QFileDialog::getOpenFileName((QWidget*)this->parent(), tr(("Open Session")), documents, ("JSON(*.json)"));
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QString input = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(input.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    datasetFile = jsonObject.value("dataset").toString();
    emit newDatasetFile(datasetFile, &dataset);
}

void Session::on_importDatasetFile()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    datasetFile = QFileDialog::getOpenFileName((QWidget*)this->parent(), tr("Import Dataset"), documents, ("csv File(*.csv)"));

    if(datasetFile.isEmpty())
    {
        return;
    }
    emit newDatasetFile(datasetFile, &dataset);
}


