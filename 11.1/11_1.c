/* 11_1 лабораторная работа по ОАИП
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
Решение СЛАУ методом Гаусса-Зейделя
Последняя правка 21.03.2023*/

#include <stdio.h>
#include <math.h>

void showMatrix();

void swapLine();

int isMatrixConverges(); // тест на сходимость матрицы

int main()
{
    int number_of_equations = 0;
    printf("Enter number of equations\n");
    scanf("%d", &number_of_equations); // Ввод кол-ва уравнений в СЛАУ

    float array_of_unknowns[number_of_equations];
    float array_of_approximations[number_of_equations];
    float expanded_matrix[number_of_equations][number_of_equations + 1];

    printf("Enter odds and answers\n"); // Ввод матрицы
    for (int i = 0; i < number_of_equations; i++)
    {
        printf("Enter Equation №%d\n", i+1);
        for (int j = 0; j < number_of_equations + 1; j++)
        {
            scanf("%f", &expanded_matrix[i][j]);
        }
    }

    //showMatrix(number_of_equations, number_of_equations + 1, expanded_matrix);

    // Есть правило по которому нельзя это считать, но оно считает все ранво.
    for (int i = 0; i < number_of_equations; i++) // приводим матрицу в правильную форму
    {
        if (!isMatrixConverges(i, expanded_matrix[i], number_of_equations))
        {
            for (int j = i; j < number_of_equations; j++)
            {
                if(isMatrixConverges(i, expanded_matrix[j], number_of_equations))
                {
                    swapLine(expanded_matrix[i], expanded_matrix[j], number_of_equations + 1);
                    break;
                }
                else if (j + 1 == number_of_equations)
                {
                    printf("This matrix cannot be calculated by the method of simple iterations.\n");
                    return 0;
                }
            }
        }
    }
    
    //showMatrix(number_of_equations, number_of_equations + 1, expanded_matrix);

    for (int i = 0; i < number_of_equations; i++) // делим каждую строку в матрице на элемент этой строки, который стоит в главной диагонали
    {
        float divider = expanded_matrix[i][i];
        for (int j = 0; j < number_of_equations + 1; j++)
        {
        expanded_matrix[i][j] /= divider;
        }
    }

    //showMatrix(number_of_equations, number_of_equations + 1, expanded_matrix);

    for (int i = 0; i < number_of_equations; i++) // переписваем приближения в массивых неизвестынх, то есть в массив иксов
    {
        array_of_unknowns[i] = expanded_matrix[i][number_of_equations];
    }

    int flag = 1;
    do  //основная часть алгоритма
    {
        for (int i = 0; i < number_of_equations; i++) // нахождение приближений-неизвестных
        {
            float sum = expanded_matrix[i][number_of_equations];

            for (int j = 0; j < number_of_equations; j++)
            {
                if (i != j)
                {
                    float a = expanded_matrix[i][j];
                    float b = array_of_unknowns[j];
                    sum -= a * b;
                }
            }

            array_of_approximations[i] = array_of_unknowns[i];

            array_of_unknowns[i] = sum;
        }

        for (int i = 0; i < number_of_equations; i++) // проверка на погрешность
        {
            float error = (array_of_unknowns[i] - array_of_approximations[i]) / array_of_unknowns[i];
            if (error > 0.01)
            {
                break;
            }
            if (i + 1 == number_of_equations)
            {
                flag = 0;
            }
        }

        for (int i = 0; i < number_of_equations ; i++) // вывод промужеточных значений приближений-неизвестных
        {
            printf("%f   ", array_of_unknowns[i]);
        }
        printf("\n\n");

    } while(flag); 

    for (int i = 0; i < number_of_equations; i++)   // Вывод ответа
    {
        printf("%d. %f\n", i + 1, array_of_unknowns[i]);
    }

    return 0;
}

void showMatrix(int size_matrix_n, int size_matrix_m, float matrix[size_matrix_n][size_matrix_m])
{
    for (int i = 0; i < size_matrix_n; i++)
    {
        printf("\n");
        for (int j = 0; j < size_matrix_m; j++)
        {
            printf("%.4f ", matrix[i][j]);
        }
    }
    printf("\n\n");
}

void swapLine(float *array_line_1, float *array_line_2, int count)
{
    float buffer;

    for (int i = 0; i < count; i++)
    {
        buffer = array_line_1[i];
        array_line_1[i] = array_line_2[i];
        array_line_2[i] = buffer;
    }
}

int isMatrixConverges(int number, float *array, int count)
{
    float sum = 0;

    for (int i = 0; i < count; i++)
    {
        if (i != number)
        {
            sum += fabs(array[i]);
        }
    }

    if (fabs(array[number]) > sum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
