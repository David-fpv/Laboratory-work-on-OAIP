/* 9_2 лабораторная работа по ОАИП
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
Последняя правка 21.03.2023*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int size_database = 0;     // кол-во клиентов
unsigned int max_size_database = 0; // макс возможное кол-во аккаунтов на данный момент

struct bank_client
{
    char fio[30];                 // фио клиента
    char bank_account_number[30]; // номер счёта
    char amount_on_account[30];   // сумма на счёте
    char date[30];                // дата
};

int entering_structures();

int add_client();

int show_all_clients();

int show_client();

int swap_clients();

int sort_relative_fio();

int relative_bank_account_number();

int sort_relative_amount_on_account();

int sort_relative_date();

int sort_clients();

int search_something();

int change_customer_information();

int delete_client_information();

int custom_menu();

int record_information_from_files();

int save_information_in_file();

int main()
{
    struct bank_client *database;       // ссылка на выделенную память для структур
    //static unsigned int size_database = 0;     // кол-ва клиентов
    //static unsigned int max_size_database = 0; // макс возможное кол-во аккаунтов на данный момент
    unsigned int size_struct = sizeof(struct bank_client); // для хранения размера структуры

    if(!(database=(struct bank_client*)calloc(100, sizeof(struct bank_client))))
    {
        printf("Not enough memory\n");
    } 
    else
    {
        max_size_database += 5;
    }

    custom_menu(database, &size_database, &max_size_database);

    free(database);
    return 0;
}



int entering_structures(struct bank_client *ptr)
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
    int flag = 1;
    while(flag)
    {
        flag = add_client(ptr);
    }
}

int add_client(struct bank_client *ptr/*, unsigned int *size_database_ptr, unsigned int *max_size_database_ptr*/)
{
    //unsigned int size_database = *size_database_ptr;
    //unsigned int max_size_database = *max_size_database_ptr;

    char buffer[30] = {};
    char zero_string[2] = "0";

    if (size_database >= max_size_database)
    {
        if(!realloc(ptr, (max_size_database + 5) * sizeof(struct bank_client)))
        {
            printf("Not enough memory\n");
            return 0;
        }
        else
        {
            printf("Maximum number of clients increased by 5.\n");
            max_size_database += 5;
        }
    }

    printf("Enter FIO or 0 to exit\n");
    gets(buffer);
    if (!strcmp(buffer, zero_string))
    {
        return 0;
    }
    strcpy(ptr[size_database].fio, buffer);
    printf("Enter bank account number\n");
    gets(ptr[size_database].bank_account_number);
    printf("Enter amount on account\n");
    gets(ptr[size_database].amount_on_account);
    printf("Enter last modified date\n");
    gets(ptr[size_database].date);
    size_database++;
    //printf("New client added\n");
    return 1;
}

int show_client(struct bank_client *ptr, int size_database, int number)
{
    if (size_database > number)
    {
        printf("%s\n", ptr[number].fio);
        printf("%s\n", ptr[number].bank_account_number);
        printf("%s\n", ptr[number].amount_on_account);
        printf("%s\n", ptr[number].date);
        return 1;
    }
    else
    {
        printf("Such an account does not exist.");
        return 0;
    }
}

int show_all_clients(struct bank_client *ptr, int size_database)
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("Show accaounts\n");
    for (int i = 0; i < size_database; i++)
    {
        show_client(ptr, size_database, i);
        if (i + 1 != size_database)
        {
            printf("\n");
        }
    }
    return 1;
}

int swap_clients(struct bank_client *ptr, int a, int b)
{
    struct bank_client buffer;
    
    strcpy(buffer.fio, ptr[a].fio);
    strcpy(buffer.bank_account_number, ptr[a].bank_account_number);
    strcpy(buffer.amount_on_account, ptr[a].amount_on_account);
    strcpy(buffer.date, ptr[a].date);

    strcpy(ptr[a].fio, ptr[b].fio);
    strcpy(ptr[a].bank_account_number, ptr[b].bank_account_number);
    strcpy(ptr[a].amount_on_account, ptr[b].amount_on_account);
    strcpy(ptr[a].date, ptr[b].date);

    strcpy(ptr[b].fio, buffer.fio);
    strcpy(ptr[b].bank_account_number, buffer.bank_account_number);
    strcpy(ptr[b].amount_on_account, buffer.amount_on_account);
    strcpy(ptr[b].date, buffer.date);
}

