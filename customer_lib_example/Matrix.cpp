#include "Matrix.h"
#include <cmath>

// public constructors and destructor

Matrix::Matrix(void)
{
    width = 0;
    height = 0;
    data = NULL;
}

/* Trying to read an object from file */
Matrix::Matrix(const char *fileName)
{
    /* set base parameters */
    width = 0;
    height = 0;
    data = NULL;

    /* We'll study what does oldWidth do later.
    For now, it's just some save buffer for matrix width */
    int oldWidth = 0;

    FILE *inputFile = fopen(fileName, "rt");

    if(inputFile != NULL) {

        double bufMartElem = 0.0;
        int resOfPartialRead = 0;
        FILE *systemOutput = fopen("SystemOutput", "wb");

        while(1) {

            /* read no-sense chars */
            if((resOfPartialRead = readChars(inputFile))) {

                if(resOfPartialRead == EOF) {
                    /* If we read all file, we have to close all (FILE *) flows */
                    fclose(inputFile);
                    fclose(systemOutput);

                    /*  */
                    if(oldWidth != width) {
                        if(height) {
                            printf("Error! File with name %s is invalid.\n"
                                   "Number of data in different strings is not similar.\n\n", fileName);
                            fclose(inputFile);
                            fclose(systemOutput);

                            /*  */
                            height = 0;
                            width = 0;

                            return;
                        } else {
                            oldWidth = width;
                        }
                    }

                    /* If we read at the last line some numbers, we have to
                    increment the height because it's incrementing only when
                    we read line in file, but line can pass not only with \n
                    but and with EOF */
                    if(width)
                        ++height;

                    /* If we read some data and write it to the binary file
                    named SystemOutput we should to report that we read something
                    but matrix was not create. */
                    if(!height) {
                        printf("Error! File with name %s is invalid.\n\n", fileName);
                        return;
                    }

                    /* If we read all file, we have to break the main loop. And
                    create an object. */
                    break;
                }

                if(resOfPartialRead == '\n') {

                    /*  */
                    if(oldWidth != width) {
                        if(height) {
                            printf("Error! File with name %s is invalid.\n"
                                   "Number of data in different strings is not similar.\n\n", fileName);
                            fclose(inputFile);
                            fclose(systemOutput);

                            /*  */
                            height = 0;
                            width = 0;

                            return;
                        } else {
                            oldWidth = width;
                        }
                    }

                    /*  */
                    ++height;
                    width = 0;
                }
            }
            fscanf(inputFile, "%lf", &bufMartElem);
            fwrite((const void *)&bufMartElem, sizeof(double), 1, systemOutput);
            width++;
        }

        /* It's could be a situation, when before reach EOF we reach \n.
        But in this case width assign a zero, because it's accumulate
        a number of read matrix elements in the current line. And if the last
        before EOF was \n we think, that it's could be a new line and a new
        data. But we reach an EOF and width is zero. It does not right I think.*/
        width = oldWidth;

        if(width && height) {
            data = new double *[height];
            inputFile = fopen("SystemOutput", "rb");
            for(int i = 0; i < height; ++i) {
                data[i] = new double [width] ();
                fread((void *)data[i], sizeof(double), width, inputFile);
            }
            fclose(inputFile);
        }
    } else {
        printf("Error! File with name %s is invalid.\n"
               "No data in the object.\n\n", fileName);
    }
}

Matrix::Matrix(const Matrix &that)
{
    width = that.width;
    height = that.height;
    data = new double *[height];
    for(int i = 0; i < height; ++i) {
        data[i] = new double [width] ();
        for(int j = 0; j < width; ++j) {
            data[i][j] = that.data[i][j];
        }
    }
}

Matrix::~Matrix(void)
{
    if(width && height) {
        for(int i = 0; i < height; ++i) {
            delete []data[i];
        }
        delete []data;
    }
}

// public methods ans operators

void Matrix::print(void) const
{
    if(height && width) {
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                printf("%14.7f ", data[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void Matrix::fprint(FILE *outputFILE) const
{
    if(height && width) {
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                fprintf(outputFILE, "%14.7f ", data[i][j]);
            }
            fprintf(outputFILE, "\n");
        }
        fprintf(outputFILE, "\n");
    }
}

void Matrix::print(const char *stringFormat) const
{
    if(height && width) {
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                printf(stringFormat, data[i][j]);
            }
//            printf("\n");
        }
//        printf("\n");
    }
}


