#ifndef _VECTORD_H_
#define _VECTORD_H_

#define VECTORD &VectorD_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _VectorD VectorD;

extern Class VectorD_Class;

extern VectorD* VectorD_New(int size);

extern VectorD* VectorD_Del(VectorD* this);

extern VectorD* VectorD_Wrap(double* work, int size, int inc);

extern VectorD* VectorD_ReWrap(VectorD* this, double* work, int size, int inc);

extern VectorD* VectorD_UnWrap(VectorD* this);

extern IObject* VectorD_GetIObject(VectorD* this);

extern int VectorD_GetInc(VectorD* this);

extern int VectorD_GetSize(VectorD* this);

extern double* VectorD_GetVector(VectorD* this);

extern double VectorD_GetElement(VectorD* this, int index);

extern VectorD* VectorD_SetElement(VectorD* this, int index, double value);

extern void VectorD_Show(VectorD* this);

extern VectorD* VectorD_Full(VectorD* this, double num);

extern VectorD* VectorD_Linspace(VectorD* this, double start, double end);

extern VectorD* VectorD_Copy(VectorD* this, VectorD* out_vector);

extern double VectorD_Max(VectorD* this);

extern double VectorD_Min(VectorD* this);

extern VectorD* VectorD_AddVectorD(VectorD* this, VectorD* in_vector, VectorD* out_vector);

extern VectorD* VectorD_SubVectorD(VectorD* this, VectorD* in_vector, VectorD* out_vector);

extern VectorD* VectorD_MulNumD(VectorD* this, double num, VectorD* out_vector);

extern double VectorD_MulVectorD(VectorD* this, VectorD* in_vector);

extern VectorD* VectorD_EMulVectorD(VectorD* this, VectorD* in_vector, VectorD* out_vector);

extern double VectorD_Norm(VectorD* this);

extern double VectorD_NormSq(VectorD* this);

#endif/*_VECTORD_H_*/
