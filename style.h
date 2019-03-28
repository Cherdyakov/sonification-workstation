#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QApplication>

class Style : public QObject
{
    Q_OBJECT
public:
    explicit Style(QObject *parent = nullptr): QObject(parent) {

        map_.insert("textColor", "#f9f9f9");
        map_.insert("windowGrey", "#424242");
        map_.insert("middleGrey", "#393939");
        map_.insert("darkGrey", "#303030");
        map_.insert("nearBlack", "#202020");
    }

    void setStyle() const
    {
        QString style = readStyleSheet();

        // Replace all variables (keys) in style with values.
        QMap<QString, QString>::ConstIterator it = map_.constBegin();
        while (it != map_.end()) {
            style.replace(it.key(), it.value());
            ++it;
        }
        qApp->setStyleSheet(style);
    }

private:

    QString readStyleSheet() const
    {
        // Load stylesheet.
        QFile file(":/styles.qss");
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());
        return stylesheet;
    }

    QMap<QString, QString> map_;

};

#endif // STYLE_H
