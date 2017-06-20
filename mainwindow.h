#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulator.h"
#include <boost/thread.hpp>

namespace Ui {
class MainWindow;
}

class simulator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setName(const QString& name);
    QString name() const;

    void showMatrix(const boost::shared_ptr<matrix> mat, int idx); // idx 0 : A, idx 1 : B, idx 2 : C

public slots:
    void setMatrixSize();
    void setThreadSize();
    void resetA();
    void resetB();
    void calculateMatrix();

private:
    Ui::MainWindow *ui;
    simulator* _simulator;
};

#endif // MAINWINDOW_H
