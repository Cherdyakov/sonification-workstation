#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>

namespace sow {

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString oscColor READ oscColor WRITE setOscColor NOTIFY oscColorChanged)

public:
    explicit ThemeManager(QObject *parent = nullptr);

    QString oscColor();
    void setOscColor(const QString &oscColor);

private:

    QString oscColor_;

signals:

    // Notify signals
    void oscColorChanged();

public slots:
};

} // End namespace sow.

#endif // THEMEMANAGER_H
