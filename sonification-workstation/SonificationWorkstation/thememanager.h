#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QVariantMap>

namespace sow {

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap themeMap READ themeMap WRITE setThemeMap NOTIFY themeMapChanged)

public:
    explicit ThemeManager(QObject *parent = nullptr);

    // QML property binding functions
    void setThemeMap(const QVariantMap &themeMap);
    QVariantMap themeMap();

    void loadTheme(QString path);

private:

    QVariantMap themeMap_;

    void setQmlTheme(QString style);

signals:

    // Notify signals
    void themeMapChanged();

public slots:
};

} // End namespace sow.

#endif // THEMEMANAGER_H
