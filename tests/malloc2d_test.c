#include <stdio.h>
#include <stdlib.h>

static void * malloc_2d(unsigned int rows, unsigned int columns, size_t size)
{
    void **ptr_array = malloc(sizeof(void *) * rows);
    if (ptr_array == NULL) {
        perror("malloc");
        return NULL;
    }

    void *data_array = malloc(rows * columns * size);
    if (data_array == NULL) {
        perror("malloc");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        ptr_array[i] = data_array + columns * size * i;
    }

    return ptr_array;
}

int main(void)
{
    double **test_array;
    int count = 0;

    test_array = malloc_2d(10, 5, sizeof(double));
    if (test_array == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int rows = 0; rows < 10; rows++) {
        for (int columns = 0; columns < 5; columns++) {
            test_array[rows][columns] = count++;
        }
    }

    printf("\n");
    for (int rows = 0; rows < 10; rows++) {
        for (int columns = 0; columns < 5; columns++) {
            printf("%2f ", test_array[rows][columns]);
        }
        printf("\n");
    }

    printf("Test completed succesfully.\n");
    exit(EXIT_SUCCESS);
}
