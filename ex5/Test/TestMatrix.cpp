/******************************************************************************

                   Written by Avi Kogan, September 2020.
       if you think there is a mistake, you can always contact me here:
                    avi.kogan@mail.huji.ac.il

*******************************************************************************/

#include "TestMatrix.h"
using namespace std;

extern "C" void exit(int status) {
    throw status;
}

void TestMatrix::testPrint()
{
    Matrix m = Matrix(2, 3);
    for(int i = 0; i < 6; ++i)
    {
        m[i] = i;
    }
    m.print();

    m[5] = 0;

    const Matrix newMatConst(m);

    newMatConst.print();
}

// constructor test

void TestMatrix::testValidConstructor()
{
    Matrix mat1(3, 3);
    Matrix mat2(50, 1);
    Matrix mat3(1, 1);
    cout << "Passed testValidConstructor" << endl;
}

void TestMatrix::testDefaultConstructor()
{
    Matrix m;
    cout << "Passed testDefaultConstructor" << endl;
}

void TestMatrix::testCopyConstructor1()
{
    //test values of copied matrix are valid.
    int MAT_SIZE = 9;
    int COLS = 3;
    int ROWS = 3;
    Matrix mat(ROWS, COLS);
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float newVal = i * 1.1;
        mat[i] = newVal;
    }

    Matrix copied(mat);

    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float expected = i * 1.1;
//        cout << "expected: " << expected << " actual: " << copied[i] << endl;
        assert(copied[i] == expected);
    }

    assert(copied.getCols() == mat.getCols() && "Failed: testCopyConstructor1 getCols");
    assert(copied.getRows() == mat.getRows() && "Failed: testCopyConstructor1 getRows");

    cout << "Passed testCopyConstructor1 " << endl;
}

void TestMatrix::testCopyConstructor2()
{
    //test change in copied matrix not affect the original matrix.
    int MAT_SIZE = 9;
    int COLS = 3;
    int ROWS = 3;
    Matrix mat(ROWS, COLS);
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float newVal = i * 1.1;
        mat[i] = newVal;
    }

    Matrix copied(mat);

    copied[2] = 0;
    assert(mat[2] != 0 && "Failed: change in copied matrix with copyConstructor affected the "
                          "original matrix");

    cout << "Passed testCopyConstructor2 " << endl;
}

void TestMatrix::testInvalidConstructor1()
{
    try
    {
        Matrix notValidRow(-10, 6);
    }catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to construct matrix with not valid"
                    "rows number, got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidConstructor 1, check ** no ** cerr message printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidConstructor1, constructor with negative row value not closed "
            "the program" << endl;

}

void TestMatrix::testInvalidConstructor2()
{
    try
    {
        Matrix notValidRow(6, -203);
    }catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to construct matrix with not valid"
                    "column number, got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidConstructor 2, check ** no ** cerr message printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidConstructor2, constructor with negative col value not closed "
            "the program" << endl;
}
// operator=

void TestMatrix::testOperatorAssignment()
{
    Matrix mat1(3,4);
    for(int i = 0; i < 12; ++i)
    {
        mat1[i] = i;
    }
    Matrix mat2;
    mat2 = mat1;
    assert(mat2.getRows() == 3 && "Failed: in operator= rows not updated in assigned matrix");
    assert(mat2.getCols() == 4 && "Failed: in operator= column not updated in assigned matrix");
    for(int i = 0; i < 12; ++i)
    {
        assert(mat2[i] == i && "Failed: in operator= wrong value in assigned matrix");
    }

    //test change in assigned not affect original

    mat2[0] = 5;
    assert(mat1[0] == 0 && "Failed: in operator= change in assigned matrix affect the original");

    //test self assignment
    mat2 = mat2;
    assert(mat2[0] == 5);
    mat1[0] = 3;
    (mat2 = mat2) = mat1;
    assert(mat2[0] == 3);
    
    cout << "Passed test operator=" << endl;
}

// getters

