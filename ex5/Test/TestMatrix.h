/******************************************************************************

                   Written by Avi Kogan, September 2020.
       if you think there is a mistake, you can always contact me here:
                    avi.kogan@mail.huji.ac.il

*******************************************************************************/

#ifndef SUMMER_EX4_TESTMATRIX_H
#define SUMMER_EX4_TESTMATRIX_H

// Change files path here if needed.


#define INFILE1 "inFile1.txt"

#define INFILE2 "inFile2.txt"

#define RESULTS0S1 "resultOS1.txt"

#define EXPECTEDOS1 "expectedOS1.txt"

#include "Matrix.h"
#include <cassert>
#include <cstring>
#include <fstream>

using std::ifstream;

class TestMatrix
{

public:

    void testPrint(); //use and see if printed correct

    void testValidConstructor();
    void testDefaultConstructor();
    void testCopyConstructor1();
    void testCopyConstructor2();

    void testInvalidConstructor1();
    void testInvalidConstructor2();

    void testOperatorAssignment();

    void testGetters();

    void testOperatorBrackets();
    void testConstOperatorBrackets();

    void testInvalidOperatorBrackets1();
    void testInvalidOperatorBrackets2();
    void testInvalidOperatorBrackets3();
    void testInvalidOperatorBrackets4();

    void testOperatorParenthesis();
    void testConstOperatorParenthesis();

    void testInvalidOperatorParenthesis1();
    void testInvalidOperatorParenthesis2();
    void testInvalidOperatorParenthesis3();
    void testInvalidOperatorParenthesis4();

    void testAddition();
    void testSelfAddition();

    void testInvalidAddition1();
    void testInvalidAddition2();

    void testMultiplications();
    void testMultSelf();

    void testInvalidMultiplications1();
    void testInvalidMultiplications2();

    void testDivision();
    void testSelfDivision();

    void testInvalidDivision1();
    void testInvalidDivision2();

    void testEqualityOp();
    void testNonEqualityOp();

    void testVectorize();
    void testInvalidVectorize();

    void testOutStream();

    void testInStream();
    void testInvalidInStream();


private:

    bool _equalFiles(ifstream& in1, ifstream& in2);
};

#endif //SUMMER_EX4_TESTMATRIX_H
