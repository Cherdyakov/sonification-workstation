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

    // QL property binding functions
//    void setOscColor(const QString &oscColor);
//    QString oscColor();
//    void setAmColor(const QString &amColor);
//    QString amColor();
//    void setFmColor(const QString &fmColor);
//    QString fmColor();
//    void setAudColor(const QString &audColor);
//    QString audColor();
//    void setPanColor(const QString &panColor);
//    QString panColor();
//    void setEnvColor(const QString &panColor);
//    QString envColor();
//    void setVolColor(const QString &volColor);
//    QString volColor();
//    void setEqColor(const QString &eqColor);
//    QString eqColor();
//    void setNseColor(const QString &nseColor);
//    QString nseColor();
//    void setOutColor(const QString &outColor);
//    QString outColor();
//    void setTextColor(const QString &textColor);
//    QString textColor();

    void setThemeMap(const QVariantMap &map);
    QVariantMap themeMap();

    void loadTheme(QString path);

private:

    QVariantMap themeMap_;

    void setBoundProperties(QString style);

signals:

    // Notify signals
    void oscColorChanged();
    void amColorChanged();
    void fmColorChanged();
    void audColorChanged();
    void panColorChanged();
    void envColorChanged();
    void volColorChanged();
    void nseColorChanged();
    void eqColorChanged();
    void outColorChanged();
    void textColorChanged();

    void themeMapChanged();

public slots:
};

} // End namespace sow.

#endif // THEMEMANAGER_H
