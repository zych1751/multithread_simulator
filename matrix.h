#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <boost/thread.hpp>

class matrix
{
private:
    int n;
    long long **arr;
public:
    matrix();
    matrix(int n);
    matrix(const matrix& m);
    ~matrix();

    matrix operator +(const matrix& other) const;
    matrix operator -(const matrix& other) const;
    matrix operator *(const matrix& other) const;

    std::vector<std::vector<boost::shared_ptr<matrix>>> split() const;

    int size() const;
    int getArr(int i, int j) const;
    void setArr(int i, int j, long long val);
};

#endif // MATRIX_H
