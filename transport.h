#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>

namespace son {
class Transport;
}

class son::Transport : public QWidget
{
    Q_OBJECT
public:
    explicit Transport(QWidget *parent = 0);

private:
    void connectUI();
    bool horizontal;
    bool paused;
    QPushButton* pauseButton;
    QPushButton* orientationButton;

signals:
    void orientationChanged(bool flipped);
    void pauseChanged(bool paused);

public slots:
    void on_orientationButtonReleased();
    void on_pauseButtonReleased();
};

#endif // TRANSPORT_H
