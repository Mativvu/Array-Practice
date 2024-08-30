#include <stdio.h>
#include <assert.h>

#include "Matrix.h"

Elem_t matrix[5][5] = {
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 0, 1, 1, 1},
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1}
};

Elem_t mix[5][5] = {
    {0, -1,  0, -1,  0},
    {0,  0, -1,  0, -1},
    {1,  0,  0, -1,  0},
    {0,  1,  0,  0, -1},
    {1,  0,  1,  0,  0}
};

Elem_t mres[5][5] = {0};

int main()
{
    Matrix res;
    MatrixDynamicCtor(&res);

    //Triangle trig;
    //TriangleCtor(&trig, TrigPosRIGHT_TOP, 10);
    //TriangleFromSquare(&trig, &m1);
    //TrianglePrint(&trig, 5);

    //TornArr arr;
    //TornArrInput(arr);
    //TornArrFree(arr);

    Matrix m_d1;
    MatrixDynamicCtor(&m_d1);

    Matrix m_d2;
    MatrixDynamicCtor(&m_d2);

    MatrixInput(&m_d1);
    MatrixInput(&m_d2);

    MatrixMul(&m_d1, &m_d2, &res);
    MatrixPrint(&res);

    MatrixFree(&res);
    MatrixFree(&m_d1);
    MatrixFree(&m_d2);
    TriangleFree(&trig);
}

void MatrixStaticCtor(Matrix* m, size_t size_y, size_t size_x, Elem_t* matrix)
{
    assert(m != nullptr);

    m->size_y = size_y;
    m->size_x = size_x;
    m->data = matrix;
    m->is_dynamic = false;
}

void MatrixDynamicCtor(Matrix* m, size_t size_y, size_t size_x, Elem_t* matrix)
{
    assert(m != nullptr);

    if (size_x * size_y)
    {
        m->data = (int*)calloc(size_x * size_y, sizeof(Elem_t));
    }
    else
    {
        m->data = nullptr;
    }
    m->size_y = size_y;
    m->size_x = size_x;
    m->is_dynamic = true;
}

void MatrixPrint(const Matrix* m)
{
    assert(m->data != nullptr);

    for (size_t y = 0; y < m->size_y; y++)
    {
        for (size_t x = 0; x < m->size_x; x++)
        {
            size_t index = y * m->size_x + x;
            assert(index < m->size_y * m->size_x);
            printf("%d ", m->data[index]);
        }
        printf("\n");
    }
    printf("\n");
}

void MatrixTranspose(Matrix* m)
{
    assert(m != nullptr);
    assert(m->size_x == m->size_y);

    size_t size_arr = m->size_y * m->size_x;
    for (size_t y = 0; y < m->size_y; ++y)
    {
        for (size_t x = y; x < m->size_x; ++x)
        {
            size_t ind_top = y * m->size_y + x;
            size_t ind_bottom = x * m->size_y + y;

            assert(ind_bottom < size_arr);
            assert(ind_top < size_arr);

            Elem_t p = m->data[ind_top];
            m->data[ind_top] = m->data[ind_bottom];
            m->data[ind_bottom] = p;
        }
    }
}

// m2, m1 as result
// MatrixSum( m1, m2, m1);

// Matrix res;
// MatrixCtorDynamic(&res, m1.sizex, m1.sizey);
// MatrixSum(&m1, &m2, &res);
void MatrixSum(const Matrix* m1, const Matrix* m2, Matrix* res)
{
    assert(m1 != nullptr);
    assert(m2 != nullptr);
    assert(res != nullptr);
    assert(m1->size_x == m2->size_x);
    assert(m1->size_y == m2->size_y);
    assert(res->size_y == m1->size_y);
    assert(res->size_x == m1->size_x);

    size_t size_x = m1->size_x;
    size_t size_y = m1->size_y;

    for (size_t y = 0; y < size_y; ++y)
    {
        for (size_t x = 0; x < size_x; ++x)
        {
            size_t index = y * size_x + x;
            assert(index < size_x * size_y);

            res->data[index] = m1->data[index] + m2->data[index];
        }
    }
}

void TriangleCtor(Triangle* t, TrigPos pos, size_t size)
{
    assert(t != nullptr);

    t->pos = pos;
    t->size = size;
    t->data = (Elem_t*)calloc(size, sizeof(Elem_t));
}

void TriangleFromSquare(Triangle* t, const Matrix* m)
{
    assert(t != nullptr);
    assert(m != nullptr);

    size_t size_x = m->size_x;
    size_t size_y = m->size_y;

    size_t t_len = 0;
    for (size_t y = 0; y < size_y; ++y)
    {
        for (size_t x = 0; x < size_x && t_len < t->size; ++x)
        {
            size_t index = y * size_x + x;
            assert(t_len < t->size);
            assert(index < size_x * size_y);

            bool belong = 0;
            switch(t->pos)
            {
                case TrigPosLEFT_TOP:
                {
                    belong = (x < size_y - y - 1);
                    break;
                }
                case TrigPosLEFT_BOT:
                {
                    belong = (x < y);
                    break;
                }
                case TrigPosRIGHT_TOP:
                {
                    belong = (x > y);
                    break;
                }
                case TrigPosRIGHT_BOT:
                {
                    belong = (x > size_y - y - 1);
                    break;
                }
            }
            if (belong)
            {
                t->data[t_len++] = m->data[index];
            }
        }
    }
}

