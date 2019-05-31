#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>

namespace sow {

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString oscColor READ oscColor WRITE setOscColor NOTIFY oscColorChanged)
    Q_PROPERTY(QString amColor READ amColor WRITE setAmColor NOTIFY amColorChanged)
    Q_PROPERTY(QString fmColor READ fmColor WRITE setFmColorr NOTIFY fmColorChanged)
    Q_PROPERTY(QString audColor READ audColor WRITE setAudColor NOTIFY audColorChanged)
    Q_PROPERTY(QString panColor READ panColor WRITE setPanColor NOTIFY panColorChanged)
    Q_PROPERTY(QString envColor READ envColor WRITE setEnvColor NOTIFY envColorChanged)
    Q_PROPERTY(QString volColor READ volColor WRITE setVolColor NOTIFY volColorChanged)
    Q_PROPERTY(QString nseColor READ nseColor WRITE setNseColor NOTIFY nseColorChanged)
    Q_PROPERTY(QString eqColor READ eqColor WRITE setEqColor NOTIFY eqColorChanged)
    Q_PROPERTY(QString outColor READ outColor WRITE setOutColor NOTIFY outColorChanged)
    Q_PROPERTY(QString textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

public:
    explicit ThemeManager(QObject *parent = nullptr);

    // QL property binding functions
    void setOscColor(const QString &oscColor);
    QString oscColor();
    void setAmColor(const QString &amColor);
    QString amColor();
    void setFmColor(const QString &fmColor);
    QString fmColor();
    void setAudColor(const QString &audColor);
    QString audColor();
    void setPanColor(const QString &panColor);
    QString panColor();
    void setEnvColor(const QString &envColor);
    QString envColor();
    void setVolColor(const QString &envColor);
    QString volColor();
    void setEqColor(const QString &envColor);
    QString eqColor();
    void setNseColor(const QString &envColor);
    QString nseColor();
    void setOutColor(const QString &envColor);
    QString outColor();
    void setTextColor(const QString &envColor);
    QString textColor();

private:

    QString oscColor_;
    QString amColor_;
    QString fmColor_;
    QString audColor_;
    QString panColor_;
    QString envColor_;
    QString volColor_;
    QString nseColor_;
    QString eqColor_;
    QString outColor_;
    QString textColor_;

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

public slots:
};

} // End namespace sow.

#endif // THEMEMANAGER_H
