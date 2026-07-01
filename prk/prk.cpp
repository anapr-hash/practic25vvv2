#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 1000

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    printf("Текущая папка: %s\n\n", buffer);

    // Открытие CSV-файла
    FILE* input = fopen("input.csv", "r");

    if (input == NULL)
    {
        printf("Ошибка: не удалось открыть файл input.csv\n");
        return 1;
    }

    // Чтение данных в массив
    int arr[MAX_SIZE];
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

    // Вывод считанных данных
    printf("Файл успешно прочитан.\n");

    return 0;
}