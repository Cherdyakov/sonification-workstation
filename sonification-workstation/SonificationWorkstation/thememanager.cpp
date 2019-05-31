#include "thememanager.h"
#include <QFile>
#include <QApplication>
#include <QDebug>

namespace sow {

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{
    themeMap_["textColor"] = "#FFFFFF";
}

void ThemeManager::setThemeMap(const QVariantMap &map)
{

}

QVariantMap ThemeManager::themeMap()
{
    return themeMap_;
}



void ThemeManager::loadTheme(QString path)
{
    // Read the stylesheet from disk
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString fileText = QLatin1String(file.readAll());
    // Split into the QML section and the genuine Qt Stylesheet
    QStringList styles = fileText.split("SynthItemColors");
    // Set all bound QML properties
    setBoundProperties(styles[1]);
    // Apply the StyleSheet
    qApp->setStyleSheet(styles[0]);
}

void ThemeManager::setBoundProperties(QString style)
{
    int top;
    int tail;

    QStringList keys = {
        "OSC",
        "amColor",
        "fmColor",
        "audColor",
        "panColor",
        "envColor",
        "volColor",
        "nseColor",
        "eqColor",
        "outColor",
        "textColor",
    };

    style.remove(" ");
    QString key = "OSC";
    QString searchString = key + ":";
    top = style.indexOf(searchString) + searchString.length();
    tail = style.indexOf(";", top);
    QStringRef value(&style, top, tail - top);
    themeMap_.insert(key, value.toString());
    qDebug() << "OSC COLOR: " << themeMap_.value(key);
}

} // End namespace sow.
