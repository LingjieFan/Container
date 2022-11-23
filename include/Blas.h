#ifndef _BLAS_H_
#define _BLAS_H_

#include <complex.h>

extern void dcopy_(int *size, double *vector1, int *inc1, double *vector2, int *inc2);

extern void dscal_(int *size, double *scale, double *vector, int *inc);

extern void dswap_(int *size, double *vector1, int *inc1, double *vector2, int *inc2);

extern double ddot_(int *size, double *vector1, int *inc1, double *vector2, int *inc2);

extern double dnrm2_(int *size, double *vector, int *inc);

extern void dgemm_(char *transA, char *transB, int *m, int *n, int *k, double *alpha, double *matrixA, int *lda, \
    double *matrixB, int *ldb, double *beta, double *matrixC, int *ldc);

extern void zscal_(int *size, double complex *scale, double complex *vector, int *inc);

extern double complex zdotu_(int *size, double complex *vector1, int *inc1, double complex *vector2, int *inc2);

extern double complex zdotc_(int *n, double complex *vector1, int *inc1, double complex *vector2, int *inc2);

extern void zcopy_(int *size, double complex *vector1, int *inc1, double complex *vector2, int *inc2);

extern void zgemm_(char *transA, char *transB, int *m, int *n, int *k, double complex *alpha, double complex *matrixA, \
    int *lda, double complex *matrixB, int *ldb, double complex *beta, double complex *matrixC, int *ldc);

#endif /*_BLAS_H_*/
