#include "thememanager.h"

namespace sow {

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{
    oscColor_ = "#FFFFFF";
}

QString ThemeManager::oscColor()
{
    return oscColor_;
}

void ThemeManager::setOscColor(const QString &oscColor)
{
    if(oscColor_ != oscColor) {
        oscColor_ = oscColor;
    }
    emit oscColorChanged();
}

} // End namespace sow.
