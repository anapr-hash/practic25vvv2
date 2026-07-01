#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Сортировка выбором (из твоего кода)
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

int main()
{
    FILE* input = fopen("input.csv", "r");

    if (input == NULL)
    {
        printf("Ошибка: не удалось открыть файл\n");
        return 1;
    }

    int arr[MAX_SIZE];
    int n = 0;

    // 🔹 РЕАЛИЗАЦИЯ ЧТЕНИЯ CSV (твой код)
    while (1)
    {
        if (fscanf(input, "%d", &arr[n]) != 1)
        {
            if (feof(input))
                break;

            printf("Ошибка данных в файле\n");
            fclose(input);
            return 1;
        }

        n++;

        char c = fgetc(input);

        if (c == EOF)
            break;

        if (c != ',')
        {
            printf("Ошибка формата CSV\n");
            fclose(input);
            return 1;
        }
    }

    fclose(input);

    // 🔹 СОРТИРОВКА (добавлена к чтению)
    selectionSort(arr, n);

    // 🔹 вывод результата (чтобы видеть, что всё работает)
    printf("Отсортированный массив:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}