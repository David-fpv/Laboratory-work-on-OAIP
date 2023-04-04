/* 9 лабораторная работа по ОАИП
1 задание
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
Последняя правка 04.03.2023*/
#include <stdio.h>

int main()
{
    FILE *F1;
    FILE *F2;

    if(!(F1=fopen("F1.txt", "w+t")))
    {
        printf("Проблема с работой файла F1.\n");
        return 0;
    }

    for (int i = 1; i < 21; i++)
    {
        fprintf(F1, "%d\n", i * 1000 + i);
    }

    fclose(F1);
    if(!(F1=fopen("F1.txt", "r+t")))
    {
        printf("Проблема с работой файла F1.\n");
        return 0;
    }

    if(!(F2=fopen("F2.txt", "w+t")))
    {
        printf("Проблема с работой файла F2.\n");
        return 0;
    }

    int k = 0; // K для задания
    printf("Enter K\n");
    scanf("%d", &k);

    char buffer[50] = {};
    int count = 1;
    while(count < 1000)
    {
        if (count == k)
        {
            for (int i = 0; i < 5; i++)
            {
                fgets(buffer, 60, F1);
                fputs(buffer, F2);
            }
            printf("Finish.");
            fclose(F1);
            fclose(F2);
            return 0;
        }
        fgets(buffer, 60, F1);
        count++;
    }
}