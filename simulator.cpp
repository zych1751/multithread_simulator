#include "simulator.h"
//#include <boost/thread.hpp>

simulator::simulator(MainWindow *window)
{
    matrix_size = 1;
    thread_size = 0;
    cur_thread = 0;

    for(int i = 0; i < 3; i++)
        mat[i] = new matrix(1);

    mainWindow = window;

    for(int i = 0; i < 3; i++)
        mainWindow->showMatrix(mat[i], i);
}

void simulator::setMatrixSize(int n)
{
    if(matrix_size == (1<<n))
        return;

    matrix_size = (1<<n);

    for(int i = 0; i < 3; i++)
    {
        delete mat[i];
        mat[i] = new matrix(matrix_size);
        mainWindow->showMatrix(mat[i], i);
    }
}

void simulator::setThreadSize(int n)
{
    thread_size = n;
}

int simulator::getMatrixSize()
{
    return matrix_size;
}

int simulator::getThreadSize()
{
    return thread_size;
}

void simulator::resetA()
{
    for(int i = 0; i < mat[0]->size(); i++)
        for(int j = 0; j < mat[0]->size(); j++)
            mat[0]->setArr(i, j, rand()%100);
    mainWindow->showMatrix(mat[0], 0);
}

void simulator::resetB()
{
    for(int i = 0; i < mat[1]->size(); i++)
        for(int j = 0; j < mat[1]->size(); j++)
            mat[1]->setArr(i, j, rand()%100);
    mainWindow->showMatrix(mat[1], 1);
}

void simulator::calculate()
{
    delete mat[2];

    mat[2] = strassen(mat[0], mat[1]);

    mainWindow->showMatrix(mat[2], 2);
}

matrix* simulator::strassen(matrix* a, matrix* b)
{
    if(a->size() <= BASE)
        return new matrix((*a)*(*b));

    auto A = a->split();
    auto B = b->split();

    matrix *M[7], *l[7], *r[7];

    l[0] = new matrix(*A[0][0]+*A[1][1]), r[0] = new matrix(*B[0][0]+*B[1][1]);
    M[0] = strassen(l[0], r[0]);

    l[1] = new matrix(*A[1][0]+*A[1][1]), r[1] = new matrix(*B[0][0]);
    M[1] = strassen(l[1], r[1]);

    l[2] = new matrix(*A[0][0]), r[2] = new matrix(*B[0][1]-*B[1][1]);
    M[2] = strassen(l[2], r[2]);

    l[3] = new matrix(*A[1][1]), r[3] = new matrix(*B[1][0]-*B[0][0]);
    M[3] = strassen(l[3], r[3]);

    l[4] = new matrix(*A[0][0]+*A[0][1]), r[4] = new matrix(*B[1][1]);
    M[4] = strassen(l[4], r[4]);

    l[5] = new matrix(*A[1][0]-*A[0][0]), r[5] = new matrix(*B[0][0]+*B[0][1]);
    M[5] = strassen(l[5], r[5]);

    l[6] = new matrix(*A[0][1]-*A[1][1]), r[6] = new matrix(*B[1][0]+*B[1][1]);
    M[6] = strassen(l[6], r[6]);


    std::vector<std::vector<matrix*>> C(2, std::vector<matrix*>(2));

    C[0][0] = new matrix((*M[0])+(*M[3])-(*M[4])+(*M[6]));
    C[0][1] = new matrix((*M[2])+(*M[4]));
    C[1][0] = new matrix((*M[1])+(*M[3]));
    C[1][1] = new matrix((*M[0])-(*M[1])+(*M[2])+(*M[5]));

    for(int i = 0; i < 7; i++)
    {
        delete l[i];
        delete r[i];
        delete M[i];
    }

    return matrix().merge(C);
}
