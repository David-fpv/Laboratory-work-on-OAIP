/* 10 лабораторная работа по ОАИП
Данная программ решает СЛАУ
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом*/


//number_of_variables + 1 - кол-во элементов в строке
#include <stdio.h>


void showMatrix(int size_matrix_n, int size_matrix_m, float matrix[size_matrix_n][size_matrix_m]);

int main()
{
    int number_of_equations = 0;
    printf("Enter number of equations\n");
    scanf("%d", &number_of_equations); // Ввод кол-ва уравнений в СЛАУ

    int number_of_variables = number_of_equations; // Для тестов, если так не будет то могут быть непредвиденные результаты
    //int number_of_variables = 0;
    /*printf("Enter number of variables\n"); 
    scanf("%d", &number_of_variables); // Ввод кол-ва переменных*/

    float array_of_unknowns[number_of_variables];
    float expanded_matrix[number_of_equations][number_of_variables+1];
    printf("Enter odds and answers\n"); // Ввод коэффициентов и ответов уравнений
    for (int i = 0; i < number_of_equations; i++)
    {
        printf("Enter Equation №%d\n", i+1);
        for (int j = 0; j < number_of_variables + 1; j++)
        {
            scanf("%f", &expanded_matrix[i][j]);
        }
    }

    showMatrix(number_of_equations, number_of_variables + 1, expanded_matrix);

    ///////////////////////////////////////////////////////////////////////////////////////
    // 1 шаг из 2 кода по решению СЛАУ

    for (int i = 0; i < number_of_equations; i++)
    {
        float divider = expanded_matrix[i][i]; // делитель элементов матрицы
        for (int j = i; j < number_of_variables + 1; j++)
        {
            expanded_matrix[i][j] /= divider;
        }

        for (int j = i + 1; j < number_of_equations; j++)
        {
            float quotient_factor = expanded_matrix[j][i]; // множитель частного
            for (int k = i; k < number_of_variables + 1; k++)
            {
                expanded_matrix[j][k] -= expanded_matrix[i][k] * quotient_factor;    
            }
        }
    }

    showMatrix(number_of_equations, number_of_variables + 1, expanded_matrix);


    // 2 шаг из 2 кода по решению СЛАУ

    for (int i = number_of_equations - 1; i >= 0; i--)
    {
        array_of_unknowns[i] = expanded_matrix[i][number_of_variables + 1 - 1];
        for (int j = number_of_variables + 1 - 2; j > i; j--)
        {
            array_of_unknowns[i] -= expanded_matrix[i][j] * array_of_unknowns[j];
        }
    }


    // вывод неизвестных

    for (int i = 0; i < number_of_variables; i++)
    {
        printf(" %.4f ", array_of_unknowns[i]);
    }

    ////////////////////////////////////////////////////////////////////////////////////////

    return 0;


}

void showMatrix(int size_matrix_n, int size_matrix_m, float matrix[size_matrix_n][size_matrix_m]) // нормально не получается отправить двумерный массив в функцию, как это правильно делать?
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