#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <utility>

class matrix
{
    //   num_rows: integer, stores the number of rows
    //   num_cols: integer, stores the number of columns
    //   elements: integer pointer, pointing to a contiguous memory stores a row-major matrix.

    int num_rows;
    int num_cols;
    int *elements;

    // all functions below must be PUBLIC!
public:

    int get_num_rows() { return num_rows; }
    int get_num_cols() { return num_cols; }

    void set_elem(int i, int j, int value)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
        }
        else
        {
            elements[i * num_cols + j] = value;
        }
    }

    int get_elem(int i, int j) const
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
            return INT_MAX;
        }
        else
        {
            return elements[i * num_cols + j];
        }
    }

    matrix(int nrow, int ncol)
    {
        if (nrow <= 0 || ncol <= 0)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            num_rows = nrow;
            num_cols = ncol;
            printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(int));
        }
    }

    ~matrix()
    {
        printf("freeing the matrix...\n");
        free(elements);
    }

    // print all elements in the matrix
    void print()
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                printf("%d ", get_elem(i, j));
            }
            printf("\n");
        }
    }

};

class symmmatrix: public matrix{

public:

    // TODO: Write a constructor that takes one argument for both dimensions of the matrix.

    // TODO: Rewrite set_elem function so that it preserves the symmetry of the matrix.


};

int main()
{
    // construct two different matrices, A and B.
    // A is a 2x3 matrix, B is a 3x3 symmetric matrix.
    matrix A(2, 3);
    symmmatrix B(3);

    // fill out some random values.
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            A.set_elem(i, j, rand() % 10);
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            B.set_elem(i, j, rand() % 10);
        }
    }

    // print out the matrices. 
    // Do they behave as expected?
    A.print();

    printf("------------------\n");

    B.print();
}
