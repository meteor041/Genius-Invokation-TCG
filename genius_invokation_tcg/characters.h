#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// #include "reaction.h"

#define NUM 3 // number of characters

int a_ch_num = 3, b_ch_num = 3; // 未倒下的角色数

typedef struct Character
{
    char name[20];
    int hp;
    int BP;
    int max_bp;
    int application; // 0-none,
    char sk_name[3][50];
    int dices_needed[3];
    int element;
    int shield;
    int status; // 0-none
    void (*sk1)(struct Character *, struct Character *, struct Character *, struct Character *, int);
    void (*sk2)(struct Character *, struct Character *, struct Character *, struct Character *, int);
    void (*sk3)(struct Character *, struct Character *, struct Character *, struct Character *, int);
} character;

character Diluc = {
    "Diluc",
    10,
    0,
    3,
    0, // application
    {"Tempered Sword", "Searing Onslaught", "Dawn"},
    {1, 3, 4},
    3, // pyro
    0, // shield = 0
    0, // status
};

character Kaeya = {
    "Kaeya",
    10,
    0, // bp initialized
    2, // max_bp
    0,
    {"Ceremonial Bladework", "Frostgnaw", "Glacial Waltz"},
    {1, 3, 4},
    1, // ice
    0, // shield
    0,
};

character Barbara = {
    "Barbara",
    10,
    0,
    3, // max_bp
    0, // application
    {"Whisper of Water", "Let the Show Begin", "Shining Miracle"},
    {1, 3, 3},
    2, // hydro
    0, // shield
    0, // status
};


// show element_application in string forms
char * application_int2str(int ele_application)
{
    char * str;
    switch (ele_application)
    {
        case 0:
            return "None";
            break;
        case 1:
            return "Cryo";
            break;
        case 2:
            return "Hydro";
            break;
        case 3:
            return "Pyro";
            break;
    }
    // return str;
}

// show characters's info
void show_ch(character a_ch, character b_ch)
{
    printf("A:%-20sB:%-20s\n", a_ch.name, b_ch.name);
    printf("HP:%-19dHP:%-19d\n", a_ch.hp, b_ch.hp);
    printf("BP:%-19dBP:%-19d\n", a_ch.BP, b_ch.BP);
    printf("Shield:%-15dShield:%-15d\n", a_ch.shield, b_ch.shield);
    printf("Application:%-10sApplication:%-10s\n", 
        application_int2str(a_ch.application), application_int2str(b_ch.application));
    // printf("Application:%-10dApplication:%-10d\n",a_ch.application, b_ch.application);
}

// show standby characters
void show_st_ch(character ch1, character ch2)
{
    printf("1:%-20s2:%-20s\n", ch1.name, ch2.name);
    printf("HP:%-19dHP:%-19d\n", ch1.hp, ch2.hp);
    printf("BP:%-19dBP:%-19d\n", ch1.BP, ch2.BP);
    printf("Shield:%-15dShield:%-15d\n", ch1.shield, ch2.shield);
    printf("Application:%-10sApplication:%-10s\n", 
        application_int2str(ch1.application), application_int2str(ch2.application));
}

int bp_count(character ch, int op)
{
    if (op == 3)
    {
        if (ch.BP < ch.max_bp)
        {
            return 0;
        }
    }
    return 1;
}

void load_sk(character *ch, void (*sk1_ptr)(struct Character *, struct Character *, struct Character *, struct Character *,int),
             void (*sk2_ptr)(struct Character *, struct Character *, struct Character *, struct Character *,int),
             void (*sk3_ptr)(struct Character *, struct Character *, struct Character *, struct Character *,int))
{
    (*ch).sk1 = sk1_ptr;
    (*ch).sk2 = sk2_ptr;
    (*ch).sk3 = sk3_ptr;
}