void TestMatrix::testGetters()
{
    Matrix mat1(3, 4);

    assert(mat1.getRows() == 3);
    assert(mat1.getCols() == 4);

    cout << "Passed testGetters" << endl;
}

// OperatorBrackets []

void TestMatrix::testOperatorBrackets()
{
    int MAT_SIZE = 9;
    int COLS = 3;
    int ROWS = 3;
    Matrix mat(COLS, ROWS);
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        assert(mat[i] == 0 && "assert all matrix constructed 0");
        mat[i] = i * 1.1;
    }
    //check if assigned.
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float expected = i * 1.1;
//        cout << "expected: " << expected << " actual: " << mat[i] << endl;
        assert(mat[i] == expected);
    }

    cout << "Passed testOperatorBrackets" << endl;
}

void TestMatrix::testConstOperatorBrackets()
{
    int MAT_SIZE = 9;
    int COLS = 3;
    int ROWS = 3;
    Matrix nonConst(ROWS, COLS);
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float newVal = i * 1.1;
        nonConst[i] = newVal;
    }
    const Matrix constMatrix(nonConst);
    //check if [] available for const.
    for(int i = 0; i < MAT_SIZE; ++i)
    {
        float expected = i * 1.1;
//        cout << "const check, expected: " << expected << " actual: " << nonConst[i] << endl;
        assert(constMatrix[i] == expected);
    }
    cout << "Passed testConstOperatorBrackets" << endl;
}

void TestMatrix::testInvalidOperatorBrackets1()
{
    Matrix m3(2, 5);

    //test 1
    try
    {
        m3[-1];
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid index with operator [], "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorBrackets 1, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: testInvalidOperatorBrackets1, access to not valid index not closed the "
            "program" <<endl;
}

void TestMatrix::testInvalidOperatorBrackets2()
{
    Matrix m3(2, 5);
    //test index > matrix size - given to non-const matrix
    try
    {
        m3[10];
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid index with operator [], "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorBrackets 2, check cerr message actually printed" << endl;
        }
        return;
    }

    cout << "Failed: testInvalidOperatorBrackets2, access to not valid index not closed the "
            "program" <<endl;
}

void TestMatrix::testInvalidOperatorBrackets3()
{
    const Matrix m4(3, 6);
    //test negative index given to const matrix
    try
    {
        m4[-1];
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid index with operator [], "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorBrackets 3, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: testInvalidOperatorBrackets3, access to not valid index not closed the "
            "program" <<endl;
}

void TestMatrix::testInvalidOperatorBrackets4()
{
    const Matrix m4(3, 6);
    //test index > matrix size - given to const matrix
    try
    {
        m4[18];
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid index with operator [], "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorBrackets 4, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: testInvalidOperatorBrackets4, access to not valid index not closed the "
            "program" <<endl;

}

// OperatorParenthesis ()

void TestMatrix::testOperatorParenthesis()
{
    int COLS = 3;
    int ROWS = 3;
    Matrix mat(COLS, ROWS);
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            assert(mat(row, col) == 0 && "assert all matrix constructed 0");
            mat(row, col) = (row + 1) * 1.1;
        }
    }

    //check if assigned.
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            float expected = (row + 1) * 1.1;
//        cout << "const check, expected: " << expected << " actual: " << mat(row, col) << endl;
            assert(mat(row, col) == expected);
        }
    }
    cout << "Passed testOperatorParenthesis" << endl;
}

void TestMatrix::testConstOperatorParenthesis()
{
    int COLS = 3;
    int ROWS = 3;
    Matrix nonConst(ROWS, COLS);

    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            nonConst(row, col) = (row + 1) * 1.1;
        }
    }
    const Matrix constMatrix(nonConst);

    //check if () available for const.
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            float expected = (row + 1) * 1.1;
//        cout << "const check, expected: " << expected << " actual: " << mat(row, col) << endl;
            assert(constMatrix(row, col) == expected);
        }
    }
    cout << "Passed testConstOperatorParenthesis" << endl;
}

