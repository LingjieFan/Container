#ifndef _LAPACK_H_
#define _LAPACK_H_

#include <complex.h>

extern void dgetrf_(int* row, int* col, double* matrixA, int* lda, int* ipiv, int* info);

extern void dgetri_(int* sizeA, double* matrixA, int* lda, int* ipiv, double* work, \
    int* lwork, int* info);

extern void dgetrs_(char* trans, int* sizeA, int* sizeB, double* matrixA, int* lda, int* ipiv, double* matrixB, \
    int* ldb, int* info);

extern void dgeev_(char* jobvl, char* jobvr, int* sizeA, double* matrixA, int* lda, double* w, \
    double* matrixVL, int* ldvl, double* matrixVR, int* ldvr, double* work, int* lwork, \
    double* rwork, int* info);

extern void zgetrf_(int* row, int* col, double complex* matrixA, int* lda, int* ipiv, int* info);

extern void zgetri_(int* sizeA, double complex* matrixA, int* lda, int* ipiv, double complex* work, \
    int* lwork, int* info);

extern void zgeev_(char* jobvl, char* jobvr, int* sizeA, double complex* matrixA, int* lda, double complex* w, \
    double complex* matrixVL, int* ldvl, double complex* matrixVR, int* ldvr, double complex* work, int* lwork, \
    double* rwork, int* info);

extern void zgetrs_(char* trans, int* sizeA, int* sizeB, double complex* matrixA, int* lda, int* ipiv, double complex* matrixB, \
    int* ldb, int* info);

extern void zgesvd_(char* jobu, char* jobvt, int* m, int* n, double complex* a, int* lda, double* s, double complex* u, int* ldu, double complex* vt, int* ldvt, double complex* work, int* lwork, double* rwork, int* info);

extern void zgesv_(int* n, int* nrhs, double complex* a, int* lda, int* ipiv, double complex* b, int* ldb, int* info);

#endif /*_LAPACK_H_*/