void Matrix::fprint(FILE *outputFILE, const char *stringFormat) const
{
    if(height && width) {
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                fprintf(outputFILE, stringFormat, data[i][j]);
            }
//            fprintf(outputFILE, "\n");
        }
//        fprintf(outputFILE, "\n");
    }
}

Matrix &Matrix::operator=(const Matrix &that)
{
    if(height && width) {
        for(int i = 0; i < height; ++i) {
            delete []data[i];
        }
        delete []data;
    }
    width = that.width;
    height = that.height;
    data = new double *[height];
    for(int i = 0; i < height; ++i) {
        data[i] = new double [width];
        for(int j = 0; j < width; ++j) {
            data[i][j] = that.data[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(Matrix &that)
{
    Matrix res = *this;
    if((height == that.height) && (width == that.width)) {
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j) {
                res.data[i][j] += that.data[i][j];
            }
    } else {
        printf("Matrices are not the same size.\n"
               "Returned left matrix.\n");
    }
    return res;
}

Matrix Matrix::operator+(double that)
{
    Matrix res = *this;
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j) {
            res.data[i][j] += that;
        }
    return res;
}

Matrix Matrix::operator-(Matrix &that)
{
    Matrix res = *this;
    if((height == that.height) && (width == that.width)) {
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j) {
                res.data[i][j] -= that.data[i][j];
            }
    } else {
        printf("Matrices are not the same size.\n"
               "Returned left matrix.\n");
    }
    return res;
}

Matrix &Matrix::operator+=(const Matrix &that)
{
    if((height == that.height) && (width == that.width)) {
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j) {
                data[i][j] += that.data[i][j];
            }
    } else {
        printf("Matrices are not the same size.\n"
               "Returned left matrix.\n");
    }
    return *this;
}

Matrix &Matrix::operator+=(const double that)
{
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j) {
            data[i][j] += that;
        }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &that)
{
    if((height == that.height) && (width == that.width)) {
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j) {
                data[i][j] -= that.data[i][j];
            }
    } else {
        printf("Matrices are not the same size.\n"
               "Returned left matrix.\n");
    }
    return *this;
}

Matrix &Matrix::operator-=(const double that)
{
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j) {
            data[i][j] -= that;
        }
    return *this;
}

Matrix Matrix::operator*(const Matrix &that)
{
    if(width == that.height) {
        Matrix res(height, that.width);
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < that.width; ++j) {
                for(int k = 0; k < width; ++k) {
                    res.data[i][j] += data[i][k] * that.data[k][j];
                }
            }
        }
        return res;
    }
    printf("Matrices are not suitable.\n"
           "Returned zero matrix.\n");
    Matrix nullMatr;
    return nullMatr;
}

Matrix Matrix::operator|(const Matrix &that)
{
    if(height != that.height) {
        printf("You are trying to paste together matrices that have different height.\n"
               "Returned left matrix.\n");
        return *this;
    }
    Matrix res(height, width + that.width);
    for(int i = 0; i < res.height; ++i) {
        for(int j = 0; j < width; ++j) {
            res.data[i][j] = data[i][j];
        }
        for(int j = 0; j < that.width; ++j) {
            res.data[i][width + j] = that.data[i][j];
        }
    }
    return res;
}


Matrix &Matrix::transp(void)
{
    Matrix res(width, height);
    double bufForElem = 0.0;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            res.data[j][i] = data[i][j];
//            bufForElem = data[i][j];
//            data[i][j] = data[j][i];
//            data[j][i] = bufForElem;
        }
    }
    *this = res;
    return *this;
}

Matrix &Matrix::norm1(void)
{
    double absMaxElem = 0.0;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            if(absMaxElem < abs(data[i][j]))
                absMaxElem = abs(data[i][j]);
        }
    }
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            data[i][j] /= absMaxElem;
        }
    }
    return *this;
}

Matrix &Matrix::norm2(void)
{
    double sum = 0.0;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            sum += data[i][j] * data[i][j];
        }
    }
    double squareRootOfSum = sqrt(sum);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            data[i][j] /= squareRootOfSum;
        }
    }
    return *this;
}

