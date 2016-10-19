#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QQuickView *getView() const;
    void setView(QQuickView *value);

private:
    Ui::MainWindow *ui;
    QQuickView* view;
};

#endif // MAINWINDOW_H
