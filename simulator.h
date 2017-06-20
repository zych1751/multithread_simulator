#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "matrix.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <boost/thread.hpp>
#include "counter.h"

class MainWindow;

class simulator
{
public:
    simulator(MainWindow *window);
    void setMatrixSize(int n);
    void setThreadSize(int n);
    int getMatrixSize();
    int getThreadSize();

    void resetA();
    void resetB();
    void calculate();
    void strassen(boost::shared_ptr<matrix> a, boost::shared_ptr<matrix> b, boost::shared_ptr<matrix>& c);

private:
    const int BASE = 8;
    int matrix_size;
    int thread_size;
    boost::shared_ptr<matrix> mat[3];
    counter _counter;
    MainWindow *mainWindow;

    void view(boost::shared_ptr<matrix> mat);
};

#endif // SIMULATOR_H
