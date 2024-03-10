#include <stdio.h>

#include "summons.h"
// #include "summons.h"

// Diluc
void dl_sk1(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 2;
}

void dl_sk2(character * my_ch_ptr, character * rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 3;
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 3, side); // pyro
}

void dl_sk3(character * my_ch_ptr, character * rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 8;
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 3, side); // pyro
}

// void (* dl_sk1_ptr)(character*, character*, character*) = dl_sk1;
// void (* dl_sk2_ptr)(character*, character*, character*) = dl_sk2;
// void (* dl_sk3_ptr)(character*, character*, character*) = dl_sk3;

//kaeya
void ky_sk1(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 2;
}

void ky_sk2(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 3;
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 1, side); // cryo
}

void ky_sk3(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 1;
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 1, side); // hydro
}

// void (* ky_sk1_ptr)(character*, character*, character*) = ky_sk1;
// void (* ky_sk2_ptr)(character*, character*, character*) = ky_sk2;
// void (* ky_sk3_ptr)(character*, character*, character*) = ky_sk3;


//barbara's skills
void br_sk1(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 1; // Deals 1 Hydro DMG.
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 2, side); // hydro
}
void br_sk2(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*rv_ch_ptr).hp -= 1;
    // create melody loop
    if (summon_ct[side] < 4) //溢出直接让当前生成的召唤物消失,这种情况在对局中一般较难出现
    {
        // summons[side][summon_ct[side]] = melody_loop;
        summon_ct[side]++; 
        create_summon("melody loop", 2, 2, side, melody_loop_effect);
    }
    application(my_ch_ptr,  rv_ch_ptr, my_st_ch_ptr, rv_st_ch_ptr, 2, side); // hydro
}
void br_sk3(character * my_ch_ptr, character  *rv_ch_ptr, character * my_st_ch_ptr, character * rv_st_ch_ptr, int side)
{
    (*my_ch_ptr).hp += 4;
    for (int i = 0; i < 2; i++)
    {
        if ((*my_st_ch_ptr).hp > 0)
        {
            (*my_st_ch_ptr).hp += 4;
        }
    }
}

// void (* br_sk1_ptr)(character*, character*, character*) = br_sk1;
// void (* br_sk2_ptr)(character*, character*, character*) = br_sk2;
// void (* br_sk3_ptr)(character*, character*, character*) = br_sk3;

// show skills
void show_sk(character ch)
{
    for (int i = 0; i < 3; i++)
    {
        printf("%d:%s\n",i+1, ch.sk_name[i]);
    }
}

void activate_sk(character *my_ch, character *rv_ch, int op, int * flag_ptr, int * dices, int element, 
                int dice_cost, character * my_st_ch, character * rv_st_ch, int side)
{
    switch (op)
    {
        case 0:
            *flag_ptr = 0;
            break;
        case 1: // skill1
            printf("%s active the skill \'%s\' towards %s\n", (*my_ch).name, (*my_ch).sk_name[0], (*rv_ch).name);

            // lauch skill
            (*my_ch).sk1(my_ch, rv_ch, my_st_ch, rv_st_ch, side);
            
            // cost dices
            if (*(dices+element) >= dice_cost)
                *(dices+element) -= dice_cost;
            else  
            {
                *(dices) -= dice_cost - *(dices+element);
                *(dices+element) = 0;
            }  
                
            // bp plus
            if ((*my_ch).BP < (*my_ch).max_bp)
                (*my_ch).BP++;
            break;
        case 2:
            printf("%s active the skill \'%s\' towards %s\n", (*my_ch).name, (*my_ch).sk_name[1], (*rv_ch).name);
            (*my_ch).sk2(my_ch, rv_ch, my_st_ch, rv_st_ch, side);

            if (*(dices+element) >= dice_cost)
                *(dices+element) -= dice_cost;
            else    
                {
                *(dices) -= dice_cost - *(dices+element);
                *(dices+element) = 0;
            } 

            if ((*my_ch).BP < (*my_ch).max_bp)
                (*my_ch).BP++;
            break;
        case 3:
            printf("%s active the skill \'%s\' towards %s\n", (*my_ch).name, (*my_ch).sk_name[2], (*rv_ch).name);
            (*my_ch).sk3(my_ch, rv_ch, my_st_ch, rv_st_ch, side);

            if (*(dices+element) >= dice_cost)
                *(dices+element) -= dice_cost;
            else    
                {
                *(dices) -= dice_cost - *(dices+element);
                *(dices+element) = 0;
            } 
            // 消耗所有BP
            (*my_ch).BP = 0;
            break;
        case 9: // change active character
            show_st_ch(*(my_st_ch), *(my_st_ch+1));
            puts("enter the number before character to set him/her as active character");
            int change_choice;
            scanf("%d", &change_choice);
            character temp = *my_ch;
            *my_ch = *(my_st_ch + change_choice - 1);
            *(my_st_ch + change_choice - 1) = temp;
            printf("Set %s as active character\n", (*my_ch).name);
    }
}

// 计算下轮谁先手(谁这轮先结束回合)
void next_round(int op, int * initial_round_ptr, int t)//t=1-a,t=0-b
{
    if (op == 0)
        if (*initial_round_ptr == 2)
            *initial_round_ptr = t;
}