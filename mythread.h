#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "matrix.h"
#include "simulator.h"
#include <boost/thread.hpp>

class mythread
{
public:
    mythread(matrix *_l, matrix *_r);
    ~mythread();
    void join();

private:
    matrix *l, *r;
    matrix *result;
};

#endif // MYTHREAD_H