void TestMatrix::testInvalidOperatorParenthesis1()
{
    Matrix m3(2, 5);
    //test row > matrix number of rows - given to non-const matrix
    try
    {
        m3(2, 1);
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid row with operator (), "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorParenthesis 1, check cerr message actually "
                    "printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidOperatorParenthesis1, access to row > matrix number of rows "
            "not colsed the program" << endl;
}

void TestMatrix::testInvalidOperatorParenthesis2()
{
    Matrix m3(2, 5);
    //test negative col, given to non-const matrix
    try
    {
        m3(1, -1);
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid column with operator (), "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorParenthesis 2, check cerr message actually "
                    "printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidOperatorParenthesis1, access to negative col not colsed the "
            "program" << endl;
}

void TestMatrix::testInvalidOperatorParenthesis3()
{
    const Matrix m3(2, 5);
    //test row > matrix number of rows - given to const matrix
    try
    {
        m3(2, 1);
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid row with operator (), "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorParenthesis 3, check cerr message actually "
                    "printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidOperatorParenthesis3, access to row > matrix number of rows "
            "not colsed the program" << endl;
}

void TestMatrix::testInvalidOperatorParenthesis4()
{
    const Matrix m3(2, 5);
    //test row > matrix number of rows - given to const matrix
    try
    {
        m3(2, 1);
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when access invalid row with operator (), "
                    "got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidOperatorParenthesis 4, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidOperatorParenthesis4, access to row > matrix number of rows "
            "not colsed the program" << endl;
}

//test Addition

void TestMatrix::testAddition()
{
    Matrix m1(2, 3);
    const Matrix m2(2, 3);
    
    Matrix res1 = m1 + m2;
    assert(res1.getRows() == 2);
    assert(res1.getCols() == 3);
    for(int i = 0; i < 6; ++i)
    {
        assert(res1[i] == 0 && "test 1");
    }

    cout << "Passed testAddition 1, empty matrices" << endl;

    for(int i = 0; i < 6; ++i)
    {
        m1[i] = i;
    }

    Matrix res2 = m1 + m2;
    for(int i = 0; i < 6; ++i)
    {
        assert(res2[i] == m1[i] && "test 2");
    }

    cout << "Passed testAddition 2" << endl;

    Matrix res3 = m1 + res2;
    for(int i = 0; i < 6; ++i)
    {
        float expected = m1[i] * 2;
        assert(res3[i] == expected && "test 3");
    }

    cout << "Passed testAddition 3" << endl;



}

void TestMatrix::testSelfAddition()
{
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    m1 += m2;
    assert(m1.getRows() == 2);
    assert(m1.getCols() == 3);
    for(int i = 0; i < 6; ++i)
    {
//        cout << "expected 0 actual " << m1[i] << endl;
        assert(m1[i] == 0 && "test 1");
    }

    cout << "Passed testSelfAddition 1, empty matrices" << endl;

    for(int i = 0; i < 6; ++i)
    {
        m2[i] = i;
    }

    m1 += m2;
    for(int i = 0; i < 6; ++i)
    {
        assert(m1[i] == i && "test 2");
    }

    cout << "Passed testSelfAddition 2" << endl;

    //test add self
    m1 += m1;
    for(int i = 0; i < 6; ++i)
    {
        float expected = i * 2;
        assert(m1[i] == expected && "test 3");
    }

    cout << "Passed testSelfAddition 3" << endl;
}

void TestMatrix::testInvalidAddition1()
{
    Matrix m3(2, 5);
    const Matrix m4(3, 6);

    try
    {
        m3 + m4;
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to adding matrix(2,5) * matrix"
                    "(3,6) got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidAddition 1, check cerr message actually printed" << endl;
        }
        return;
    }

    cout << "Failed: in testInvalidAddition1, trying to add matrix if not valid dimensions not "
            "closed the program" << endl;
}

void TestMatrix::testInvalidAddition2()
{
    Matrix m3(2, 5);
    const Matrix m4(3, 6);

    try
    {
        m4 + m3;
    }
    catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to adding matrix(3,6) * matrix"
                    "(2,5) got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidAddition 2, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidAddition2, trying to add matrix if not valid dimensions not "
            "closed the program" << endl;
}

//test multiplication

void TestMatrix::testMultiplications()
{
    Matrix m1;
    const Matrix m2;
    Matrix m3(10, 20);
    const Matrix m4(20, 5);

    m1 * m1;
    m1 * m2;
    m2 * m1;
    m2 * m2;


    Matrix m9(m3 * m4);
    assert(m9.getRows() == 10);
    assert(m9.getCols() == 5);

    std::cout << "Passed operator matrix*matrix, test 1, concatenating" << std::endl;

    float num = 2;
    m1[0] = 4;
    m1 = m1 * num;
//    std::cout << "assert " << m1[0] << " == " << 8 << std::endl;
    assert(m1[0] == 8);
    std::cout << "Passed operator matrix*float, test 2" << std::endl;

    num = 5;
    m3(2, 1) = -3;
    m3 = num * m3;
//    std::cout << "assert " << m3(2,1) << " == " << -15 << std::endl;
//    std::cout << "actual " << m3(2,1) << endl;
    assert(m3(2,1) == -15);
    std::cout << "Passed operator float*matrix, test 3" << std::endl;

}

void TestMatrix::testMultSelf()
{
    int ROWS = 3, COLS = 4, SIZE = ROWS * COLS;
    Matrix mat1(ROWS, COLS);

    for(int i = 0; i < SIZE; ++i)
    {
        mat1[i] = i * 1.5;
    }

    mat1 *= 3;

    for(int i = 0; i < SIZE; ++i)
    {
        float expected = i * 1.5 * 3;
        assert(mat1[i] == expected);
    }

    assert(mat1.getRows() == ROWS);
    assert(mat1.getCols() == COLS);

    cout << "Passed mat1 *= scalar " << endl;

    Matrix mat2(4, 2);
    for(int i = 0; i < 8; ++i)
    {
        mat2[i] = i * 0.5;
    }

    mat1 *= mat2;

    float expectedMultRes[3][2] = {{63, 76.5},{171, 220.5}, {279, 364.5 }};

    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 2; ++col)
        {
//            cout << "expected " <<  expectedMultRes[row][col] << " actual " << mat1(row, col)
//            << endl;
            assert(mat1(row, col) == expectedMultRes[row][col]);
        }
    }

    cout << "Passed test mat1 *= mat2" << endl;

    Matrix mat(2,3);
    mat1 *= mat1 *= mat;
    assert(mat1[8] == 0);

    cout << "Passed test mat1 *= mat1 *= mat" << endl;
}

void TestMatrix::testInvalidMultiplications1()
{
    Matrix mat1(3, 2);
    Matrix mat2;

    //test invalid mat * mat
    try
    {
        Matrix newMat = mat1 * mat2;
    } catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to multiply matrix(1,1) * matrix"
                    "(3,2) got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidMultiplications1, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in test testInvalidMultiplications1, in operator* trying to multiply "
            "matrices with not valid dimension not closed the program" << endl;
}

void TestMatrix::testInvalidMultiplications2()
{
    Matrix mat1(3, 2);
    Matrix mat2;

    //test invalid *=
    try
    {
        mat1 *= mat2;
    } catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to multiply matrix(1,1) *= matrix"
                    "(3,2) got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidMultiplications2, check cerr message actually printed" << endl;
        }
        return;
    }

    cout << "Failed: in test testInvalidMultiplications2, in operator *= trying to multiply "
            "matrices with not valid dimension not closed the program" << endl;
}

