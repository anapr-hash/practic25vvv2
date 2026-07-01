int generateRandom(int arr[], int arr2[])
{

    int n;

    printf("¬ведите количество чисел (максимум %d): ", MAX_SIZE);

    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)

    {

        printf("ќшибка: неверное количество.\n");

        return 0;

    }

    int min, max;

    printf("¬ведите минимальное значение: ");

    scanf("%d", &min);

    printf("¬ведите максимальное значение: ");

    scanf("%d", &max);

    if (min >= max)

    {

        printf("ќшибка: минимум должен быть меньше максимума.\n");

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