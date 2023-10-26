#include <stdio.h>
#include <stdlib.h>

int **mat_alloc(int nrows, int ncols)
{

    int **mat = malloc(nrows * sizeof(int *));
    if (mat == NULL)
    {
        printf("ERROR allocating memory 1\n");
        exit(-1);
    }

    for (int i = 0; i < nrows; i++)
    {
        mat[i] = malloc(ncols * sizeof(int));
        if (mat[i] == NULL)
        {
            printf("ERROR allocating memory 2\n");
            exit(-1);
        }
    }

    return mat;
}

void mat_free(int **mat, int nrows, int ncols)
{
    if (mat == NULL)
        return;

    for (int i = 0; i < nrows; i++)
    {
        if (mat[i] != NULL)
        {
            free(mat[i]);
        }
    }
    free(mat);

    return;
}

void matmul(int **a, int **b, int **c, int r_a, int c_a, int r_b, int c_b)
{
    // assert (c_a==r_b)

    for (int i = 0; i < r_a; i++)
    {
        for (int j = 0; j < c_b; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < c_a; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}

void mat_init(int **a, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            a[i][j] = 0;
}

void mat_show(int **a, int rows, int cols)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d, ", a[i][j]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL)
    {
        printf("ERROR opening file %s\n", argv[1]);
        exit(-1);
    }

    int numrows_a = atoi(argv[1]);
    int numcols_a = atoi(argv[2]);
    int numrows_b = atoi(argv[3]);
    int numcols_b = atoi(argv[4]);

    // read a
    int **a = mat_alloc(numrows_a, numcols_a);
    for (int i = 0; i < numrows_a; i++)
        for (int j = 0; j < numcols_a; j++)
            scanf("%d ", &a[i][j]);

    mat_show(a, numrows_a, numcols_a);
    printf("\n");
    
    // read b
    int **b = mat_alloc(numrows_b, numcols_b);
    for (int i = 0; i < numrows_b; i++)
        for (int j = 0; j < numcols_b; j++)
            scanf("%d ", &b[i][j]);

    mat_show(b, numrows_b, numcols_b);
    printf("\n");

    // allocate memory for c
    int **c = mat_alloc(numrows_a, numcols_b);

    // do multiplication
    matmul(a, b, c, numrows_a, numcols_a, numrows_b, numcols_b);

    mat_show(c, numrows_a, numcols_b);
    printf("\n");

    // cleanup
    if (a)
        mat_free(a, numrows_a, numcols_a);
    if (b)
        mat_free(b, numrows_b, numcols_b);
    if (c)
        mat_free(c, numrows_a, numcols_b);
    return 0;
}