#ifndef _MATRIXDC_H_
#define _MATRIXDC_H_

#include <complex.h>

#define MATRIXDC &MatrixDC_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _VectorDC VectorDC;
typedef struct _MatrixDC MatrixDC;

extern Class MatrixDC_Class;

extern MatrixDC* MatrixDC_New(int row, int col);

extern MatrixDC* MatrixDC_Del(MatrixDC* this);

extern MatrixDC* MatrixDC_Wrap(double complex* work, int row, int col, int ld);

extern MatrixDC* MatrixDC_ReWrap(MatrixDC* this, double complex* work, int row, int col, int ld);

extern MatrixDC* MatrixDC_UnWrap(MatrixDC* this);

extern IObject* MatrixDC_GetIObject(MatrixDC* this);

extern int MatrixDC_GetRow(MatrixDC* this);

extern int MatrixDC_GetCol(MatrixDC* this);

extern int MatrixDC_GetLd(MatrixDC* this);

extern double complex* MatrixDC_GetMatrix(MatrixDC* this);

extern double complex MatrixDC_GetElement(MatrixDC* this, int row_index, int col_index);

extern MatrixDC* MatrixDC_SetElement(MatrixDC* this, int row_index, int col_index, double complex value);

extern void MatrixDC_Show(MatrixDC* this);

extern MatrixDC* MatrixDC_Set(MatrixDC* this, double complex diag, double complex off_diag);

extern MatrixDC* MatrixDC_Copy(MatrixDC* this, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_T(MatrixDC* this, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_CT(MatrixDC* this, MatrixDC* out_matrix);

extern double complex MatrixDC_Det(MatrixDC* this);

extern MatrixDC* MatrixDC_Inv(MatrixDC* this, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_PInv(MatrixDC* this, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_AddMatrixDC(MatrixDC* this, MatrixDC* in_matrix, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_SubMatrixDC(MatrixDC* this, MatrixDC* in_matrix, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_MulNumDC(MatrixDC* this, double complex num, MatrixDC* out_matrix);

extern VectorDC* MatrixDC_MulVectorDC(MatrixDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern VectorDC* MatrixDC_TMulVectorDC(MatrixDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern VectorDC* MatrixDC_CMulVectorDC(MatrixDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern MatrixDC* MatrixDC_TMulSelf(MatrixDC* this, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_O2Mul(MatrixDC* this, MatrixDC* in_matrix, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_DiagLeftMul(MatrixDC* this, VectorDC* diag_matrix, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_DiagRightMul(MatrixDC* this, VectorDC* diag_matrix, MatrixDC* out_matrix);

extern MatrixDC* MatrixDC_MulMatrixDC(MatrixDC* this, MatrixDC* in_matrix, MatrixDC* out_matrix);

extern VectorDC* MatrixDC_LinearSolver(MatrixDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern void MatrixDC_EigenEquation(MatrixDC* this, VectorDC* out_vector, MatrixDC* out_matrix);

#endif/*_MATRIXDC_H_*/
