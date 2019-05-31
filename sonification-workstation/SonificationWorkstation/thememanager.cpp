#include "thememanager.h"
#include <QFile>
#include <QApplication>

namespace sow {

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{
    themeMap_["textColor"] = "#FFFFFF";
}

void ThemeManager::setThemeMap(const QVariantMap &themeMap)
{
    if(themeMap_ != themeMap) {
        themeMap_ = themeMap;
        emit themeMapChanged();
    }
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
    // Set bound QML properties
    setQmlTheme(styles[1]);
    // Apply the StyleSheet to Qt Widgets
    qApp->setStyleSheet(styles[0]);
}

void ThemeManager::setQmlTheme(QString style)
{
    QStringList keys = {
        "OSC",
        "AM",
        "FM",
        "AUD",
        "PAN",
        "ENV",
        "VOL",
        "NSE",
        "EQ",
        "OUT",
        "textColor",
        "backgroundColor"
    };

    style.remove(" ");

    int top;
    int tail;

    foreach (const QString &key, keys) {
        QString searchString = key + ":";
        top = style.indexOf(searchString) + searchString.length();
        tail = style.indexOf(";", top);
        QStringRef value(&style, top, tail - top);
        themeMap_.insert(key, value.toString());
    }

    emit themeMapChanged();
}

} // End namespace sow.
