#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define size 45

typedef struct Car
{
    char brand[size];
    char model[size];
    int year;
    char board[8];
} Car;
int count = 0;
int numberOfCars = 0;
Car *car = NULL;

int main()
{
    expandArray(true);
    setlocale(LC_ALL, "Portuguese");
    char option;
    do
    {
        system("cls");
        printLine();
        printf("%ls\n", L" Opções:");
        printf("%ls\n", L" 1. Inserir um novo veículo");
        printf("%ls\n", L" 2. Listar os veículos cadastrados");
        printf("%ls\n", L" 3. Listar os veículos por ano de fabricação");
        printf("%ls\n", L" 4. Listar os veículos a partir do ano de fabricação");
        printf("%ls\n", L" 5. Listar os veículos pelo modelo");
        printf("%ls\n", L" 6. Sair");
        printf("%ls", L" Digite a opção desejada: ");
        scanf("%c", &option);
        setbuf(stdin, NULL);
        system("cls");
        switch (option)
        {
        case '1':
            create();
            break;
        case '2':
            list();
            break;
        case '3':
            listByYear();
            break;
        case '4':
            listAboveYear();
            break;
        case '5':
            listByModel();
            break;
        default:
            break;
        }
    } while (option != '6');
    free(car);
    return 0;
}

void expandArray(int start)
{
    numberOfCars += 10;
    if (start == true)
    {
        car = malloc(numberOfCars * sizeof(Car));
    }
    else
    {
        car = realloc(car, numberOfCars * sizeof(Car));
    }
    if (car == NULL)
    {
        printf(" Memory allocation error!!!\n");
        exit(1);
    }
    return;
}

void printLine()
{
    char list[size];
    for (int i = 0; i < size; i++)
    {
        list[i] = '=';
    }
    printf("%s\n", list);
    return;
}

void getYear()
{
    int temp;
    do
    {
        scanf("%i", &temp);
        setbuf(stdin, NULL);
        temp < 1886 ? printf("%ls\n", L" Não existiam carros nesta época!") : 0;
    } while (temp < 1886);
    car[count].year = temp;
    return;
}

void getBoard()
{
    char temp;
    for (int i = 0; i < 8; i++)
    {
        if (i == 3)
        {
            car[count].board[i] = '-';
            continue;
        }
        printf(" Digite a %i %ls da placa: ", (i < 3 ? i + 1 : i - 3), (i < 3 ? L"letra" : L"número"));
        scanf("%c", &temp);
        setbuf(stdin, NULL);
        if ((i < 3 && isdigit(temp) == 0) || (i > 3 && isdigit(temp) != 0))
        {
            car[count].board[i] = toupper(temp);
        }
        else
        {
            i--;
            printf("%ls\n", L" Use o formato ABC-1234!");
        }
    }
    car[count].board[8] ='\0';
    return;
}

void create()
{
    if (count < numberOfCars)
    {
        char option;
        printf("%ls", L" Digite a marca do veículo: ");
        scanf("%s", &car[count].brand);
        setbuf(stdin, NULL);
        printf("%ls", L" Digite o modelo do veículo: ");
        scanf("%s", &car[count].model);
        setbuf(stdin, NULL);
        printf("%ls", L" Digite o ano do veículo: ");
        getYear();
        printf("%ls\n", L" Digite a placa do veículo no o formato ABC-1234: ");
        getBoard();
        count++;
        printf("%ls", L" Deseja cadastrar mais veículos (S/N)? ");
        scanf("%c", &option);
        setbuf(stdin, NULL);
        if (tolower(option) == 's')
        {
            system("cls");
            create();
        }
    }
    else
    {
        expandArray(false);
        create();
    }
    return;
}

void printCar(i)
{
    printLine();
    printf("%ls %s\n", L" Marca do veículo:", car[i].brand);
    printf("%ls %s\n", L" Modelo do veículo:", car[i].model);
    printf("%ls %i\n", L" Ano do veículo:", car[i].year);
    printf("%ls %s\n\n", L" Placa do veículo:", car[i].board);
    return;
}

void list()
{
    for (int i = 0; i < count; i++)
    {
        printCar(i);
    }
    if (count == 0)
    {
        printf("%ls\n\n", L" Não há veículos cadastrados!");
    }
    system("pause");
    return;
}

void listByYear()
{
    int get = 0;
    int year;
    printf("%ls", L" Qual ano de pesquisa: ");
    scanf("%i", &year);
    setbuf(stdin, NULL);
    system("cls");
    for (int i = 0; i < count; i++)
    {
        if (car[i].year == year)
        {
            get++;
            printCar(i);
        }
    }
    if (get == 0)
    {
        printf("%ls %i!\n\n", L" Não foram encontrados veículos do ano", year);
    }

    system("pause");
    return;
}

void listAboveYear()
{
    int get = 0;
    int year;
    printf("%ls", L" Qual ano inicial de pesquisa: ");
    scanf("%i", &year);
    setbuf(stdin, NULL);
    system("cls");
    for (int i = 0; i < count; i++)
    {
        if (car[i].year >= year)
        {
            get++;
            printCar(i);
        }
    }
    if (get == 0)
    {
        printf("%ls %i!\n\n", L" Não foram encontrados veículos com ano maior ou igual que", year);
    }
    system("pause");
    return;
}

void listByModel()
{
    int get = 0;
    char model[size];
    printf("%ls", L" Qual o modelo de pesquisa: ");
    scanf("%s", &model);
    setbuf(stdin, NULL);
    system("cls");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(strlwr(car[i].model), strlwr(model)) == 0)
        {
            get++;
            printCar(i);
        }
    }
    if (get == 0)
    {
        printf("%ls %s!\n\n", L" Não foram encontrados veículos do modelo", model);
    }
    system("pause");
    return;
}
