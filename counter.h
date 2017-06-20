#ifndef COUNTER_H
#define COUNTER_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

class counter
{
public:
    counter();
    bool canAdd(int maxSize);
    void incerase();
    void decrease();
    int get();

private:
    bool ready;
    boost::mutex mut;
    boost::condition_variable cond;
    int curSize;

    void wait();
};

#endif // COUNTER_H
