#include "counter.h"

counter::counter()
{
    curSize= 0;
    ready = true;
}

int counter::get()
{
    wait();
    return curSize;
}

bool counter::canAdd(int maxSize)
{
    wait();

    return curSize < maxSize;
}

void counter::incerase()
{
    wait();

    ready = false;
    curSize++;
    ready = true;
    cond.notify_one();
}

void counter::decrease()
{
    wait();

    ready = false;
    curSize--;
    ready = true;
    cond.notify_one();
}

void counter::wait()
{
    boost::unique_lock<boost::mutex> lock(mut);
    while(!ready)
    {
        cond.wait(lock);
    }
}
