/* 12 лабораторная работа по ОАИП
Выполнена студентом группы МС-12 ГГУ
Тарасенко Давидом
26.03.2023*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define capacity_array 100

typedef struct zap
{
    int key;          // будет храниться ключ
    int info;         // будет отображать номер, для тестов
    struct zap *next; // указатель на следующий элемент, для цепочки
}zap;

int getHashCode(int, int, double);

int maxKeyInStack();

void showHashStack();

//void showAllHashTablet();

int main()
{
    srand(time(NULL));
    double A = (sqrt(5) - 1) / 2; // значение A основано на свойствах золотого сечения; для хэф-функции
    
    int number_of_elements = 0;
    printf("Enter number of elements.\n");
    scanf("%d", &number_of_elements);

    zap data[number_of_elements];

    for (int i = 0; i < number_of_elements; i++) // заполнение структур
    {
        data[i].key = rand() % 1000;
        data[i].info = i;
        data[i].next = NULL;
    }

    struct zap *hash_table[capacity_array];
    for (int i = 0; i < capacity_array; i++) // зануление ссылок в хеш-таблице, без этого выдаёт ошибку
    {
        hash_table[i] = NULL;
    }

    for (int i = 0; i < number_of_elements; i++) // заполняем хеш-таблицу
    {
        int hash = getHashCode(data[i].key, capacity_array, A);

        if (hash_table[hash] == NULL)
        {
            hash_table[hash] = &data[i];
        }
        else
        {
            struct zap *data_j_link = hash_table[hash];
            hash_table[hash] = &data[i];
            data[i].next = data_j_link;
        }
    }


    int max_key_number; // для записи строки с наибольшим ключом
    int max_key;        // для записи ключа, для сравнений
    for (int i = 0; i < capacity_array; i++) // поиск первого элемента в хеш-таблице
    {
        if (hash_table[i] == NULL)
        {
            if (i + 1 >= capacity_array) // Если нету элементов в хеш-таблице
            {
                printf("There are no elements in the hash table.\n");
                return 0;
            } 
            continue;
        }
        else
        {
            max_key_number = i;
            max_key = maxKeyInStack(hash_table[i]);
            break;
        }
    }

    for (int i = max_key_number + 1; i < capacity_array; i++) // поиск номера стека с наибольшим ключом
    {
        if (hash_table[i] == NULL) // если нету элемента с хешем i
        {
            continue;
        }

        int i_max_key = maxKeyInStack(hash_table[i]);
        if (max_key < i_max_key)
        {
            max_key_number = i;
            max_key = i_max_key;
        }
    }

    printf("Answer: %d\n", max_key_number);
    
    //showAllHashTablet(capacity_array, hash_table);

    for (int i = 0; i < capacity_array; i++) // вывод хэш-таблицы
    {
        printf("%d. ", i);
        if (hash_table[i] != NULL) // если нету элемента с хешем i
        {
            showHashStack(hash_table[i]);
        }
        printf("\n");
    }

    return 0;
}


int getHashCode(int key, int N_, double A)
{
    double hash;
    modf(N_ * modf(A * key, &hash), &hash);
    return (int)hash;
    //return key % N_;
}

int maxKeyInStack(struct zap *place_in_table) // возвращает максимальный ключ из стека
{   
    if (place_in_table->next == NULL)
    {
        return place_in_table->key;
    }
    else
    {
        int other_key = maxKeyInStack(place_in_table->next);
        if (other_key > place_in_table->key)
        {
            return other_key;
        }
        else
        {
            return place_in_table->key;
        }
    }
}

void showHashStack(struct zap *place_in_table)
{
    printf("%d; ",  place_in_table->key);
    if (place_in_table->next != NULL)
    {
        showHashStack(place_in_table->next);
    }
}

/*void showAllHashTablet(int N_, struct zap *hash_table)
{
    for (int i = 0; i < N_; i++)
    {
        printf("%d. ", i);
        if ((hash_table + i) != NULL) // если нету элемента с хешем i
        {
            showHashStack(hash_table[i]);
        }
        printf("\n");
    }
}*/