double Matrix::getDetByGauss(void)
{
    double res = 0.0;
    Matrix bufMatr = *this;
    if(bufMatr.height == bufMatr.width) {
        res = 1.0;
        bool    *excptns = new bool [bufMatr.width] ();
        double  mainElem = 0.0;
        int     mainElemPos = 0;
        double  *saveCollumn = new double [bufMatr.height] ();
        for(int i = 0; i < bufMatr.height; ++i) {
            mainElem = getMaxElemWithExcptns(bufMatr.data[i], excptns, bufMatr.width, mainElemPos);
            if(mainElem == 0.0)
                return 0.0;
            res *= mainElem;
            if((i + mainElemPos) % 2) {
                res = -res;
            }
            divLine(bufMatr.data[i], bufMatr.width, mainElem);
            for(int j = 0; j < bufMatr.height; ++j) {
                saveCollumn[j] = -bufMatr.data[j][mainElemPos];
            }
            for(int j = 0; j < bufMatr.height; ++j) {
                if(j != i) {
                    for(int k = 0; k < bufMatr.width; ++k) {
                        bufMatr.data[j][k] += saveCollumn[j] * bufMatr.data[i][k];
                    }
                }
                excptns[j] = false;
            }
        }
        if((bufMatr.height - 1 + mainElemPos) % 2)
            res = -res;
        delete []saveCollumn;
        delete []excptns;
    } else {
        printf("You are trying to get determinant from bad size matrix.\n"
               "Returned zero.\n\n");
    }
    return res;
}

Matrix Matrix::getInvByGauss(void)
{
    Matrix bufMatr = *this;
    if(bufMatr.getDetByGauss() != 0.0) {
        Matrix indentityMatr(height, width);
        for(int i = 0; i < indentityMatr.height; ++i) {
            indentityMatr.data[i][i] = 1.0;
        }
        bool    *excptns = new bool [bufMatr.width] ();
        double  mainElem = 0.0;
        int     mainElemPos = 0;
        double  *saveCollumn = new double [bufMatr.height] ();
        for(int i = 0; i < bufMatr.height; ++i) {
            mainElem = getMaxElemWithExcptns(bufMatr.data[i], excptns, bufMatr.width, mainElemPos);
            divLine(bufMatr.data[i], bufMatr.width, mainElem);
            divLine(indentityMatr.data[i], indentityMatr.width, mainElem);
            for(int j = 0; j < bufMatr.height; ++j) {
                saveCollumn[j] = -bufMatr.data[j][mainElemPos];
            }
            for(int j = 0; j < bufMatr.height; ++j) {
                if(j != i) {
                    for(int k = 0; k < bufMatr.width; ++k) {
                        bufMatr.data[j][k] += saveCollumn[j] * bufMatr.data[i][k];
                        indentityMatr.data[j][k] += saveCollumn[j] * indentityMatr.data[i][k];
                    }
                }
                excptns[j] = false;
            }
        }
        delete []saveCollumn;
        delete []excptns;
        return indentityMatr;
    } else {
        printf("To get inversed matrix you trying to use bad matrix\n"
               "(determinant is zero). Returned current matrix.\n\n");
        return bufMatr;
    }
}

Matrix Matrix::getEigenVector(double accuracy, double &maxEValue)
{
    if(height == width) {

        /* old, current and new eigenvalues */
        Matrix oldEVector(height, 1);
        Matrix curEVector(height, 1);
        Matrix newEVector(height, 1);

        /* it have to start from non zero vector */
        curEVector.data[0][0] = 1.0;

        /* it's a quirk to do first iteration of loop */
        newEVector.data[0][0] = curEVector.data[0][0];

        /* matrix that we need to get */
//        Matrix eigenValues(height, 1);

        /* algorithm to find first eigenvalue */
        double curEValue = 0.0;
        double preEValue = abs(accuracy) + abs(curEValue) + 1.0;
        while(abs(curEValue - preEValue) > accuracy) {

            oldEVector.norm1();
            curEVector.norm1();

            oldEVector = curEVector;
            curEVector = newEVector;

            newEVector = (*this) * curEVector;

            preEValue = curEValue;
            curEValue = newEVector.data[0][0] / curEVector.data[0][0];

            newEVector.norm1();
        }

        maxEValue = curEValue;
        return newEVector;

//        printf("%20.10f\n\n", curEValue);
//
//        oldEVector.print();
//        curEVector.print();
//        newEVector.print();
//        printf("\n\n");
//
//        double meanNewEV = newEVector.mean();
//        double meanCurEV = curEVector.mean();
//        double meanOldEV = oldEVector.mean();
//
//        eigenValues.data[0][0] = curEValue;
//
//        for(int i = 1; i < height; ++i) {
//            eigenValues.data[i][0] =
//                (meanNewEV - eigenValues.data[i - 1][0] * meanCurEV)
//                        / (meanCurEV - eigenValues.data[i - 1][0] * meanOldEV);
//        }
//
//        return eigenValues;

    } else {
        printf("You are trying to get an eigenvalues from not square matrix.\n"
               "Returned current matrix.\n");
        return *this;
    }
}

