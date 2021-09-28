#ifndef SUMMER_EX4_MATRIX_H
#define SUMMER_EX4_MATRIX_H

/**
 * @file Matrix.h
 * @author  Avi Kogan <avi.kogan@mail.huji.ac.il>
 * @version 1.0
 * @date 7 September 2020
 *
 * @brief header file of Matrix.cpp
 *
 */

// ------------------------------ includes ------------------------------

#include <iostream>

// -------------------------- using definitions -------------------------

using std::istream;
using std::ostream;
using std::cerr;
using std::endl;
using std::cout;
using std::cin;

// -------------------------- const definitions -------------------------

#define INVALID_DIMENSIONS_ERROR "Invalid matrix dimensions"
#define DIVISION_BY_ZERO_ERROR "Division by zero"
#define INDEX_OUT_OF_RANGE_ERROR "Index out of range."
#define LOAD_FROM_FILE_ERROR "Error loading from input stream."


// ------------------------------ functions -----------------------------

/**
 * @class Matrix
 * @brief The class represents a matrix that contain float, with the API operations.
 */
class Matrix
{

public:
    /**
     * @brief The class constructor - other constructors make deligation to him, Inits a new
     * matrix with all coordinates 0, allocates _matrix member - will freed in destructor.
     * if rows or cols negative it will exit the program.
     * @param rows: the matrix row number
     * @param cols: the matrix column number.
     */
    Matrix(int rows, int cols);

    /**
     * @brief The class default constructor - delegate to class constructor with row = col = 1.
     */
    Matrix() : Matrix(DEFAULT_ROWS, DEFAULT_COLS){}

    /**
      * @brief The class copy constructor - create new matrix with the same rows and same column
      * of the copied matrix, allocates new _matrix member - will freed in destructor.
      * @param rhs: the matrix to copy from
      */
    Matrix(const Matrix& rhs);

    /**
     * @brief The class destructor - delete the _matrix (member) array.
     */
    ~Matrix();

    /**
    *@fn Matrix::getRows()const
    *@brief return the member _rows that represent the number of rows in _matrix.
    */
    int getRows() const { return _rows; };

    /**
    *@fn Matrix::getCols()const
    *@brief return the member _cols that represent the number of column in _matrix.
    */
    int getCols() const { return _cols; };

    /**
    *@fn Matrix::operator=(Matrix const &rhs);
    *@brief delete _matrix and allocates new if the rhs not the same size, the copy all the
    *       coordinates
    *@param rhs: the matrix to copy from.
    *@return reference to the lhs matrix.
    */
    Matrix& operator=(const Matrix& rhs);

    /**
    *@fn Matrix::operator*(const Matrix &rhs) const;
    *@brief construct new matrix from the matrix's multiplication and return it by value.
    *@param rhs: the matrix to multiply the lhs with.
    *@return the new constructed matrix by value.
    */
    Matrix operator*(const Matrix& rhs) const;

    /**
    *@fn Matrix::operator*(float c) const;
    *@brief construct new matrix from the matrix and param c multiplication.
    *@param c: the param to multiply the lhs matrix with.
    *@return the new constructed matrix by value.
    */
    Matrix operator*(const float& c) const;

    /**
    *@fn operator*(float c, const Matrix &rhs);
    *@brief construct new matrix from the matrix and param c multiplication.
    *@param scalarOnLeft: the param to multiply the rhs matrix with.
    *@param rhs: the rhs matrix to multiply the param c with.
    *@return the new constructed matrix by value.
    */
    friend Matrix operator*(const int& scalarOnLeft, const Matrix& rhs);

    /**
    *@fn operator*=(const Matrix &rhs);
    *@brief multiply the lhs Matrix with the rhs, exit the program if the dimensions not valid.
    *@param rhs: the rhs matrix to multiply the param c with.
    *@return the lhs matrix after multiplication by reference.
    */
    Matrix& operator*=(const Matrix& rhs);

    /**
    *@fn operator*=(const float& scalar);
    *@brief multiply the lhs Matrix with the rhs.
    *@param scalar: the param to multiply the lhs matrix with.
    *@return the lhs matrix after multiplication by reference.
    */
    Matrix& operator*=(const float& scalar);

    /**
    *@fn operator/(float c);
    *@brief construct new matrix from the lhs Matrix and divide it by param c, exit the program if
    *       c == 0.
    *@param c: the param to divide new constructed matrix with.
    *@return the new constructed matrix by value.
    */
    Matrix operator/(const float& c) const;

    /**
    *@fn operator/=(float c);
    *@brief divide the lhs Matrix by param c, exit the program if c == 0.
    *@param c: the param to divide the lhs matrix with.
    *@return the lhs matrix by reference.
    */
    Matrix& operator/=(const float& c);

