#include <stdio.h>
#include <stdlib.h>
#include <climits>

class matrix
{
    // TODO: Write a matrix class with three private fields:
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

    // TODO: Write set_elem and get get_elem functions. Must check for invalid indices.
    //  Use zreo-based indexing!

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

    // TODO: Write a print function.

    int get_elem(int i, int j)
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

    // TODO: Write an add function. Must check for invalid dimensions.
    void add(matrix B)
    {
        if (num_rows != B.num_rows || num_cols != B.num_cols)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            for (int i = 0; i < num_rows; i++)
            {
                for (int j = 0; j < num_cols; j++)
                {
                    set_elem(i, j, get_elem(i, j) + B.get_elem(i, j));
                }
            }
        }
    }

    // TODO: Write a constructor, which takes three arguments: nrow, ncol, and elem.
    //  Must check nrow and ncol are positive integers. If they are not, print "invalid dimensions!" and do nothing.
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

    // print out
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

void read_image(int image[])
{
    FILE *in = fopen("surprise.dat", "rb");
    int count = 0;
    unsigned char b = fgetc(in);
    while (!feof(in))
    {
        image[count] = b;
        b = fgetc(in);
        count++;
    }
    fclose(in);
}

class image: public matrix
{

public:
    image(int height, int weight, int *data): matrix(height, weight)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < weight; j++)
            {
                set_elem(i, j, data[i * weight + j]);
            }
        }
    }

    void show(){
    //See lab 7, how images are stored in computers
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/lecs/lec8.pdf
    for(int i = 0; i < get_num_rows(); i++){
        for(int j = 0; j < get_num_cols(); j++){
            if( get_elem(i,j) < 85){
                printf(" ");
            }
            else if(get_elem(i,j) <170){
                printf("I");
            }else{
                printf("M");
            }
        }
        printf("\n");
    }
    }

};

int main()
{
    // testing code for the matrix class.
    
    int HEIGHT = 45; 
    int WIDTH = 44;
    int *data = (int *)malloc(HEIGHT * WIDTH * sizeof(int));

    read_image(data);
    image img(HEIGHT, WIDTH, data);
    img.show();

    free(data);
}
