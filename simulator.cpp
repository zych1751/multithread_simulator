#include "simulator.h"
#include <boost/thread.hpp>
#include <QTextStream>

simulator::simulator(MainWindow *window)
{
    matrix_size = 1;
    thread_size = 0;
    cur_thread = 0;

    for(int i = 0; i < 3; i++)
        mat[i] = boost::shared_ptr<matrix>(new matrix(1));

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
        mat[i] = boost::shared_ptr<matrix>(new matrix(matrix_size));
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
    QTextStream qt(stdout);
    qt << cur_thread << endl;

    strassen(mat[0], mat[1], mat[2]);

    mainWindow->showMatrix(mat[2], 2);
}

void simulator::strassen(boost::shared_ptr<matrix> a, boost::shared_ptr<matrix> b, boost::shared_ptr<matrix>& c)
{
    if(a->size() <= BASE)
    {
        c = boost::shared_ptr<matrix>(new matrix((*a)*(*b)));
        return;
    }

    auto A = a->split();
    auto B = b->split();

    boost::shared_ptr<matrix> M[7], l[7], r[7];

    l[0] = boost::shared_ptr<matrix>(new matrix(*A[0][0]+*A[1][1])), r[0] = boost::shared_ptr<matrix>(new matrix(*B[0][0]+*B[1][1]));
    l[1] = boost::shared_ptr<matrix>(new matrix(*A[1][0]+*A[1][1])), r[1] = boost::shared_ptr<matrix>(new matrix(*B[0][0]));
    l[2] = boost::shared_ptr<matrix>(new matrix(*A[0][0])), r[2] = boost::shared_ptr<matrix>(new matrix(*B[0][1]-*B[1][1]));
    l[3] = boost::shared_ptr<matrix>(new matrix(*A[1][1])), r[3] = boost::shared_ptr<matrix>(new matrix(*B[1][0]-*B[0][0]));
    l[4] = boost::shared_ptr<matrix>(new matrix(*A[0][0]+*A[0][1])), r[4] = boost::shared_ptr<matrix>(new matrix(*B[1][1]));
    l[5] = boost::shared_ptr<matrix>(new matrix(*A[1][0]-*A[0][0])), r[5] = boost::shared_ptr<matrix>(new matrix(*B[0][0]+*B[0][1]));
    l[6] = boost::shared_ptr<matrix>(new matrix(*A[0][1]-*A[1][1])), r[6] = boost::shared_ptr<matrix>(new matrix(*B[1][0]+*B[1][1]));

    boost::shared_ptr<boost::thread> th[7];
    bool waited[7] = {0, };

    for(int i = 0; i < 7; i++)
    {
        if(cur_thread < thread_size)
        {
            cur_thread++;
            th[i] = boost::shared_ptr<boost::thread>(new boost::thread(&simulator::strassen, this, l[i], r[i], boost::ref(M[i])));
            waited[i] = true;
        }
        else    strassen(l[i], r[i], M[i]);
    }

    for(int i = 0; i < 7; i++)
        if(waited[i])
        {
            th[i]->join();
            cur_thread--;
        }

    std::vector<std::vector<boost::shared_ptr<matrix>>> C(2, std::vector<boost::shared_ptr<matrix>>(2));

    C[0][0] = boost::shared_ptr<matrix>(new matrix((*M[0])+(*M[3])-(*M[4])+(*M[6])));
    C[0][1] = boost::shared_ptr<matrix>(new matrix((*M[2])+(*M[4])));
    C[1][0] = boost::shared_ptr<matrix>(new matrix((*M[1])+(*M[3])));
    C[1][1] = boost::shared_ptr<matrix>(new matrix((*M[0])-(*M[1])+(*M[2])+(*M[5])));

    int nn = C[0][0]->size();
    c = boost::shared_ptr<matrix>(new matrix(nn*2));

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int ii = 0; ii < nn; ii++)
                for(int jj = 0; jj < nn; jj++)
                    c->setArr(ii+i*nn, jj+j*nn, C[i][j]->getArr(ii, jj));
    return;
}
