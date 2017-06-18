#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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

    void set(int _n);

    matrix operator +(const matrix& other) const;
    matrix operator -(const matrix& other) const;
    matrix operator *(const matrix& other) const;

    matrix* merge(const std::vector<std::vector<matrix*>>& C) const;
    std::vector<std::vector<matrix*>> split() const;

    int size() const;
    int getArr(int i, int j) const;
    void setArr(int i, int j, long long val);
};

#endif // MATRIX_H
