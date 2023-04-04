/* 12 лабораторная работа по ОАИП
Данная программ решает СЛАУ
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
25.03.2023*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 100 // размер хеш-таблицы

int hash_function();

int main()
{
    //srand(time(NULL));

    int number_of_elements = 0;
    printf("Enter number of elements.\n");
    scanf("%d", &number_of_elements);

    return 0;
}

int hash_function(int key, int N_)
{
    return key / N_;
}