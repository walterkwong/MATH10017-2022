#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// the class below is copied from the previous assignment
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
            return 'N';
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
            // printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(double));
        }
    }

    ~matrix()
    {
        // printf("freeing the matrix...\n");
        free(elements);
    }
};

class Problem
{
    matrix A;
    double p[5];
    double p_old[5];

    // check if the stopping condition is satisfied
    int is_converged()
    {
        for (int i = 0; i < 5; i++)
        {
            if (fabs(p[i] - p_old[i]) > 1e-15)
                return 0;
        }
        return 1;
    }

    // print out the pagerank
    void print()
    {
        for (int i = 0; i < 5; i++)
            printf("%.2f ", p[i]);

        printf("\n");
    }

public:
    Problem() : A(5, 5)
    {
        // using the constructor to initialize the matrix
        double a[] = {0, 1, 1, 0, 0,
                      1, 0, 0, 0, 0,
                      0, 0, 0, 1, 1,
                      1, 1, 1, 0, 1,
                      1, 0, 1, 0, 0};

        // copying the values into the matrix
        for (int i = 0; i < 25; i++)
            A.set_elem(i / 5, i % 5, a[i]);

        // initialize the pagerank
        for (int i = 0; i < 5; i++)
        {
            p[i] = 1.0 / 5.0;
            p_old[i] = 999.0;
        }
    }

    void solve()
    {
        while (!is_converged())
        {
            // copy p to p_old,
            // so that we can check the stopping condition in the next iteration
            for (int i = 0; i < 5; i++)
                p_old[i] = p[i];

            // the iterative algorithm for calculating the pagerank
            double q[5];
            // update the pagerank
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (A.get_elem(j, i) == 1)
                        q[i] += p[j];
                }
            }

            // normalize the pagerank
            double sum = 0;
            for (int i = 0; i < 5; i++)
                sum += q[i];

            for (int i = 0; i < 5; i++)
                p[i] = q[i] / sum;
        }

        // print the final result
        print();
    }

};

int main()
{

    Problem p;
    p.solve();

    return 0;
}