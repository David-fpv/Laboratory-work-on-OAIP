/* 8 лабораторная работа по ОАИП
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
Последняя правка 04.03.2023*/

#include <stdio.h>
#include <string.h>

struct bank_client
{
    char fio[30];                 // фио клиента
    char bank_account_number[30]; // номер счёта
    char amount_on_account[30];   // сумма на счёте
    char date[30];                // дата
};

struct bank_client *database;       // ссылка на выделенную память для структур
unsigned int size_database = 0;     // кол-ва клиентов
unsigned int max_size_database = 5; // макс возможное кол-во аккаунтов на данный момент
unsigned int size_struct = sizeof(struct bank_client); // для хранения размера структуры


int entering_Structures();

int add_client();

int show_all_clients();

int swap_clients();

int main()
{
    if(!(database=(struct bank_client*)calloc(5, sizeof(struct bank_client))))
    {
        printf("Not enough memory\n");
    } 

    entering_Structures(database);
    show_clients(database);
    free(database);
    return 0;
}

int entering_Structures(struct bank_client *ptr)
{
    int flag = 1;
    while(flag)
    {
        flag = add_client(ptr);
    }
}

int add_client(struct bank_client *ptr)
{
    char buffer[30] = {};
    char zero_string[30] = "0";

    if (size_database >= max_size_database)
    {
        if(!realloc(ptr, (max_size_database + 5) * size_struct))
        {
            printf("Not enough memory\n");
            return 0;
        }
    }

    printf("Enter FIO or 0 to exit\n");
    gets(buffer);
    if (!strcmp(buffer, zero_string))
    {
        return 0;
    }
    strcpy(database[size_database].fio, buffer);
    printf("Enter bank account number\n");
    gets(database[size_database].bank_account_number);
    printf("Enter amount on account\n");
    gets(database[size_database].amount_on_account);
    printf("Enter last modified date\n");
    gets(database[size_database].date);
    size_database++;
    //printf("New client added\n");
    return 1;
}

int show_all_clients(struct bank_client *ptr)
{
    printf("Show accaounts\n");
    for (int i = 0; i < size_database; i++)
    {
        printf("%s\n", database[i].fio);
        printf("%s\n", database[i].bank_account_number);
        printf("%s\n", database[i].amount_on_account);
        printf("%s\n", database[i].date);
        if (i + 1 != size_database)
        {
            printf("\n");
        }
    }
}

int swap_clients(struct bank_client *ptr, int a, int b)
{
    struct bank_client buffer;
    
}