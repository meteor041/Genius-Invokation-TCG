#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// #include "characters.h"

int a_dices[8];
int b_dices[8];

void roll_dice(int dices[8])
{
    int randomNumber;
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        randomNumber = (int)rand() % 8;
        dices[randomNumber] += 1;
    }
}

void show_dices(int dices[8])
{
    printf("dices: \n");
    for (int j = 0; j < 8; j++)
    {
        if (j == 4)
            putchar('\n');
        switch (j)
        {
        case 0:
            printf("Omni:   ");
            break;
        case 1:
            printf("Cryo: ");
            break;
        case 2:
            printf("Hydro:");
            break;
        case 3:
            printf("Pyro:  ");
            break;
        case 4:
            printf("Electro:");
            break;
        case 5:
            printf("Anemo:");
            break;
        case 6:
            printf("Geo:  ");
            break;
        case 7:
            printf("Dendro:");
            break;
        }
        printf("%d   ", dices[j]);
    }
    putchar('\n');
}

int dice_count(int element, int dices_needed, int dices[8])//i - skill
{
    if (dices[element] + dices[0] >= dices_needed)
        return 1;
    else
        return 0;
}