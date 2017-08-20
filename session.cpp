#include "session.h"

Session::Session(QObject *tree, QObject *parent) : QObject(parent)
{
    synthTree = tree;
    filename = QString();
    dataset = QString();
}

void Session::write()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(synthTree, "readTree",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, dataset));
    QJsonDocument jsonDocument = QJsonDocument::fromJson(returnedValue.toString().toUtf8());

    QFile jsonFile(filename);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
}

void Session::save()
{
    if(filename == NULL) {
        saveAs();
    }
    else {
        write();
    }
}

void Session::saveAs()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    filename = QFileDialog::getSaveFileName((QWidget*)this->parent(), tr(("Save Session")), documents, ("JSON(*.json)"));
    write();
}

void Session::open()
{

}