// characters fall down
int ch_fall_down(character * a_ch, character * b_ch, character * a_st_ch, character * b_st_ch)
{
    if ((*a_ch).hp <= 0)
    {
        printf("%s falls down\n", (*a_ch).name);
        a_ch_num--;


    //change party
        if (a_ch_num > 0)
        {
            show_st_ch((*a_st_ch), *(a_st_ch + 1));
            puts("enter the number before character to set him/her as active character");
            int change_choice;
            scanf("%d", &change_choice);
            while ((*(a_st_ch + change_choice - 1)).hp <= 0)
            {
                printf("%s has fallen down\n", (*(a_st_ch + change_choice - 1)).name);
                scanf("%d", &change_choice);
            }
            character temp = *a_ch;
            *a_ch = *(a_st_ch + change_choice - 1);
            *(a_st_ch + change_choice - 1) = temp;
        }
        else
        {
            printf("B player wins!\n");
            return 1; // 表示结束对局
        }

        printf("Set %s as active character\n", (*a_ch).name);
    }

    if ((*b_ch).hp <= 0)
    {
        printf("%s falls down\n", (*b_ch).name);
        b_ch_num--;


    //change party
        if (b_ch_num > 0)
        {
            show_st_ch((*b_st_ch), *(b_st_ch + 1));
            puts("enter the number before character to set him/her as active character");
            int change_choice;
            scanf("%d", &change_choice);
            while ((*(b_st_ch + change_choice - 1)).hp <= 0)
            {
                printf("%s has fallen down\n", (*(b_st_ch + change_choice - 1)).name);
                scanf("%d", &change_choice);
            }
            character temp = *b_ch;
            *b_ch = *(b_st_ch + change_choice - 1);
            *(b_st_ch + change_choice - 1) = temp;
        }
        else
        {
            printf("A player wins!\n");
            return 1; // 表示结束对局
        }

        printf("Set %s as active character\n", (*b_ch).name);
    }
    
    return 0;
}



// // Summons
// typedef struct Summon
// {
//     char name[30];
//     int duration;
//     int max_duration; // 最大存在回合
//     int side;
//     void (*effect)(character *, character *, character *, character *);
//     struct Summon *link;
// } summon;

// // summon summons[2][4];

// int summon_ct[2] = {0, 0}; // 0-A, 1-B

// // summon melody_loop = {
// //     "Melody Loop",
// //     2,
// //     2,
// //     // melody_loop_effect,
// // };

// summon *List = NULL;
// summon *r, *p;

// void create_summon(char * summon_name, int summon_duration, 
//         int summon_max_duration, int summon_side, 
//         void (*summon_effect)(character *, character *, character *, character *))
// {
//     p = (summon *)malloc(sizeof(summon));
//     strcpy(p->name, summon_name);
//     p->duration = summon_duration;
//     p->max_duration = summon_max_duration;
//     p->duration = summon_side;
//     p->effect = summon_effect;
//     if (List == NULL)
//     {
//         List = p;
//     }
//     else
//     {
//         r->link = p;
//     }
//     r = p;
//     r->link = NULL;
// }

// void melody_loop_effect(character *my_ch, character *rv_ch, 
//                         character *my_standby_ch, character *rv_standby_ch)
// {
//     printf("Barbara's melody loop takes effect!\n");
//     (*my_ch).hp += 1;
//     if ((*my_ch).hp > 10)
//         (*my_ch).hp = 10;

//     (*my_standby_ch).hp += 1;
//     if ((*my_standby_ch).hp > 10)
//         (*my_standby_ch).hp = 10;

//     (*(my_standby_ch + 1)).hp += 1;
//     if ((*(my_standby_ch+1)).hp > 10) // 后期制作中会有部分角色血量不为10,到时再改
//         (*(my_standby_ch+1)).hp = 10; // 防止治疗量溢出(反正没做海染套)

//     // hydro application
//     harmless_application(my_ch, 2); 

// }

// // void load_summon_effect(summon *my_summon, void (*effect_ptr)(character *, character *, character *, character *))
// // {
// //     (*my_summon).effect = effect_ptr;
// // }

// void del_summon(summon *del_summon)
// {
//     if (del_summon == List)
//     {
//         List = List->link;
//         free(del_summon);
//     }
//     else
//     {
//         summon *q = List;
//         while (q->link != del_summon && (q->link != NULL))
//         {
//             q = q->link;
//         }
//         q->link = del_summon->link;
//         free(del_summon);
//     }
// }

// void summon_take_effect(summon *list, character *a_ch, character *b_ch, 
//         character *a_st_ch, character *b_st_ch)
// {
//     summon * look_for = list;
//     while (look_for != NULL)
//     {
//         summon * q = look_for;
//         look_for->duration -= 1; // 使用次数-1
//         if (look_for->side == 0)// A
//             look_for->effect(a_ch, b_ch, a_st_ch, b_st_ch);
//         else // B
//             look_for->effect(b_ch, a_ch, b_st_ch, a_st_ch);

//         if (look_for->duration == 0)//delete
//         {
//             del_summon(look_for);
//         }

//         look_for = q->link;
//     }
// }

