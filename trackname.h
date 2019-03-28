#ifndef TRACKNAME_H
#define TRACKNAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "utility.h"

namespace sow {

class TrackName : public QWidget
{
    Q_OBJECT

public:

    explicit TrackName(QWidget *parent = nullptr);

    void setNumber(unsigned int num);
    void setText(const QString name);
    QString text() const;

protected:

    void paintEvent(QPaintEvent* event) override;

private:

    QLabel *label_;
    QString text_;

    QString intToChar(const unsigned int num);

signals:

public slots:
};

} // namespace sow

#endif // TRACKNAME_H