int sort_relative_fio(struct bank_client *ptr, int size_database)
{
    unsigned int size_struct = sizeof(struct bank_client); 
    int max = 0;
    for (int i = 0; i < size_database; i++)
    {
        int max = i;
        for (int j = i; j < size_database; j++)
        {
            //if (strcmp(ptr + key_sort * 30 + i * size_struct, ptr + key_sort * 30 + i * size_struct)) // примерно универсальное условие
            if (strcmp(ptr[max].fio, ptr[j].fio) > 0) // при удалении универскального условия надо редактировать список параметров функции
            {
                max = j;
            }
        }
        swap_clients(ptr, i, max);
    }
}

int sort_relative_bank_account_number(struct bank_client *ptr, int size_database)
{
    unsigned int size_struct = sizeof(struct bank_client); 
    int max = 0;
    for (int i = 0; i < size_database; i++)
    {
        int max = i;
        for (int j = i; j < size_database; j++)
        {
            if (strcmp(ptr[max].bank_account_number, ptr[j].bank_account_number) > 0)
            {
                max = j;
            }
        }
        swap_clients(ptr, i, max);
    }
}

int sort_relative_amount_on_account(struct bank_client *ptr, int size_database)
{
    unsigned int size_struct = sizeof(struct bank_client); 
    int max = 0;
    for (int i = 0; i < size_database; i++)
    {
        int max = i;
        for (int j = i; j < size_database; j++)
        {
            if (atoi(ptr[max].amount_on_account) < atoi(ptr[j].amount_on_account)) // atoi преобразует строку в инт
            {
                max = j;
            }
        }
        swap_clients(ptr, i, max);
    }
}

int sort_relative_date(struct bank_client *ptr, int size_database)
{
    unsigned int size_struct = sizeof(struct bank_client); 
    int max = 0;
    for (int i = 0; i < size_database; i++)
    {
        int max = i;
        for (int j = i; j < size_database; j++)
        {
            if (strcmp(ptr[max].date, ptr[j].date) < 0)
            {
                max = j;
            }
        }
        swap_clients(ptr, i, max);
    }
}

int sort_clients(struct bank_client *ptr, int size_database) 
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");

    char char_of_command[3] = {};
    int number_of_command = 0;

    printf("What do you want to sort by?\n");
    printf("1. Sort relative to FIO.\n");
    printf("2. Sort relative to bank account number.\n");
    printf("3. Sort relative to amounts in the account.\n");
    printf("4. Sort relative to last modified date.\n");
    printf("0. Cancel. \n");
    gets(char_of_command);
    number_of_command = atoi(char_of_command);
    printf("\n");

    switch (number_of_command) 
    {
        case 1:
            sort_relative_fio(ptr, size_database);
            break;
                    
        case 2:
            sort_relative_bank_account_number(ptr, size_database);
            break;

        case 3:
            sort_relative_amount_on_account(ptr, size_database);
            break;

        case 4:
            sort_relative_date(ptr, size_database);
            break;
                
        case 0:
            return 1;

        default:
            printf("No such command found.\n");
            return 0;
    }
}

int search_something(struct bank_client *ptr, int size_database)
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");

    char buffer[30] = {};
    printf("Enter what you want to find.\n");
    gets(buffer);

    int flag = 0;
    for (int i = 0; i < size_database; i++)
    {
        if (!strcmp(buffer, ptr[i].fio)) flag = 1;
        if (!strcmp(buffer, ptr[i].bank_account_number)) flag = 1;
        if (!strcmp(buffer, ptr[i].amount_on_account)) flag = 1;
        if (!strcmp(buffer, ptr[i].date)) flag = 1;
        
        if (flag)
        {
            show_client(ptr, size_database, i);
            printf("\n");
            flag = 0;
        }
    }
}

int change_customer_information(struct bank_client *ptr, int size_database)
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");

    char char_of_command[3] = {};
    int number = 0;

    printf("Enter the number of the record to be edited.\n");
    gets(char_of_command);
    number = atoi(char_of_command) - 1; // -1 нужен для перевода человеческого отсчёта с 1, к машинному от 0

    if (size_database > number)
    {
        int number_of_command = 0;
        char buffer[30] = {};

        while(1)
        {
            printf("What do you want to change?\n");
            printf("1. FIO.\n");
            printf("2. Bank account number.\n");
            printf("3. Amount on account.\n");
            printf("4. Date.\n");
            printf("0. Exit.\n");
            int number_of_command = 1;
            gets(char_of_command);
            number_of_command = atoi(char_of_command);
            printf("\n");

            switch (number_of_command)
            {
            case 1:
                printf("Enter a new FIO.\n");
                gets(buffer);
                strcpy(ptr[number].fio, buffer);
                break;

            case 2:
                printf("Enter a new bank account number.\n");
                gets(buffer);
                strcpy(ptr[number].bank_account_number, buffer);
                break;

            case 3:
                printf("Enter a new amount on account.\n");
                gets(buffer);
                strcpy(ptr[number].amount_on_account, buffer);
                break;

            case 4:
                printf("Enter a new date.\n");
                gets(buffer);
                strcpy(ptr[number].date, buffer);
                break;

            case 0:
                return 1;
                break;
            
            default:
                break;
            }
        }
    }
    else
    {
        printf("Such an account does not exist.");
        return 0;
    }
}

