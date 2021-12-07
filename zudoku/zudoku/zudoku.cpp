#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief vytiskne sudoku na standartní výstup
 *
 * @param arr
 */
void printSudoku(int arr[10][10])
{

    fprintf(stdout, "   123456789\n");
    for (int i = 0; i < 9; i++)
    {
        fprintf(stdout, "%d: ", i + 1);
        for (int j = 0; j < 9; j++)
        {
            if (arr[i][j] == 0)
            {
                fprintf(stdout, " ");
            }
            else
            {
                fprintf(stdout, "%d", arr[i][j]);
            }
        }
        fprintf(stdout, "\n");
    }
}
/**
 * @brief Kontroluje jestli v kazdym radku jsou jenom ruzne cislice
 *
 * @param arr
 * @return int
 *  @retval 0 NE
 *  @retval 1 ANO
 */
int rowsOk(int arr[10][10])
{

    for (int i = 0; i < 9; i++)
    {
        int checkArr[10] = { 0 };
        for (int j = 0; j < 9; j++)
        {
            //pokud je 0, tak preskoc
            if (arr[i][j] == 0)
            {
                continue;
            }
            if (checkArr[arr[i][j]] == 1)//pokud je 1, znamena to, ze toto cislo tam uz bylo, tak tedy vrat 0
            {
                return 0;
            }
            else
            {
                checkArr[arr[i][j]] = 1;
            }
        }
    }
    return 1;
}

/**
 * @brief Kontroluje jestli v kazdym ctverci jsou jenom ruzne cislice
 *
 * @param arr
 * @return int
 *  @retval 0 NE
 *  @retval 1 ANO
 */
int squaresOk(int arr[10][10]) //funkce kontroly čtvercu
{

    for (int k = 0; k < 9; k += 3)
    {

        for (int l = 0; l < 9; l += 3)
        {

            int checkArr[10] = { 0 };
            for (int i = k; i < 3; i++)
            {

                for (int j = l; j < 3; j++)
                {
                    if (arr[i][j] == 0)
                    {
                        continue;
                    }
                    if (checkArr[arr[i][j]] == 1)
                    {
                        return 0;
                    }
                    else
                    {
                        checkArr[arr[i][j]] = 1;
                    }
                }
            }
        }
    }
    return 1;
}

/**
 * @brief Kontroluje jestli v kazdym sloupci jsou jenom ruzne cislice
 *
 * @param arr
 * @return int
 *  @retval 0 NE
 *  @retval 1 ANO
 */
int collumnsOk(int arr[10][10])
{

    for (int i = 0; i < 9; i++)
    {
        int checkArr[10] = { 0 };
        for (int j = 0; j < 9; j++)
        {
            if (arr[j][i] == 0)
            {
                continue;
            }

            if (checkArr[arr[j][i]] == 1)
            {
                return 0;
            }
            else
            {
                checkArr[arr[j][i]] = 1;
            }
        }
    }
    return 1;
}

int main(int argc, char** argv)
{



    //otevre soubor
    FILE* fp = fopen("sudoku.txt", "r");

    //deklarace pole a jeho nulovani
    int arr[10][10] = { 0 };

    int y = 0;
    int x = 0;
    char c;

    //nacteni dat ze souboru
    //nacita znak po znaku
    for (; (c = fgetc(fp)) != EOF; y++)
    {
        //pokud je znak znakem novyho radku, zance se ukladat na dalsi radek pole
        if (c == '\n')
        {
            x++;
            y = -1; //-1 protoze by se pri dalsim pruchodu zvedlo o 1, a my potrebujeme v dalsim cyklu aby to bylo 0
            continue;
        }

        if (x > 9 || y > 9)
        {
            break;
        }
        //ulozi cislo na spravne misto v poli (prevod znaku na cislo(c - '0'))
        arr[x][y] = c - '0';
    }

    int row = 0;
    int collumn = 0;
    int number = 0;
    int err = 0;
    while (1)
    {
        //vycisteni prikazoviho radku
        system("cls");
        //vytiskne pole
        printSudoku(arr);
        //pokud se zadaly neplatne souradnice tak vypis chybu
        if (err)
        {
            printf("Cislo nemuze byt na teto pozici.\n");
        }

        //nulovani a nasledne nacteni promenych
        row = 0;
        collumn = 0;
        number = 0;
        printf("zadejte cislo radku");
        scanf("%d", &row);
        printf("zadejte cislo sloupce: ");
        scanf("%d", &collumn);
        printf("zadejte cislo co chcete umistit na tento radek: ");
        scanf("%d", &number);

        //pokud uzivatel zada nespravne cislo na nespravne misto, neuloz ho do pole, a napis mu chybu
        int temp = arr[row - 1][collumn - 1];
        arr[row - 1][collumn - 1] = number;
        if (!collumnsOk(arr) || !rowsOk(arr) || !squaresOk(arr))
        {
            err = 1;
            arr[row - 1][collumn - 1] = temp;
        }
    }
    return 0;
}