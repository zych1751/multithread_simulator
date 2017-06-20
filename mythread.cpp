#include "mythread.h"

mythread::mythread(matrix *_l, matrix *_r)
{
    l = _l;
    r = _r;
}

mythread::~mythread()
{
    delete result;
}

void mythread::join()
{

}
