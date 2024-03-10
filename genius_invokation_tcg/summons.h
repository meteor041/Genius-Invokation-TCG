#include "reaction.h"

// Summons
typedef struct Summon
{
    char name[30];
    int duration;
    int max_duration; // 最大存在回合
    int side;
    void (*effect)(character *, character *, character *, character *);
    struct Summon *link;
} summon;

// summon summons[2][4];

int summon_ct[2] = {0, 0}; // 0-A, 1-B

// summon melody_loop = {
//     "Melody Loop",
//     2,
//     2,
//     // melody_loop_effect,
// };

summon *List = NULL;
summon *r, *p;

void create_summon(char * summon_name, int summon_duration, 
        int summon_max_duration, int summon_side, 
        void (*summon_effect)(character *, character *, character *, character *))
{
    p = (summon *)malloc(sizeof(summon));
    strcpy(p->name, summon_name);
    p->duration = summon_duration;
    p->max_duration = summon_max_duration;
    p->side = summon_side;
    p->effect = summon_effect;
    if (List == NULL)
    {
        List = p;
    }
    else
    {
        r->link = p;
    }
    r = p;
    r->link = NULL;
}

void melody_loop_effect(character *my_ch, character *rv_ch, 
                        character *my_standby_ch, character *rv_standby_ch)
{
    printf("Barbara's melody loop takes effect!\n");
    (*my_ch).hp += 1;
    if ((*my_ch).hp > 10)
        (*my_ch).hp = 10;

    (*my_standby_ch).hp += 1;
    if ((*my_standby_ch).hp > 10)
        (*my_standby_ch).hp = 10;

    (*(my_standby_ch + 1)).hp += 1;
    if ((*(my_standby_ch+1)).hp > 10) // 后期制作中会有部分角色血量不为10,到时再改
        (*(my_standby_ch+1)).hp = 10; // 防止治疗量溢出(反正没做海染套)

    // hydro application
    harmless_application(my_ch, 2); 

}

// void load_summon_effect(summon *my_summon, void (*effect_ptr)(character *, character *, character *, character *))
// {
//     (*my_summon).effect = effect_ptr;
// }

void del_summon(summon *del_summon)
{
    if (del_summon == List)
    {
        List = List->link;
        free(del_summon);
    }
    else
    {
        summon *q = List;
        while (q->link != del_summon && (q->link != NULL))
        {
            q = q->link;
        }
        q->link = del_summon->link;
        free(del_summon);
    }
}

void summon_take_effect(summon *list, character *a_ch, character *b_ch, 
        character *a_st_ch, character *b_st_ch)
{
    summon * look_for = list;
    while (look_for != NULL)
    {
        summon * q = look_for;
        look_for->duration -= 1; // 使用次数-1
        if (look_for->side == 0)// A
            look_for->effect(a_ch, b_ch, a_st_ch, b_st_ch);
        else // B
            look_for->effect(b_ch, a_ch, b_st_ch, a_st_ch);

        if (look_for->duration == 0)//delete
        {
            del_summon(look_for);
        }

        look_for = q->link;
    }
}