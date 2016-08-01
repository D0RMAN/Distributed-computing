#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio>

class Matrix
{
public:
    Matrix(void);
    Matrix(const char *fileName);
    Matrix(const Matrix &that);
    ~Matrix();
    void print() const;
    void fprint(FILE *outputFILE) const;
    void print(const char *stringFormat) const;
    void fprint(FILE *outputFILE, const char *stringFormat) const;
    Matrix &operator=(const Matrix &that);
    Matrix operator+(Matrix &that);
    Matrix operator+(double that);
    Matrix operator-(Matrix &that);
    Matrix &operator+=(const Matrix &that);
    Matrix &operator+=(const double that);
    Matrix &operator-=(const Matrix &that);
    Matrix &operator-=(const double that);
    Matrix operator*(const Matrix &that);
    Matrix operator|(const Matrix &that);
    Matrix &transp(void);
    Matrix &norm1(void);
    Matrix &norm2(void);
    double getDetByGauss(void);
    Matrix getInvByGauss(void);
    Matrix getEigenVector(double accuracy, double &maxEValue);
    double mean(void) const;
    void research1(double step, int numOfIter);
    void research2(double step, int numOfIter);
protected:
private:
    int width;
    int height;
    double **data;
private:
    Matrix(const int _heigth, const int _width);
    double det(void);
    int readChars(FILE *pfile);
    double getMaxElemWithExcptns(double *from, bool *excptns, int dataSize, int &maxElemPos);
    void divLine(double *line, int lineSize, const double divisor);
    double abs(double n);
    Matrix abs();
};

#endif // MATRIX_H
