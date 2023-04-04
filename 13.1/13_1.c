/* 13 лабораторная работа по ОАИП
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
24.03.2023*/

#include <stdio.h>
#include <stdlib.h>

int *mergeSort();

int sortingTest();

int main()
{
    int array_a[5] = {1, 5, 7, 123, 124};
    int array_b[5] = {2, 3, 122, 124, 125};
    int *array_c = mergeSort(5, array_a, 5, array_b);

    sortingTest(10, array_c);
    
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array_c[i]);
    }
}

int *mergeSort(int size_array_a, int *array_a, int size_array_b, int *array_b)
{
    int count_a = 0;
    int count_b = 0;
    int *array_c;
    if(!(array_c = (int*)calloc(size_array_a + size_array_b, sizeof(int))))
    {
        printf("Error memory.\n");
    }

    for (int i = 0; i < size_array_a + size_array_b; i++)
    {
        if ((count_a < size_array_a) && ((array_a[count_a] <= array_b[count_b]) || (count_b >= size_array_b)))
        {
            array_c[i] = array_a[count_a];
            count_a++;
        }
        else
        {
            array_c[i] = array_b[count_b];
            count_b++;
        }
    }
    return array_c;
}

int sortingTest(int size_array, int *array)
{
    for (int i = 0; i < size_array - 1; i++)
    {
        if (array[i] > array[i+1])
        {   
            printf("Sorting failed.\n");
            return 0;
        }
    }
    printf("Sorting was successful.\n");
    return 1;
}