int delete_client_information(struct bank_client *ptr/*, unsigned *size_database, unsigned int *max_size_database*/)
{
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");

    char char_of_command[3] = {};
    int number = 0;

    printf("Enter the number of the record to be deleted.\n");
    gets(char_of_command);
    number = atoi(char_of_command) - 1; // -1 нужен для перевода человеческого отсчёта с 1, к машинному от 0

    if (size_database > number)
    {
        for (int i = number; i < size_database - 1; i++)
        {
            strcpy(ptr[i].fio, ptr[i + 1].fio);
            strcpy(ptr[i].bank_account_number, ptr[i + 1].bank_account_number);
            strcpy(ptr[i].amount_on_account, ptr[i + 1].amount_on_account);
            strcpy(ptr[i].date, ptr[i + 1].date);
        }

        strcpy(ptr[size_database - 1].fio, "");
        strcpy(ptr[size_database - 1].bank_account_number, "");
        strcpy(ptr[size_database - 1].amount_on_account, "");
        strcpy(ptr[size_database - 1].date, "");

        size_database--;

        if(size_database + 5 < max_size_database) // может быть баг из-за 5
        {
            if(!realloc(ptr, (max_size_database - 5) * sizeof(struct bank_client)))
            {
                printf("Memory shrink error.\n");
                return 0;
            }
            else
            {
                printf("The maximum number of clients has been reduced by 5.\n");
                max_size_database -= 5;
            }
        }
        return 1;

    }
    else
    {
        printf("Such an account does not exist.");
        return 0;
    }
}

int custom_menu(struct bank_client *ptr, unsigned int *size_database, unsigned int *max_size_database)
{
    char char_of_command[3] = {};
    int number_of_command = 0;
    while(1)
    {
        printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
        printf("What do you want to do?\n");
        printf("1. Adding customer records.\n");
        printf("2. Sorting.\n");
        printf("3. Search.\n");
        printf("4. Changing customer data.\n");
        printf("5. Deleting a customer record.\n");
        printf("6. Data output of all clients.\n");
        printf("7. Loading data from a file.\n");
        printf("8. Saving data to a file.\n");
        printf("0. Exit.\n");

        gets(char_of_command);
        number_of_command = atoi(char_of_command);
        
        switch (number_of_command)
        {
        case 1:
            entering_structures(ptr);
            break;

        case 2:
            sort_clients(ptr, *size_database);
            break;
            
        case 3:
            search_something(ptr, *size_database);
            break;
            
        case 4:
            change_customer_information(ptr, *size_database);
            break;
            
        case 5:
            delete_client_information(ptr);
            break;
            
        case 6:
            show_all_clients(ptr, *size_database);
            break;
            
            
        case 7:
            record_information_from_files(ptr/*, size_database, max_size_database*/);
            break;
            
            
        case 8:
            save_information_in_file(ptr/*, size_database, max_size_database*/);
            break;
            
        case 0:
            return 1;
            break;
        
        default:
            break;
        }
    }
}

int record_information_from_files(struct bank_client *ptr/*, unsigned *size_database, unsigned int *max_size_database*/)
{
    FILE *F1;
    if(!(F1=fopen("F1.bat", "rb")))
    {
        printf("Problem opening file F1.\n");
        return 0;
    }
    
    while (!feof(F1))
    {
        if (size_database >= max_size_database)
        {
            if(!realloc(ptr, (max_size_database + 5) * sizeof(struct bank_client)))
            {
                printf("Not enough memory\n");
                return 0;
            }
            else
            {
                printf("Maximum number of clients increased by 5.\n");
                max_size_database += 5;
            }
        }
        fread((ptr + size_database), 120, 1, F1);
        size_database++;
    }
    size_database--; // Из-за того что в feof проскакивает лишние срабатывание

    fclose(F1);
    return 1;
}

int save_information_in_file(struct bank_client *ptr/*, unsigned *size_database, unsigned int *max_size_database*/)
{
    FILE *F2;
    
    if(!(F2=fopen("F1.bat", "w+b")))
    {
        printf("Problem opening file F1.\n");
        return 0;
    }

    for (int i = 0; i < size_database; i++)
    {
        fwrite((ptr + i), 120, 1, F2);
    }

    fclose(F2);
    return 1;
}