void TrianglePrint(const Triangle* t, size_t size)
{
    assert(t != nullptr);

    size_t index = 0;
    for (size_t y = 0; y < size; ++y)
    {
        for (size_t x = 0; x < size; ++x)
        {
            bool printed = false;
            switch(t->pos)
            {
                case TrigPosLEFT_TOP:
                {
                    printed = (x < size - y - 1);
                    break;
                }
                case TrigPosLEFT_BOT:
                {
                    printed = (x < y);
                    break;
                }
                case TrigPosRIGHT_TOP:
                {
                    printed = (x > y);
                    break;
                }
                case TrigPosRIGHT_BOT:
                {
                    printed = (x > size - y - 1);
                    break;
                }
            }
            if (printed)
            {
                printf("%d ", t->data[index++]);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MatrixInput(Matrix* m)
{
    assert(m != nullptr);

    MatrixFree(m);

    size_t size_x = 0, size_y = 0;
    scanf("%zu %zu", &size_y, &size_x);

    m->is_dynamic = true;
    m->size_x = size_x;
    m->size_y = size_y;
    m->data = (int*)calloc(size_x * size_y, sizeof(Elem_t));

    for (size_t y = 0; y < size_y; ++y)
    {
        for (size_t x = 0; x < size_x; ++x)
        {
            size_t index = y * size_x + x;
            assert(index < size_y * size_x);
            scanf("%d", &m->data[index]);
        }
    }
    printf("\n");
}

void MatrixFree(Matrix* m)
{
    if (m->is_dynamic && m->data != nullptr)
    {
        free(m->data);
        m->size_x = 0;
        m->size_y = 0;
        m->data = nullptr;
    }
}

void MatrixMul(const Matrix* m1, const Matrix* m2, Matrix* res)
{
    assert(m1 != nullptr);
    assert(m2 != nullptr);
    assert(res != nullptr);
    assert(m1->size_x == m2->size_y);

    MatrixFree(res);

    size_t size_x = m2->size_x;
    size_t size_y = m1->size_y;

    res->is_dynamic = true;
    res->size_x = size_x;
    res->size_y = size_y;
    res->data = (int*)calloc(size_x * size_y, sizeof(Elem_t));

    for (size_t y = 0; y < size_y; ++y)
    {
        for (size_t x = 0; x < size_x; ++x)
        {
            Elem_t vec_sum = 0;
            for (size_t g = 0; g < m1->size_x; ++g)
            {
                size_t m1_index = y * m1->size_x + g;
                size_t m2_index = g * m2->size_x + x;

                assert(m1_index < m1->size_x * m1->size_y);
                assert(m2_index < m2->size_x * m2->size_y);

                vec_sum += m1->data[m1_index] * m2->data[m2_index];
            }
            res->data[y * size_x + x] = vec_sum;
        }
    }
}

void TornArrInput(TornArr* arr)
{
    assert(torn_arr == nullptr);

    size_t arr->num_of_rows = 0;
    scanf("%zu", &arr->num_of_rows);

    size_t* arr->len_of_rows = (size_t*)calloc(arr->num_of_rows, sizeof(size_t));
    for (size_t i = 0; i < arr->num_of_rows; ++i)
    {
        scanf("%zu", &arr->len_of_rows[i]);
    }

    size_t* arr->row_len_bytes = (size_t*)calloc(arr->num_of_rows+1, sizeof(size_t));
    for (size_t i = 1; i < arr->num_of_rows+1; ++i)
    {
        arr->row_len_bytes[i] = arr->row_len_bytes[i-1] + sizeof(int) * arr->len_of_rows[i-1];
    }

    for (size_t i = 0; i < arr->num_of_rows; ++i)
    {
        size_t size = arr->len_of_rows[i];
        arr->data = (Elem_t*)realloc(arr->data, (arr->row_len_bytes[i] + size) * sizeof(Elem_t));

        for (size_t j = 0; j < size; ++j)
        {
            scanf("%d", &arr->data[arr->row_len_bytes[i] + j]);
        }
    }
    printf("\n");
}

void TornArrPrint(const TornArr* arr)
{
    assert(arr != nullptr);

    for (size_t i = 0; i < arr->num_of_rows; ++i)
    {
        for (size_t j = 0; j < arr->len_of_rows[i]; ++j)
        {
            printf("%d ", *(arr->data + arr->row_len_bytes[i] + j));
        }
        printf("\n");
    }
}

void TornArrFree(TornArr* arr)
{
    free(arr->len_of_rows);
    arr->len_of_rows = nullptr;
    free(arr->row_len_bytes);
    arr->row_len_bytes = nullptr;
    free(arr->data);
    arr->data = nullptr;
}

