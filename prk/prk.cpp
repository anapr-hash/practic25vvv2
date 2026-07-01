#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <time.h>

#include <windows.h>

#define MAX_SIZE 1000

void selectionSort(int arr[], int n)

{

    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++)

    {

        minIndex = i;

        for (j = i + 1; j < n; j++)

        {

            if (arr[j] < arr[minIndex])

            {

                minIndex = j;

            }

        }

        temp = arr[i];

        arr[i] = arr[minIndex];

        arr[minIndex] = temp;

    }

}

int compare(const void* a, const void* b)

{

    return (*(int*)a - *(int*)b);

}

int main()

{

    SetConsoleCP(1251);

    SetConsoleOutputCP(1251);

    char buffer[MAX_PATH];

    GetCurrentDirectoryA(MAX_PATH, buffer);

    printf("Текущая папка: %s\n\n", buffer);

    FILE* input = fopen("C:\\Users\\aleon\\OneDrive\\Desktop\\2semestr\\practica\\pract\\pract\\input.csv", "r");

    if (input == NULL)

    {

        printf("Ошибка: не удалось открыть файл input.csv\n");

        return 1;

    }

    int arr[MAX_SIZE];

    int arr2[MAX_SIZE];

    int n = 0;

    while (1)

    {

        if (fscanf(input, "%d", &arr[n]) != 1)

        {

            if (feof(input))

                break;

            printf("Ошибка: некорректные данные во входном файле.\n");

            fclose(input);

            return 1;

        }

        arr2[n] = arr[n];

        n++;

        char c = fgetc(input);

        if (c == EOF)

            break;

        if (c != ',')

        {

            printf("Ошибка: неверный формат CSV.\n");

            fclose(input);

            return 1;

        }

    }

    fclose(input);

    clock_t start, end;

    double selectionTime, qsortTime;

    start = clock();

    selectionSort(arr, n);

    end = clock();

    selectionTime = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();

    qsort(arr2, n, sizeof(int), compare);

    end = clock();

    qsortTime = (double)(end - start) / CLOCKS_PER_SEC;

    FILE* output = fopen("output.csv", "w");

    if (output == NULL)

    {

        printf("Ошибка: не удалось создать output.csv\n");

        return 1;

    }

    for (int i = 0; i < n; i++)

    {

        fprintf(output, "%d", arr[i]);

        if (i != n - 1)

            fprintf(output, ",");

    }

    fclose(output);

    printf("Сортировка завершена успешно.\n");

    printf("Результат записан в output.csv\n\n");

    printf("Сравнение производительности:\n");

    printf("Сортировка выбором: %.8f сек.\n", selectionTime);

    printf("Стандартная qsort: %.8f сек.\n", qsortTime);

    if (selectionTime > qsortTime)

    {

        printf("Вывод: qsort работает быстрее сортировки выбором.\n");

    }

    else if (selectionTime < qsortTime)

    {

        printf("Вывод: сортировка выбором работает быстрее.\n");

    }

    else

    {

        printf("Вывод: время выполнения одинаковое.\n");

    }

    return 0;

}