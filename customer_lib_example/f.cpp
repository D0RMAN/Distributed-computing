#include "Matrix.h"

extern "C" {

int f()
{
    Matrix that("InputMatrix.txt");
    that.research1(0.01, 1000);
    that.research2(0.01, 1000);
    return 0;
}
	
}
