#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "matrix.h"
#include "mainwindow.h"
#include <QMainWindow>

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

private:
    int matrix_size;
    int thread_size;
    matrix *mat[3];
    const int BASE = 8;
    int cur_thread;
    MainWindow *mainWindow;

    matrix* strassen(matrix* a, matrix* b);
    void view(matrix* mat);
};

#endif // SIMULATOR_H
