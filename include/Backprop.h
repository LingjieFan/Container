#ifndef _BACKPROP_H_
#define _BACKPROP_H_

typedef struct _MatrixDC MatrixDC;
typedef struct _VectorDC VectorDC;

extern void Backprop_MatrixDC_MulVectorDC_ToMatrix1(VectorDC* grad_vector2, VectorDC* vector1, MatrixDC* grad_matrix1);

extern void Backprop_MatrixDC_MulVectorDC_ToVector1(VectorDC* grad_vector2, MatrixDC* matrix, VectorDC* grad_vector1);

extern void Backprop_MatrixDC_MulMatrixDC_ToMatrix1(MatrixDC* grad_matrix3, MatrixDC* matrix2, MatrixDC* grad_matrix1);

extern void Backprop_MatrixDC_MulMatrixDC_ToMatrix2(MatrixDC* grad_matrix3, MatrixDC* matrix1, MatrixDC* grad_matrix2);

extern void Backprop_MatrixDC_Inv_ToMatrix1(MatrixDC* grad_matrix2, MatrixDC* matrix2, MatrixDC* grad_matrix1);

extern void Backprop_MatrixDC_DiagLeftMul_ToMatrix1(MatrixDC* grad_matrix2, VectorDC* vector1, MatrixDC* grad_matrix1);

extern void Backprop_MatrixDC_DiagLeftMul_ToVector1(MatrixDC* grad_matrix2, MatrixDC* matrix1, VectorDC* grad_vector1);

extern void Backprop_MatrixDC_DiagRightMul_ToMatrix1(MatrixDC* grad_matrix2, VectorDC* vector1, MatrixDC* grad_matrix1);

extern void Backprop_MatrixDC_DiagRightMul_ToVector1(MatrixDC* grad_matrix2, MatrixDC* matrix1, VectorDC* grad_vector1);

#endif /*_BACKPROP_H_*/
