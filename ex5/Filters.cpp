#ifndef SUMMER_EX4_FILTERS_CPP
#define SUMMER_EX4_FILTERS_CPP

/**
 * @file Filters.cpp
 * @author  Avi Kogan <avi.kogan@mail.huji.ac.il>
 * @version 1.0
 * @date 7 September 2020
 *
 * @brief implement the function of Filters.
 *
 */

// ------------------------------ includes ------------------------------

#include "Matrix.h"
#include <cmath>

// -------------------------- const definitions -------------------------

/**
 * The number of colors parameter to use in the filters functions.
 */
const int NUMBER_OF_COLORS = 256;

/**
 * The minimal value of color that available in matrix in the after filter function.
 */
const float MIN_COLOR_VAL = 0.f;

/**
 * The maximal value of color that available in matrix in the after filter function.
 */
const float MAX_COLOR_VAL = 255.f;

/**
 * Number of rows in convolution matrix.
 */
const int CONVOLUTION_MAT_ROWS = 3;

/**
 * Number of column in convolution matrix.
 */
const int CONVOLUTION_MAT_COLS = 3;

/**
 * The convolution matrix of blur function as float array, will be used to construct the
 * convolution matrix in blur function.
 */
const float BLUR_CONVOLUTION_MAT[CONVOLUTION_MAT_ROWS][CONVOLUTION_MAT_COLS] =
                                                                {{1.0 / 16, 2.0 / 16, 1.0 / 16},
                                                                {2.0 / 16, 4.0 / 16, 2.0 / 16},
                                                                {1.0 / 16, 2.0 / 16, 1.0 / 16}};
/**
 * The convolution matrix of sobel function of axis X as float array, will be used to construct the
 * convolution matrix of axis X in sobel function.
 */
const float SOBEL_X_CONVOLUTION_MAT[CONVOLUTION_MAT_ROWS][CONVOLUTION_MAT_COLS] =
                                                                {{1.0 / 8, 0.0, -1.0 / 8},
                                                                 {2.0 / 8, 0.0, -2.0 / 8},
                                                                 {1.0 / 8, 0.0, -1.0 / 8}};
/**
 * The convolution matrix of sobel function of axis Y as float array, will be used to construct the
 * convolution matrix of axis Y in sobel function.
 */
const float SOBEL_Y_CONVOLUTION_MAT[CONVOLUTION_MAT_ROWS][CONVOLUTION_MAT_COLS] =
                                                                {{1.0 / 8, 2.0 / 8, 1.0 / 8},
                                                                 {0.0, 0.0, 0.0},
                                                                 {-1.0 / 8, -2.0 / 8, -1.0 / 8}};



//------------------------- decelerations -------------------------

/**
 * @brief updating the given reference 'lowerBound' to the lower index that the given 'num' between
 *        it and the next index values.
 * @param num the num to check between which two indexes values he is.
 * @param arrayOfLevels the array with the levels to check between which to the num is.
 * @param arraySize the size of arrayOfLevels
 * @param lowerBound the index that the given 'num' between it and the next index values.
 */
void _updateLowerLevelBoundInd(float num, int* arrayOfLevels, int arraySize, int& lowerBound);

/**
 * @brief Returns to the convolution function the appropriate value for the given parameters.
 * @param image the image to return the value in.
 * @param imageRow the row of the coordinate in the image to return its value.
 * @param imageCol the column of the coordinate in the image to return its value.
 * @return if the given 'imageRow' and 'imageCol' are valid returns the value in the appropriate
 *         coordinate, otherwise return 0.
 */
float _getVal(const Matrix& image, int imageRow, int imageCol);

/**
 * validate that all the values in the given Matrix are between MIN_COLOR_VAL - MAX_COLOR_VAL,
 * if the value in some coordinate lower than MIN_COLOR_VAL it change it to MIN_COLOR_VAL,
 * if the value in some coordinate greater than MAX_COLOR_VAL it change it to MAX_COLOR_VAL.
 * @param mat the matrix to validate
 */
void _validateResult(Matrix& mat);

/**
 * Calculate the convolution with the given 'image' Matrix and 'convolutionMat' Matrix and updating
 * according to the convolution result the given Matrix reference 'result',
 * @param result the Matrix to update with the convolution calculations.
 * @param image the image to calculate in the convolution.
 * @param convolutionMat the convolution Matrix to calculate in the convolution.
 */
void _convolution(Matrix& result, const Matrix& image, const Matrix& convolutionMat);

/**
 * Perform the quantization operation on the given 'image' according to the given 'levels'.
 * @param image the image to perform the quantization on.
 * @param levels the levels to to perform the quantization according to.
 * @return new Matrix with the value of image after the quantization.
 */
Matrix quantization(const Matrix& image, int levels);

/**
 * Perform the blur operation on the given 'image'.
 * @param image the image to perform the blur on.
 * @return new Matrix with the value of image after the blur.
 */
Matrix blur(const Matrix& image);

/**
 * Perform the sobel operation on the given 'image'.
 * @param image the image to perform the sobel on.
 * @return new Matrix with the value of image after the sobel.
 */