//test Division

void TestMatrix::testDivision()
{
    int ROWS = 3, COLS = 2, SIZE = ROWS * COLS;
    Matrix mat(ROWS, COLS);
    for(int i = 0; i < SIZE; ++i)
    {
        mat[i] = 1.5 * i;
    }

    Matrix newMat = mat / 2;

    //test division result
    for(int i = 0; i < SIZE; ++i)
    {
        float expected = 1.5 * i / 2;
        assert(newMat[i] == expected);
    }

    cout << "Passed testDivision: mat / scalar" << endl;
}

void TestMatrix::testSelfDivision()
{
    int ROWS = 3, COLS = 2, SIZE = ROWS * COLS;
    Matrix mat(ROWS, COLS);

    for(int i = 0; i < SIZE; ++i)
    {
        mat[i] = 1.5 * i;
    }

    mat /= 2;

    //test division result
    for(int i = 0; i < SIZE; ++i)
    {
        float expected = 1.5 * i / 2;
        assert(mat[i] == expected);
    }

    cout << "Passed testSelfDivision: mat /= scalar" << endl;
}

void TestMatrix::testInvalidDivision1()
{
    int ROWS = 3, COLS = 2, SIZE = ROWS * COLS;
    Matrix mat(ROWS, COLS);
    for(int i = 0; i < SIZE; ++i)
    {
        mat[i] = 1.5 * i;
    }
    //test mat / 0
    try
    {
        Matrix newMat = mat / 0;
    }catch( int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to divide matrix(3,2) / 0 got :"
                 << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidDivision1, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidDivision1, mat / 0 not closed the program" << endl;
}

void TestMatrix::testInvalidDivision2()
{
    int ROWS = 3, COLS = 2, SIZE = ROWS * COLS;
    Matrix mat(ROWS, COLS);
    for(int i = 0; i < SIZE; ++i)
    {
        mat[i] = 1.5 * i;
    }

    try
    {
        mat /= 0;
    }catch( int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to divide matrix(3*2) /= 0 got :"
                 << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidDivision 2, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidDivision2, mat /= 0 not closed the program" << endl;
}

//test equality operations == !=

void TestMatrix::testEqualityOp()
{
    // In assert messages mat(1,1) means matrix of dimensions 1*1
    Matrix mat1;
    Matrix mat2(2, 2);
    assert(!(mat1 == mat2) && "Failed: mat(1,1) == mat(2,2) returned true instead false");

    Matrix mat3(2,2);
    mat2[1] = 1;

    assert(!(mat3 == mat2) && "Failed: mat(2,2) == mat(2,2) with not equal values (diff in index "
                              "1) returned true instead false");

    mat3[1] = 1;
    assert((mat3 == mat2) && "Failed: mat(2,2) == mat(2,2) with equal values returned false "
                             "instead true");

    cout << "Passed testEqualityOp" << endl;
}

void TestMatrix::testNonEqualityOp()
{
    // In assert messages mat(1,1) means matrix of dimensions 1*1
    Matrix mat1;
    Matrix mat2(2, 2);
    assert((mat1 != mat2) && "Failed: mat(1,1) != mat(2,2) returned false instead true");

    Matrix mat3(2,2);
    mat2[1] = 1;

    assert((mat3 != mat2) && "Failed: mat(2,2) != mat(2,2) with not equal values (diff in index "
                              "1) returned false instead true");

    mat3[1] = 1;
    assert(!(mat3 != mat2) && "Failed: mat(2,2) != mat(2,2) with equal values returned true "
                              "instead false");

    cout << "Passed testNonEqualityOp" << endl;
}

//test stream

void TestMatrix::testOutStream()
{
    int ROWS = 3, COLS = 4, SIZE = 12;
    std::ofstream outFile(RESULTS0S1, std::ios::out);
    ifstream compFile(EXPECTEDOS1);
    if(!compFile.good() || !outFile.good())
    {
        cout << "problem in files for testOutStream, the test didnt run" << endl;
        outFile.close();
        compFile.close();
        return;
    }
    Matrix mat(ROWS, COLS);

    for(int i = 0; i < SIZE; ++i)
    {
        mat[i] = i * 1.5;
    }
    outFile << mat;

    outFile.close();
    ifstream outForComp(RESULTS0S1);

    if(_equalFiles(outForComp, compFile))
    {
        cout << "Passed testOutStream, Matrix Operator <<" << endl;
    }
    else
    {
        cout << "Matrix Operator << ** Not-Passed ** check the diff between resultOS1.txt and expectedOS1" <<
             endl;
    }

    outFile.close();
    outForComp.close();
}

void TestMatrix::testInStream()
{
    //testInStream 1
    ifstream inFile1(INFILE1);
    if(!inFile1.good())
    {
        cout << "problem in file for testInStream 1, the test didnt run" << endl;
        inFile1.close();
    }

    Matrix mat(3, 4);
    try
    {
        inFile1 >> mat;
        float expectedMat[12] = {0, 1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12, 13.5, 15, 16.5};
        for(int i = 0; i < 12; ++i)
        {
            assert(mat[i] == expectedMat[i] && "problem in testInStream 1, matrix filled with wrong"
                                               " values");
        }

        cout << "Passed testInStream 1, Matrix Operator >>" << endl;
    } catch(int e)
    {
        cout << "problem in testInStream1, trying to fill matrix with valid file failed, program "
                "exited with exit code " << e << endl;
        return;
    }

    //test matrix with dimensions 1*1, testInStream 2
    ifstream inFile2(INFILE2);

    if(!inFile2.good())
    {
        cout << "problem in file for testInStream 2, the test didnt run" << endl;
        inFile2.close();
        return;
    }

    Matrix mat2;
    try
    {
        inFile2 >> mat2;
        assert(mat2[0] == 1 && "problem in testInStream 2, matrix filled with wrong values");
    } catch(int e)
    {
        cout << "problem in testInStream 2, trying to fill matrix with valid file failed, program "
                "exited with exit code " << e << endl;
        return;
    }

    cout << "Passed testInStream 2, Matrix Operator >>" << endl;
}

void TestMatrix::testInvalidInStream()
{
    ifstream inFile1("notExistFile.txt");
    Matrix mat(3, 4);
    try
    {
        inFile1 >> mat;
    }catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to load invalid file with operator>>"
                 << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testInvalidInStream, check cerr message actually printed" << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidInStream, trying to load invalid file with operator>> not "
            "closed the program" << endl;
}

//test vectorize

void TestMatrix::testVectorize()
{
    Matrix m(2,3);
    for(int i = 0; i < 6; ++i)
    {
        m[i] = i;
    }

    assert(m(1,0) == 3);

    m.vectorize();

    assert(m.getRows() == 6);
    assert(m.getCols() == 1);

    assert((m(3, 0) == m[3]) &&  m[3] == 3 && "Filed: vectorize");
    cout << "Passed testVectorize" << endl;
}

void TestMatrix::testInvalidVectorize()
{
    Matrix m(2,3);
    for(int i = 0; i < 6; ++i)
    {
        m[i] = i;
    }

    assert(m(1,0) == 3);

    m.vectorize();
    try
    {
        m(1,1);
    }catch (int e)
    {
        if (e != 1)
        {
            cout << "Invalid expected return value when trying to access matrix(1,0) after "
                    "vectorize got :" << e << " instead 1" << std::endl;
        }
        else
        {
            cout << "Passed testVectorize, check cerr message actually printed Out of range message"
                 << endl;
        }
        return;
    }
    cout << "Failed: in testInvalidVectorize, access to not valid index after vectorize not "
            "closed the prgram" <<endl;
}

//private
//taken from https://stackoverflow.com/questions/6163611/compare-two-files
bool TestMatrix::_equalFiles(ifstream& in1, ifstream& in2)
{
    ifstream::pos_type size1, size2;

    size1 = in1.seekg(0, ifstream::end).tellg();
    in1.seekg(0, ifstream::beg);

    size2 = in2.seekg(0, ifstream::end).tellg();
    in2.seekg(0, ifstream::beg);

    if(size1 != size2)
        return false;

    static const size_t BLOCKSIZE = 4096;
    size_t remaining = size1;

    while(remaining)
    {
        char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
        size_t size = std::min(BLOCKSIZE, remaining);

        in1.read(buffer1, size);
        in2.read(buffer2, size);

        if(0 != memcmp(buffer1, buffer2, size))
            return false;

        remaining -= size;
    }

    return true;
}







