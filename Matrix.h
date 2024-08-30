#ifndef MATRIX_H
#define MATRIX_H

typedef int Elem_t;

enum TrigPos
{
    TrigPosLEFT_TOP  = 0,
    TrigPosLEFT_BOT  = 1,
    TrigPosRIGHT_TOP = 2,
    TrigPosRIGHT_BOT = 3
};

struct Matrix {
    size_t size_x;
    size_t size_y;
    Elem_t* data;
    bool is_dynamic;
};

struct Triangle {
    TrigPos pos;
    size_t size;
    Elem_t* data;
};

struct TornArr {
    size_t num_of_rows;
    size_t* len_of_rows;
    size_t* row_len_bytes;
    Elem_t* data;
};

void TornArrInput(TornArr* arr);
void TornArrPrint(const TornArr* arr);
void TornArrFree(TornArr* arr);

void MatrixStaticCtor(Matrix* m, size_t size_y = 0, size_t size_x = 0,
                      Elem_t* matrix = nullptr);
void MatrixDynamicCtor(Matrix* m, size_t size_y = 0, size_t size_x = 0,
                       Elem_t* matrix = nullptr);
void MatrixPrint(const Matrix* m);
void MatrixTranspose(Matrix* m);
void MatrixSum(const Matrix* m1, const Matrix* m2, Matrix* res);
void MatrixMul(const Matrix* m1, const Matrix* m2, Matrix* res);
void MatrixInput(Matrix* m);
void MatrixFree(Matrix* m);

void TriangleFromSquare(Triangle* t, const Matrix* m);
void TriangleCtor(Triangle* t, TrigPos pos, size_t size);
void TrianglePrint(const Triangle *t, size_t size);

#endif
