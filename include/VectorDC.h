#ifndef _VECTORDC_H_
#define _VECTORDC_H_

#include <complex.h>

#define VECTORDC &VectorDC_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _MatrixDC MatrixDC;
typedef struct _VectorDC VectorDC;

extern Class VectorDC_Class;

extern VectorDC* VectorDC_New(int size);

extern VectorDC* VectorDC_Del(VectorDC* this);

extern VectorDC* VectorDC_Wrap(double complex* work, int size, int inc);

extern VectorDC* VectorDC_ReWrap(VectorDC* this, double complex* work, int size, int inc);

extern VectorDC* VectorDC_UnWrap(VectorDC* this);

extern IObject* VectorDC_GetIObject(VectorDC* this);

extern int VectorDC_GetInc(VectorDC* this);

extern int VectorDC_GetSize(VectorDC* this);

extern double complex* VectorDC_GetVector(VectorDC* this);

extern double complex VectorDC_GetElement(VectorDC* this, int index);

extern VectorDC* VectorDC_SetElement(VectorDC* this, int index, double complex value);

extern void VectorDC_Show(VectorDC* this);

extern VectorDC* VectorDC_Full(VectorDC* this, double complex num);

extern VectorDC* VectorDC_Linsapce(VectorDC* this, double complex start, double complex end);

extern VectorDC* VectorDC_Copy(VectorDC* this, VectorDC* out_vector);

extern VectorDC* VectorDC_AddVectorDC(VectorDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern VectorDC* VectorDC_SubVectorDC(VectorDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern VectorDC* VectorDC_MulNumDC(VectorDC* this, double complex num, VectorDC* out_vector);

extern double complex VectorDC_MulVectorDC(VectorDC* this, VectorDC* in_vector);

extern VectorDC* VectorDC_EMulVectorDC(VectorDC* this, VectorDC* in_vector, VectorDC* out_vector);

extern double complex VectorDC_CMulVectorDC(VectorDC* this, VectorDC* in_vector);

extern MatrixDC* VectorDC_TMulVectorDC(VectorDC* this, VectorDC* in_vector, MatrixDC* out_matrix);

#endif/*_VECTORDC_H_*/
