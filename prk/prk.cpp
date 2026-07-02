#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h> 

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

void saveToFile(int arr[], int n, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Ошибка: не удалось создать %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d", arr[i]);
        if (i != n - 1)
            fprintf(file, ",");
    }
    fclose(file);
    printf("Данные сохранены в %s\n", filename);
}

int readFromFile(int arr[], int arr2[], const char* filename)
{
    FILE* input = fopen(filename, "r");
    if (input == NULL)
    {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }

    int n = 0;
    while (1)
    {
        if (fscanf(input, "%d", &arr[n]) != 1)
        {
            if (feof(input))
                break;
            printf("Ошибка: некорректные данные во входном файле.\n");
            fclose(input);
            return 0;
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
            return 0;
        }
    }
    fclose(input);
    return n;
}

int manualInput(int arr[], int arr2[])
{
    int n;
    printf("Введите количество чисел (максимум %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)
    {
        printf("Ошибка: неверное количество.\n");
        return 0;
    }

    printf("Введите %d чисел через пробел: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }

    saveToFile(arr, n, "input.csv");
    return n;
}

int generateRandom(int arr[], int arr2[])
{
    int n;
    printf("Введите количество чисел (максимум %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)
    {
        printf("Ошибка: неверное количество.\n");
        return 0;
    }

    int min, max;
    printf("Введите минимальное значение: ");
    scanf("%d", &min);
    printf("Введите максимальное значение: ");
    scanf("%d", &max);

    if (min >= max)
    {
        printf("Ошибка: минимум должен быть меньше максимума.\n");
        return 0;
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = min + rand() % (max - min + 1);
        arr2[i] = arr[i];
    }

    saveToFile(arr, n, "input.csv");
    return n;
}

void printMenu()
{
    printf("----------------------------------------------------\n");
    printf("                   ГЛАВНОЕ МЕНЮ                    \n");
    printf("----------------------------------------------------\n");
    printf("  1. Ручной ввод чисел                           \n");
    printf("  2. Генерация случайных чисел                   \n");
    printf("  3. Загрузить из файла input.csv               \n");
    printf("  4. Выполнить сортировку и сохранить результат \n");
    printf("  5. Показать текущие данные                    \n");
    printf("  0. Выход                                      \n");
    printf("----------------------------------------------------\n");
    printf("Выберите действие: ");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int arr[MAX_SIZE];
    int arr2[MAX_SIZE];
    int n = 0;
    int choice;

    while (1)
    {
        printMenu();
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 0:
            printf("Программа завершена.\n");
            return 0;

        case 1:
            printf("\n--- РУЧНОЙ ВВОД ЧИСЕЛ ---\n");
            n = manualInput(arr, arr2);
            if (n > 0)
                printf("Успешно введено %d чисел.\n", n);
            break;

        case 2:
            printf("\n--- ГЕНЕРАЦИЯ СЛУЧАЙНЫХ ЧИСЕЛ ---\n");
            n = generateRandom(arr, arr2);
            if (n > 0)
                printf("Успешно сгенерировано %d чисел.\n", n);
            break;

        case 3:
            printf("\n--- ЗАГРУЗКА ИЗ ФАЙЛА ---\n");
            n = readFromFile(arr, arr2, "input.csv");
            if (n > 0)
                printf("Успешно загружено %d чисел из input.csv.\n", n);
            break;

        case 4:
            printf("\n--- ВЫПОЛНЕНИЕ СОРТИРОВКИ ---\n");
            if (n < 2)
            {
                printf("Ошибка: недостаточно данных для сортировки (нужно минимум 2 числа).\n");
                printf("Сначала загрузите или введите данные.\n");
                break;
            }

            int original[MAX_SIZE];
            for (int i = 0; i < n; i++)
                original[i] = arr[i];
            clock_t start, end;
            double selectionTime, qsortTime;

            start = clock();
            selectionSort(arr, n);
            end = clock();
            selectionTime = (double)(end - start) / CLOCKS_PER_SEC;

            saveToFile(arr, n, "output_selection.csv");

            for (int i = 0; i < n; i++)
                arr2[i] = original[i];

            start = clock();
            qsort(arr2, n, sizeof(int), compare);
            end = clock();
            qsortTime = (double)(end - start) / CLOCKS_PER_SEC;

            saveToFile(arr2, n, "output_qsort.csv");

            printf("\n-----------------------------------------------------\n");
            printf("                   РЕЗУЛЬТАТЫ\n");
            printf("-------------------------------------------------------\n");
            printf("Сортировка выбором: %.8f сек.\n", selectionTime);
            printf("Стандартная qsort:  %.8f сек.\n", qsortTime);
            printf("-------------------------------------------------------\n");

            if (selectionTime > qsortTime)
                printf(" Вывод: qsort работает быстрее сортировки выбором.\n");
            else if (selectionTime < qsortTime)
                printf(" Вывод: сортировка выбором работает быстрее.\n");
            else
                printf(" Вывод: время выполнения одинаковое.\n");

            printf("------------------------------------------------------\n");
            printf("Результаты сохранены в:\n");
            printf("  - output_selection.csv (сортировка выбором)\n");
            printf("  - output_qsort.csv (стандартная qsort)\n");
            break;

        case 5:
            printf("\n--- ТЕКУЩИЕ ДАННЫЕ ---\n");
            if (n == 0)
            {
                printf("Данные не загружены.\n");
            }
            else
            {
                printf("Количество чисел: %d\n", n);
                printf("Числа: ");
                for (int i = 0; i < n; i++)
                {
                    printf("%d", arr[i]);
                    if (i != n - 1)
                        printf(", ");
                }
                printf("\n");
            }
            break;

        default:
            printf("Ошибка: неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}