Matrix sobel(const Matrix& image);

//------------------------- implementations -------------------------

void _updateLowerLevelBoundInd(float num, int* arrayOfLevels, int arraySize, int& lowerBound)
{
    for(int i = 0; i < arraySize - 1; ++i)
    {
        if(arrayOfLevels[i] <= num && num < arrayOfLevels[i + 1])
        {
            lowerBound = i;
            return;
        }
    }
}

float _getVal(const Matrix& image, int imageRow, int imageCol)
{
    if(imageRow < 0 || imageRow >= image.getRows() || imageCol < 0 || imageCol >= image.getCols())
    {
        return 0;
    }
    return image(imageRow, imageCol);
}

void _validateResult(Matrix& mat)
{
    int matSize = mat.getRows() * mat.getCols();
    for(int i = 0; i < matSize; ++i)
    {
        if(mat[i] < MIN_COLOR_VAL)
        {
            mat[i] = MIN_COLOR_VAL;
        }
        else if(mat[i] > MAX_COLOR_VAL)
        {
            mat[i] = MAX_COLOR_VAL;
        }
    }
}

void _convolution(Matrix& result, const Matrix& image, const Matrix& convolutionMat)
{
    for(int row = 0; row < image.getRows(); ++row)
    {
        for(int col = 0; col < image.getCols(); ++col)
        {

            result(row, col) =  rintf(
                    _getVal(image, row - 1, col - 1) * convolutionMat(0, 0) +
                    _getVal(image, row - 1, col)     * convolutionMat(0, 1) +
                    _getVal(image, row - 1, col + 1) * convolutionMat(0, 2) +
                    _getVal(image, row, col - 1)     * convolutionMat(1, 0) +
                    _getVal(image, row, col)         * convolutionMat(1, 1) +
                    _getVal(image, row, col + 1)     * convolutionMat(1, 2) +
                    _getVal(image, row + 1, col - 1) * convolutionMat(2, 0) +
                    _getVal(image, row + 1, col)     * convolutionMat(2, 1) +
                    _getVal(image, row + 1, col + 1) * convolutionMat(2, 2));
        }
    }
}

Matrix quantization(const Matrix& image, int levels)
{
    //create the array of levels
    int* arrayOfLimits = new int[levels + 1];
    int numOfColorsInLevel = NUMBER_OF_COLORS / levels;
    for(int i = 0; i < levels; ++i)
    {
        arrayOfLimits[i] = i * numOfColorsInLevel;
    }
    arrayOfLimits[levels] = NUMBER_OF_COLORS; //for average calculations.

    //create array of the averages
    int* arrayOfAverages = new int[levels];
    for(int i = 0; i < levels; ++i)
    {
        arrayOfAverages[i] = (arrayOfLimits[i] + arrayOfLimits[i + 1] - 1) / 2;
    }
    arrayOfLimits[levels] = NUMBER_OF_COLORS;

    Matrix matToReturn(image.getRows(), image.getCols());

    //do the quantization
    int imageMatSize = image.getRows() * image.getCols();
    int lowerLevelBound; //the lower bound index in arrayOfLimits -> the needed index in
                         // arrayOfAverages
    for(int i = 0; i < imageMatSize; ++i)
    {
        _updateLowerLevelBoundInd(image[i], arrayOfLimits, levels + 1, lowerLevelBound);
        matToReturn[i] = arrayOfAverages[lowerLevelBound];
    }
    delete[] arrayOfLimits;
    delete[] arrayOfAverages;

    return matToReturn;
}


Matrix blur(const Matrix& image)
{
    Matrix convolutionMat = Matrix(image.getRows(), image.getCols());
    for(int row = 0; row < image.getRows(); ++row)
    {
        for(int col = 0; col < image.getCols(); ++col)
        {
            convolutionMat(row, col) = BLUR_CONVOLUTION_MAT[row][col];
        }
    }

    Matrix convolutionResult = Matrix(image.getRows(), image.getCols());

    _convolution(convolutionResult, image, convolutionMat);
    _validateResult(convolutionResult);
    return convolutionResult;
}

Matrix sobel(const Matrix& image)
{
    Matrix convolutionMatX = Matrix(image.getRows(), image.getCols());
    Matrix convolutionMatY = Matrix(image.getRows(), image.getCols());

    Matrix convolutionResultsX = Matrix(image.getRows(), image.getCols());
    Matrix convolutionResultsY = Matrix(image.getRows(), image.getCols());

    for(int row = 0; row < image.getRows(); ++row)
    {
        for(int col = 0; col < image.getCols(); ++col)
        {
            convolutionMatX(row, col) = SOBEL_X_CONVOLUTION_MAT[row][col];
            convolutionMatY(row, col) = SOBEL_Y_CONVOLUTION_MAT[row][col];
        }
    }

    _convolution(convolutionResultsX, image, convolutionMatX);
    _convolution(convolutionResultsY, image, convolutionMatY);

    Matrix res = convolutionResultsX + convolutionResultsY;
    _validateResult(res);

    return res;
}


#endif //SUMMER_EX4_FILTERS_CPP