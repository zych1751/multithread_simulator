#include "matrix.h"

matrix::matrix()
{

}

matrix::matrix(int n): n(n)
{
    arr = new long long*[n];

    for(int i = 0; i < n; i++)
    {
        arr[i] = new long long[n];
        for(int j = 0; j < n; j++)
            arr[i][j] = 0;
    }
}

matrix::matrix(const matrix& m)
{
    n = m.size();

    arr = new long long*[n];

    for(int i = 0; i < n; i++)
    {
        arr[i] = new long long[n];
        for(int j = 0; j < n; j++)
            arr[i][j] = m.getArr(i, j);
    }
}

matrix::~matrix()
{
    for(int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

void matrix::set(int _n)
{
    n = _n;

    arr = new long long*[n];

    for(int i = 0; i < n; i++)
    {
        arr[i] = new long long[n];
        for(int j = 0; j < n; j++)
            arr[i][j] = 0;
    }
}

matrix matrix::operator +(const matrix& other) const
{
    matrix result(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            result.arr[i][j] = arr[i][j] + other.arr[i][j];

    return result;
}

matrix matrix::operator -(const matrix& other) const
{
    matrix result(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            result.arr[i][j] = arr[i][j] - other.arr[i][j];

    return result;
}

matrix matrix::operator *(const matrix& other) const
{
    matrix result(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                result.arr[i][j] += arr[i][k]*other.arr[k][j];

    return result;
}

matrix* matrix::merge(const std::vector<std::vector<matrix>>& C) const
{
    int nn = C[0][0].n;
    matrix* result = new matrix(nn*2);

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int ii = 0; ii < nn; ii++)
                for(int jj = 0; jj < nn; jj++)
                    result->arr[ii+i*nn][jj+j*nn] = C[i][j].arr[ii][jj];

    return result;
}

std::vector<std::vector<matrix>> matrix::split() const
{
    int nn = n/2;
    std::vector<std::vector<matrix>> result(2, std::vector<matrix>(2));

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
        {
            result[i][j].set(nn);
            for(int ii = 0; ii < nn; ii++)
                for(int jj = 0; jj < nn; jj++)
                    result[i][j].arr[ii][jj] = arr[ii+i*nn][jj+j*nn];
        }
    return result;
}

int matrix::size() const
{
    return n;
}

int matrix::getArr(int i, int j) const
{
    return arr[i][j];
}

void matrix::setArr(int i, int j, long long val)
{
    arr[i][j] = val;
}