    /**
    *@fn Matrix::operator+(const Matrix &rhs);
    *@brief construct new matrix from the matrix's and adding it to the rhs.
    *@param rhs: the rhs matrix to add with new constructed matrix.
    *@return the new constructed matrix by value after adding.
    */
    Matrix operator+(const Matrix& rhs) const;

    /**
    *@fn operator+=(const Matrix& rhs);
    *@brief add the lhs matrix with the rhs, exit the program if the dimensions not valid.
    *@param rhs: the rhs matrix to add with lhs matrix.
    *@return the lhs matrix by reference.
    */
    Matrix& operator+=(const Matrix& rhs);

    /**
    *@fn operator+=(const float& scalar);
    *@brief add the scalar to each index in the matrix, exit the program if the dimensions not
    *       valid.
    *@param scalar: the scalar to add to each index in the matrix.
    *@return the lhs matrix by reference.
    */
    Matrix& operator+=(const float& scalar);

    /**
    *@fn Matrix::operator()(const int& row, const int& col) const;
    *@return the _matrix row col coordinate by const reference, exit the program if one of them not
    *        valid.
    */
    const float& operator()(const int& row, const int& col) const;

    /**
    *@fn Matrix::operator()(const int& row, const int& col);
    *@return the _matrix row col coordinate by reference, exit the program if one of them not
    *        valid.
    */
    float& operator()(const int& row, const int& col);

    /**
    *@fn Matrix::operator[](const int& ind) const;
    *@return the _matrix index coordinate by const reference, exit the program if the index not
    *        valid.
    */
    const float& operator[](const int& ind) const;

    /**
    *@fn Matrix::operator[](const int& ind);
    *@return the _matrix index coordinate by reference, exit the program if the index not valid.
    */
    float& operator[](const int& ind);

    /**
    *@fn Matrix::operator==(const Matrix& rhs) const;
    *@return true if lhs and rhs have the same values in each of there indexes.
    */
    bool operator==(const Matrix& rhs) const;

    /**
    *@fn Matrix::operator!=(const Matrix& rhs);
    *@return false if lhs and rhs have the same values in each of there indexes.
    */
    bool operator!=(const Matrix& rhs) const { return !(*this == rhs); }

    /**
    *@fn friend operator>>(istream& is, Matrix& rhs);
    *@brief: Fills matrix elements, read the input stream fully to the rhs, exit the program if
    *        is (the input stream) is not valid.
    *@param is the input stream to load to rhs.
    *@param rhs the matrix to load the is to.
    *@return reference to lhs istream.
    */
    friend istream& operator>>(istream& is, Matrix& rhs);

    /**
    *@fn friend ostream& operator<<(ostream& os, const Matrix& rhs);
    *@brief: write the rhs to the given os (output stream), each row in new line, each coordinate
    *        in the row separated by space, no new line after the last row.
    *        exit the program if the os is not valid.
    *@param os the output stream to write the rhs to.
    *@param rhs the matrix to write to the os.
    *@return reference to lhs ostream.
    */
    friend ostream& operator<<(ostream& os, const Matrix& rhs);

    /**
     * @fn Matrix::vectorize();
     * @brief change matrix to be vector - change the matrix to be 1 column matrix with the
     *        current values.
     */
    Matrix& vectorize();

    /**
     * @fn Matrix::print();
     * prints to the standard output - each row in new line, each coordinate in the row separated
     * by space, no new line after the last row.
     */
    void print() const;

private:

    /**
    *@memberof Matrix::_rows
    *@brief represent the matrix number of rows.
    */
    int _rows;

    /**
    *@memberof Matrix:: _cols
    *@brief represent the matrix number of column.
    */
    int _cols;

    /**
    *@memberof Matrix::_matirx
    *@brief pointer to array of float of size _rows * _cols (dynamically allocated).
    */
    float* _matrix;

    /**
     *@static the default number of rows created in the default constructor.
     */
    static const int DEFAULT_ROWS = 1;

    /**
     *@static the default number of column created in the default constructor.
     */
    static const int DEFAULT_COLS = 1;

    /**
     * validate that both leftMat and rightMat have the same dimensions.
     * exit the program if the dimensions are not valid.
     * @param leftMat the left Matrix in the addition.
     * @param rightMat the right Matrix in the addition.
     */
    static void _isValidForAddition(const Matrix& leftMat, const Matrix& rightMat);

    /**
     * validate that the scalar is valid for division, means c != 0. exit the program if c not
     * valid.
     * @param c the scalar to check if valid for division with.
     */
    static void _isValidScalarForDivision(const int& c);

};

#endif //SUMMER_EX4_MATRIX_H
