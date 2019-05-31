#include "thememanager.h"
#include <QFile>
#include <QApplication>
#include <QDebug>

namespace sow {

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{

}

void ThemeManager::setOscColor(const QString &oscColor)
{
    if(oscColor_ != oscColor) {
        oscColor_ = oscColor;
        emit oscColorChanged();
    }
}

QString ThemeManager::oscColor()
{
    return oscColor_;
}

void ThemeManager::setAmColor(const QString &amColor)
{
    if(amColor_ != amColor) {
        amColor_ = amColor;
        emit amColorChanged();
    }
}

QString ThemeManager::amColor()
{
    return amColor_;
}

void ThemeManager::setFmColor(const QString &fmColor)
{
    if(fmColor_ != fmColor) {
        fmColor_ = fmColor;
        emit fmColorChanged();
    }
}

QString ThemeManager::fmColor()
{
    return fmColor_;
}

void ThemeManager::setAudColor(const QString &audColor)
{
    if(audColor_ != audColor) {
        audColor_ = audColor;
        emit fmColorChanged();
    }
}

QString ThemeManager::audColor()
{
    return audColor_;
}

void ThemeManager::setPanColor(const QString &panColor)
{
    if(panColor_ != panColor) {
        panColor_ = panColor;
        emit panColorChanged();
    }
}

QString ThemeManager::panColor()
{
    return panColor_;
}

void ThemeManager::setEnvColor(const QString &envColor)
{
    if(envColor_ != envColor) {
        envColor_ = envColor;
        emit envColorChanged();
    }
}

QString ThemeManager::envColor()
{
    return envColor_;
}

void ThemeManager::setVolColor(const QString &volColor)
{
    if(volColor_ != volColor) {
        volColor_ = volColor;
        emit volColorChanged();
    }
}

QString ThemeManager::volColor()
{
    return volColor_;
}

void ThemeManager::setEqColor(const QString &eqColor)
{
    if(eqColor_ != eqColor) {
        eqColor_ = eqColor;
        emit eqColorChanged();
    }
}

QString ThemeManager::eqColor()
{
    return eqColor_;
}

void ThemeManager::setNseColor(const QString &nseColor)
{
    if(nseColor_ != nseColor) {
        nseColor_ = nseColor;
        emit nseColorChanged();
    }
}

QString ThemeManager::nseColor()
{
    return nseColor_;
}

void ThemeManager::setOutColor(const QString &outColor)
{
    if(outColor_ != outColor) {
        outColor_ = outColor;
        emit outColorChanged();
    }
}

QString ThemeManager::outColor()
{
    return outColor_;
}

void ThemeManager::setTextColor(const QString &textColor)
{
    if(textColor_ != textColor) {
        textColor_ = textColor;
        emit textColorChanged();
    }
}

QString ThemeManager::textColor()
{
    return textColor_;
}

void ThemeManager::loadTheme(QString path)
{
    // Read the stylesheet from disk
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString fileText = QLatin1String(file.readAll());
    // Split into the QML section and the genuine Qt Stylesheet
    QStringList styles = fileText.split("SynthItems");
    // Set all bound QML properties
    setBoundProperties(styles[1]);
    // Apply the StyleSheet
    qApp->setStyleSheet(styles[0]);
}

void ThemeManager::setBoundProperties(QString style)
{
    int top;
    int tail;

    style.remove(" ");
    QString key = "oscColor:";
    top = style.indexOf(key) + key.length();
    tail = style.indexOf(";", top);
    QStringRef oscColor(&style, top, tail - top);
    qDebug() << "OSC COLOR: " << oscColor;
}

} // End namespace sow.