double Matrix::mean(void) const
{
    double sum = 0.0;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            sum += data[i][j];
        }
    }
    return sum / ((double)(height * width));
}

void Matrix::research1(double step, int numOfIter)
{
    Matrix curMatr = *this;
    double ev = 0.0;
    FILE *outputFILE = fopen("out1.txt", "wt");
    for(int i = 0; i < numOfIter; ++i) {
        (curMatr.getEigenVector(0.0001,  ev)).transp().fprint(outputFILE, "%20.10f");
        fprintf(outputFILE, "%20.10f\n", ev);
        curMatr += step;
    }
    fclose(outputFILE);
}

void Matrix::research2(double step, int numOfIter)
{
    Matrix curMatr = *this;
    double ev = 0.0;
    FILE *outputFILE = fopen("out2.txt", "wt");
    for(int i = 0; i < numOfIter; ++i) {
        (curMatr.getEigenVector(0.0001,  ev)).transp().fprint(outputFILE, "%20.10f");
        fprintf(outputFILE, "%20.10f\n", ev);
        for(int j = 0; j < height; ++j) {
            curMatr.data[j][j] += step;
        }
    }
    fclose(outputFILE);
}


// private methods

/* Create an empty matrix (each value is zero) */
Matrix::Matrix(int _heigth, int _width)
{
    height = _heigth;
    width = _width;
    data = new double *[height];
    for(int i = 0; i < height; ++i) {
        data[i] = new double [width];
        for(int j = 0; j < width; ++j) {
            data[i][j] = 0.0;
        }
    }
}

/* Get a true but dangerous determinant of matrix
(there is no exception to division by zero and etc). */
double Matrix::det(void)
{
    Matrix tmpMatr = *this;
    if(height == width) {
        double res = 1.0;
        for(int i = 0; i < height - 1; ++i) {
            // step 1
            for(int j = i; j < height; ++j) {
                double saveFirst = tmpMatr.data[j][i];
                res *= saveFirst;
                for(int k = i; k < width; ++k) {
                    tmpMatr.data[j][k] /= saveFirst;
                }
            }
            // step 2
            for(int j = i + 1; j < height; ++j) {
                for(int k = 0; k < width; ++k) {
                    tmpMatr.data[j][k] -= tmpMatr.data[i][k];
                }
            }
            tmpMatr.print();
        }
        return res * tmpMatr.data[height - 1][height - 1];
    }
    return 0.0;
}

/*
This function takes a pointer to an open FILE, and attempts to skip whitespace and garbage.
*/
int Matrix::readChars(FILE *pfile)
{
    int bufChar = 0;
    bool isHereNextLine = false;

    while(!feof(pfile)) {

        /* we trying to read one char, and if it's a \n,
        we signaling, that we've get one line from the file*/
        if((bufChar = fgetc(pfile)) == '\n') {
            isHereNextLine = true;
        }

        /* if we got a number, or minus, or plus, we report */
        if( ( (bufChar <= '9') && (bufChar >= '0') ) || (bufChar == '-') || (bufChar == '+') ) {
            /* but before we report, we have to retrieve taken char*/
            ungetc(bufChar, pfile);

            /* if we've get one line we reporting about this before we report about that
            we've read all trash and ready to read double number, because
            \n is more important information than that we */
            if(isHereNextLine) {
                return '\n';
            }

            /* if we've read all trash and ready to read double number
            we are signaling about this by returning zero */
            return 0;
        }
    }

    /* if we've reach to this line, we've get the end-of-file, so
    we have to report that we've get the end-of-file */
    return EOF;
}

double Matrix::getMaxElemWithExcptns(double *from, bool *excptns, int dataSize, int &maxElemPos)
{
    double res = 0.0;
    for(int i = 0; i < dataSize; ++i) {
        if(!excptns[i] && abs(res) < abs(from[i])) {
            res = from[i];
            excptns[i] = true;
            maxElemPos = i;
        }
    }
    return res;
}

void Matrix::divLine(double *line, int lineSize, const double divisor)
{
    if(divisor != 0.0) {
        for(int i = 0; i < lineSize; ++i) {
            line[i] /= divisor;
        }
    } else {
        printf("You are trying to divide by zero.\n");
    }
}

double Matrix::abs(double n)
{
    return (n >= 0.0) ? (n) : (-n);
}

Matrix Matrix::abs(void)
{
    Matrix res = *this;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            res.data[i][j] = abs(data[i][j]);
        }
    }
    return res;
}
