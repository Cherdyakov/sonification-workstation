#include "session.h"

namespace sow {

Session::Session(QObject *root, QObject *parent) : QObject(parent)
{
    qmlRoot_ = root;
    sessionfile_ = QString();
    datafile_ = QString();
}

void Session::write()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(qmlRoot_, "readTree",
                              Q_RETURN_ARG(QVariant, returnedValue));

    QJsonDocument jsonDocument = QJsonDocument::fromJson(returnedValue.toString().toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    jsonObject.insert("dataset", datafile_);
    jsonObject.insert("interpolate", interpolate_);
    jsonObject.insert("speed", speed_);

    QJsonDocument sessionDocument;
    sessionDocument.setObject(jsonObject);

    QFile file(sessionfile_);
    file.open(QFile::WriteOnly);
    file.write(sessionDocument.toJson());
}

void Session::on_save()
{
    if(sessionfile_ == NULL) {
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
    sessionfile_ = QFileDialog::getSaveFileName((QWidget*)this->parent(), tr(("Save Session")), documents, ("JSON(*.json)"));
    if(!sessionfile_.isEmpty()) {
        if(!sessionfile_.endsWith(".json")) {
            sessionfile_ += ".json";
        }
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
        datafile_ = value.toString();
        emit newDatafile(datafile_, &dataset_);

        // set playback speed
        speed_ = jsonObject.value("speed").toInt();
        emit speedChanged(speed_);

        // set interpolation state
        interpolate_ = jsonObject.value("interpolate").toBool();
        emit interpolateChanged(interpolate_);

        // get the synthItems and send it to QML as
        // a string, to reconstruct it
        value = jsonObject.value("synthItems");
        QVariant synthItems = value.toVariant();
        QMetaObject::invokeMethod(qmlRoot_, "createTree",
                                  Q_ARG(QVariant, synthItems));
    }

}

void Session::on_importDatasetFile()
{
    QStringList docDirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documents = docDirs[0];
    datafile_ = QFileDialog::getOpenFileName((QWidget*)this->parent(), tr("Import Dataset"), documents, ("csv File(*.csv)"));

    if(!datafile_.isEmpty())
    {
        emit newDatafile(datafile_, &dataset_);
    }
}

void Session::onInterpolateChanged(bool interpolate)
{
    this->interpolate_ = interpolate;
}

void Session::on_speedChanged(int speed)
{
    this->speed_ = speed;
}

} // End namespace sow.
