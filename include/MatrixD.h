#ifndef _MATRIXD_H_
#define _MATRIXD_H_

#define MATRIXD &MatrixD_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _VectorD VectorD;
typedef struct _MatrixD MatrixD;

extern Class MatrixD_Class;

extern MatrixD* MatrixD_New(int row, int col);

extern MatrixD* MatrixD_Del(MatrixD* this);

extern MatrixD* MatrixD_Wrap(double* work, int row, int col, int ld);

extern MatrixD* MatrixD_UnWrap(MatrixD* this);

extern IObject* MatrixD_GetIObject(MatrixD* this);

extern int MatrixD_GetRow(MatrixD* this);

extern int MatrixD_GetCol(MatrixD* this);

extern int MatrixD_GetLd(MatrixD* this);

extern double* MatrixD_GetMatrix(MatrixD* this);

extern double MatrixD_GetElement(MatrixD* this, int row_index, int col_index);

extern MatrixD* MatrixD_SetElement(MatrixD* this, int row_index, int col_index, double value);

extern void MatrixD_Show(MatrixD* this);

extern MatrixD* MatrixD_Set(MatrixD* this, double diag, double off_diag);

extern MatrixD* MatrixD_Copy(MatrixD* this, MatrixD* out_matrix);

extern MatrixD* MatrixD_T(MatrixD* this, MatrixD* out_matrix);

extern double MatrixD_Det(MatrixD* this);

extern MatrixD* MatrixD_Inv(MatrixD* this, MatrixD* out_matrix);

extern VectorD* MatrixD_MulVectorD(MatrixD* this, VectorD* in_vector, VectorD* out_vector);

extern VectorD* MatrixD_TMulVectorD(MatrixD* this, VectorD* in_vector, VectorD* out_vector);

extern MatrixD* MatrixD_TMulSelf(MatrixD* this, MatrixD* out_matrix);

extern MatrixD* MatrixD_O2Mul(MatrixD* this, MatrixD* in_matrix, MatrixD* out_matrix);

extern MatrixD* MatrixD_MulMatrixD(MatrixD* this, MatrixD* in_matrix, MatrixD* out_matrix);

extern double MatrixD_MaxDiagElem(MatrixD* this);

extern VectorD* MatrixD_LinearSolver(MatrixD* this, VectorD* in_vector, VectorD* out_vector);

extern void MatrixD_EigenEquation(MatrixD* this, VectorD* out_vector, MatrixD* out_matrix);

#endif/*_Matrix*/
