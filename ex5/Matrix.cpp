/**
 * @file Matrix.cpp
 * @author  Avi Kogan <avi.kogan@mail.huji.ac.il>
 * @version 1.0
 * @date 7 September 2020
 *
 * @brief The class Matrix operators and constructors implementation.
 */

#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int rows, int cols)
{
    if(rows < 0 || cols < 0)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        _rows = rows;
        _cols = cols;
        _matrix = new float[rows * cols];
        long matSize = _rows * _cols;
        for(long i = 0; i < matSize; ++i)
        {
            _matrix[i] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& rhs): _rows(rhs._rows ), _cols(rhs._cols)
{
    _matrix =  new float[_rows * _cols];

    long matSize = _rows * _cols;
    for(long i = 0; i < matSize; ++i)
    {
        _matrix[i] = rhs._matrix[i];
    }
}

Matrix::~Matrix()
{
    delete[] _matrix;
    _matrix = nullptr;
}

Matrix & Matrix::vectorize()
{
    _rows *= _cols;
    _cols = 1;
    return *this;
}

void Matrix::print() const
{
    for(int row = 0; row < _rows; ++row)
    {
        for(int col = 0; col < _cols - 1; ++col)
        {
            cout << this->operator()(row, col) << " ";
        }
        cout << this->operator()(row, _cols - 1);
        if(row != _rows - 1)
        {
            cout << endl;
        }
    }
}

Matrix& Matrix::operator=(const Matrix &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    _rows = rhs._rows;
    _cols = rhs._cols;
    delete[] _matrix;

    _matrix = new float[rhs._rows * rhs._cols]();

    long matSize = _rows * _cols;
    for(long i = 0; i < matSize; ++i)
    {
        _matrix[i] = rhs._matrix[i];
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &rhs) const
{
    if(_cols != rhs._rows)
    {
        cerr << INVALID_DIMENSIONS_ERROR << endl;
        exit(EXIT_FAILURE);
    }

    Matrix newMat = Matrix(_rows, rhs._cols);
    for(int i = 0; i < newMat._rows; i++)
    {
        for(int j = 0; j < newMat._cols; j++)
        {
            for(int k = 0; k < _cols; k++)
            {
                newMat(i, j) += (this->operator()(i, k) * rhs(k, j));
            }
        }
    }
    return newMat;
}

Matrix Matrix::operator*(const float &c) const
{
    return c * (*this);
}

Matrix operator*(const int &c, const Matrix &rhs)
{
    Matrix newMat = Matrix(rhs._rows, rhs._cols);
    long matSize = newMat._rows * newMat._cols;
    for(long i = 0; i < matSize; ++i)
    {
        newMat._matrix[i] = rhs._matrix[i] * c;
    }

    return newMat;
}

Matrix &Matrix::operator*=(const Matrix &rhs)
{
    Matrix newMat = Matrix(_rows, rhs._cols);
    newMat = (*this) * rhs; //validate the dimensions in ((*this) * mat) operator.

    *this = newMat;
    return *this;
}

Matrix& Matrix::operator*=(const float &scalar)
{
    int matSize = _rows * _cols;
    for(int i = 0; i < matSize; ++i)
    {
        _matrix[i] *= scalar;
    }
    return *this;
}


Matrix Matrix::operator+(const Matrix &rhs) const
{
    _isValidForAddition(*this, rhs); //if not will exit the program

    Matrix newMat = Matrix(_rows, _cols);
    for(long int i = 0; i < _rows * _cols; i++)
    {
        newMat._matrix[i] = _matrix[i] + rhs._matrix[i];
    }
    return newMat;
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
    _isValidForAddition(*this, rhs); //if not will exit the program

    int matSize = _rows * _cols;

    for(int i = 0; i < matSize; ++i)
    {
        _matrix[i] += rhs._matrix[i];
    }
    return *this;
}

Matrix& Matrix::operator+=(const float &scalar)
{
    int matSize = _rows * _cols;

    for(int i = 0; i < matSize; ++i)
    {
        _matrix[i] += scalar;
    }
    return *this;
}

const float& Matrix::operator[](const int &ind) const
{
    if(ind < 0 || ind >= _rows * _cols)
    {
        cerr << INDEX_OUT_OF_RANGE_ERROR << endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[ind];
}

float& Matrix::operator[](const int &ind)
{
    if(ind < 0 || ind >= _rows * _cols)
    {
        cerr << INDEX_OUT_OF_RANGE_ERROR << endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[ind];
}

const float& Matrix::operator()(const int &row, const int &col) const
{
    if(row < 0 || col < 0 || _rows <= row || _cols <= col)
    {
        cerr << INDEX_OUT_OF_RANGE_ERROR << endl;
        exit(EXIT_FAILURE);
    }
    int returnInd = _cols * row + col;
    return _matrix[returnInd];
}

float& Matrix::operator()(const int &row, const int &col)
{
    if(row < 0 || col < 0 || _rows <= row || _cols <= col)
    {
        cerr << INDEX_OUT_OF_RANGE_ERROR << endl;
        exit(EXIT_FAILURE);
    }
    int returnInd = _cols * row + col;
    return _matrix[returnInd];
}

bool Matrix::operator==(const Matrix &rhs) const
{
    if(_rows != rhs._rows || _cols != rhs._cols)
    {
        return false;
    }

    int matSize = _cols * _rows;
    for(int i = 0; i < matSize; ++i)
    {
        if(_matrix[i] != rhs._matrix[i])
        {
            return false;
        }
    }
    return true;
}

Matrix Matrix::operator/(const float &c) const
{
    _isValidScalarForDivision(c); //if not will exit the program
    Matrix newMat(_rows, _cols);
    int matSize = _rows * _cols;
    for(int i = 0; i < matSize; ++i)
    {
        newMat[i] = _matrix[i] / c;
    }
    return newMat;
}

Matrix& Matrix::operator/=(const float &c)
{
    _isValidScalarForDivision(c); //if not will exit the program
    int matSize = _rows * _cols;
    for(int i = 0; i < matSize; ++i)
    {
        _matrix[i] /= c;
    }
    return *this;
}

istream& operator>>(istream &is, Matrix &rhs)
{
    if(!is.good())
    {
        cerr << LOAD_FROM_FILE_ERROR << endl;
        exit(EXIT_FAILURE);
    }

    float curData;
    int curInd = 0;
    while(is >> curData)
    {
        rhs[curInd] = curData;
        curInd++;
    }
    return is;
}

ostream& operator<<(ostream& os, const Matrix &rhs)
{
    if(!os.good())
    {
        cerr << LOAD_FROM_FILE_ERROR << endl;
        exit(EXIT_FAILURE);
    }

    for(int row = 0; row < rhs._rows; ++row)
    {
        for(int col = 0; col < rhs._cols - 1; ++col)
        {
            os << rhs(row, col) << " ";
        }
        os << rhs(row, rhs._cols - 1);
        if(row != rhs._rows - 1)
        {
            os << endl;
        }
    }
    return os;
}

void Matrix::_isValidForAddition(const Matrix &leftMat, const Matrix &rightMat)
{
    if(leftMat._rows != rightMat._rows || leftMat._cols != rightMat._cols)
    {
        cerr << INVALID_DIMENSIONS_ERROR << endl;
        exit(EXIT_FAILURE);
    }
}

void Matrix::_isValidScalarForDivision(const int &c)
{
    if(c == 0)
    {
        cerr << DIVISION_BY_ZERO_ERROR << endl;
        exit(EXIT_FAILURE);
    }
}


