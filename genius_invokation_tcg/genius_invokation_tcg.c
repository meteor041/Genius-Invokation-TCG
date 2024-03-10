#include <stdio.h>

// #include "characters.h"
#include "dice.h"
#include "skills.h"
// #include "reaction.h"
// #include "load.h"

character a_ch, b_ch;
character a_standby[2], b_standby[2];
int main()
{
    // A-Diluc B-Kaeya
    // 由于结构体变量内含函数指针,函数指针在运行时操作,
    // 全局变量初始化在编译时完成,无法将结构体变量从主函数提出来

    // load skills
    load_sk(&Diluc, dl_sk1, dl_sk2, dl_sk3);
    load_sk(&Kaeya, ky_sk1, ky_sk2, ky_sk3);
    load_sk(&Barbara, br_sk1, br_sk2, br_sk3);

    // load summons
    // load_summon_effect(&melody_loop, melody_loop_effect);

    // load characters into a group
    character ch_list[NUM] = {Diluc, Kaeya, Barbara};

    // character ch_list[NUM];
    // load_ch(ch_list);

    puts("Now game starts!");
    // show character
    for (int i = 0; i < NUM; i++)
    {
        printf("%d : %s\n", i + 1, ch_list[i].name);
    }

    // choose character
    int a_choice, b_choice;
    puts("Now A can choose a character:\n(Please enter three numbers before the characters' names)\n(The first character you choose will be the active character)");
    scanf("%d", &a_choice);
    a_ch = ch_list[a_choice - 1];
    scanf("%d", &a_choice);
    a_standby[0] = ch_list[a_choice - 1]; // 1
    scanf("%d", &a_choice);
    a_standby[1] = ch_list[a_choice - 1]; // 2
    puts("------------------------------------------------");

    puts("Now B can choose a character:\n(Please enter three numbers before the characters' names)\n(The first character you choose will be the active character)");
    scanf("%d", &b_choice);
    b_ch = ch_list[b_choice - 1];
    scanf("%d", &b_choice);
    b_standby[0] = ch_list[b_choice - 1]; // 1
    scanf("%d", &b_choice);
    b_standby[1] = ch_list[b_choice - 1]; // 2
    puts("------------------------------------------------");

    // show character's information
    show_ch(a_ch, b_ch);
    puts("------------------------------------------------");

    // start game
    int game_flag = 1;
    int first = 1;         // 1-A, 0-B
    int initial_round = 1; // 谁先手,开局默认A


    while (game_flag)
    {
        // a round of game
        int a_flag = 1;
        int b_flag = 1;

        // round start
        first = initial_round;
        roll_dice(a_dices);
        roll_dice(b_dices);
        printf("A new round! %c will begin first.\n", 'B' - first); // first = 1, A. first = 0, B.
        puts("------------------------------------------------");

        initial_round = 2;

        while (a_flag == 1 || b_flag == 1)
        {
            if ((first == 1 && a_flag == 1) || (a_flag == 1 && b_flag == 0))
            {
                // show the dice
                puts("turn for A");
                show_dices(a_dices);
                int op;
                puts("Enter the num before skill to use it.(enter 0 to end the turn)");
                puts("(enter 9 to change active character)");
                show_sk(a_ch);
                scanf("%d", &op);
                while ((op != 9 && op != 0) && a_ch.status == 1)//frozen
                {
                    printf("%s has been frozen!\n", a_ch.name);
                    scanf("%d", &op);
                }
                while (op != 9 && dice_count(a_ch.element, a_ch.dices_needed[op - 1], a_dices) == 0 || bp_count(a_ch, op) == 0)
                {
                    puts("Insufficient dices!Please enter another number.");
                    scanf("%d", &op);
                }
                printf("A: \n");
                activate_sk(&a_ch, &b_ch, op, &a_flag, a_dices, a_ch.element, a_ch.dices_needed[op - 1], a_standby, b_standby, 0);
                next_round(op, &initial_round, 1);
                first = 0;
                puts("------------------------------------------------");
            }
            else
            {
                puts("turn for B");
                // roll the dice
                show_dices(b_dices);
                int op;
                puts("B:Enter the num before skill to use it.(enter 0 to end the turn)");
                puts("(enter 9 to change active character)");
                show_sk(b_ch);
                scanf("%d", &op);
                while ((op != 9 && op != 0) && b_ch.status == 1)//frozen
                {
                    printf("%s has been frozen!\n", b_ch.name);
                    scanf("%d", &op);
                }
                while (op != 9 && (dice_count(b_ch.element, b_ch.dices_needed[op - 1], b_dices) == 0 || bp_count(b_ch, op) == 0))
                {
                    puts("Insufficient dices or BP!Please enter another number.");
                    scanf("%d", &op);
                }
                printf("B: \n");
                activate_sk(&b_ch, &a_ch, op, &b_flag, b_dices, b_ch.element, b_ch.dices_needed[op - 1], b_standby, a_standby, 1);
                next_round(op, &initial_round, 0);
                first = 1;
                puts("------------------------------------------------");
            }

            

            // 判定角色是否倒下
            if (ch_fall_down(&a_ch, &b_ch, a_standby, b_standby))
                return 0;//结束对局(程序)
            // if (a_ch.hp <= 0)
            // {
            //     printf("%s falls down", a_ch.name);
            //     a_ch_num--;

            //     // 更换角色
            //     if (a_ch_num > 0)
            //     {
            //         show_st_ch(a_standby[0], a_standby[1]);
            //         puts("enter the number before character to set him/her as active character");
            //         int change_choice;
            //         scanf("%d", &change_choice);
            //         while (a_standby[change_choice - 1].hp <= 0)
            //         {
            //             printf("%s has fallen down\n", a_standby[change_choice-1].name);
            //             scanf("%d", &change_choice);
            //         }
            //         character temp = a_ch;
            //         a_ch = a_standby[change_choice - 1];
            //         a_standby[change_choice - 1] = temp;
            //     }
            //     else
            //     {
            //         printf("B player wins!\n");
            //         return 0;
            //     }

            //     printf("Set %s as active character\n", a_ch.name);

            //     game_flag = 0;
            //     break;
            // }
            // else if (b_ch.hp <= 0)
            // {
            //     printf("%s falls down", b_ch.name);
            //     b_ch_num--;

            //     // 更换角色
            //     if (b_ch_num > 0)
            //     {
            //         show_st_ch(b_standby[0], b_standby[1]);
            //         puts("enter the number before character to set him/her as active character");
            //         int change_choice;
            //         scanf("%d", &change_choice);
            //         while (b_standby[change_choice-1].hp <= 0)
            //         {
            //             printf("%s has fallen down\n", b_standby[change_choice-1]);
            //             scanf("%d", &change_choice);
            //         }
            //         character temp = b_ch;
            //         b_ch = b_standby[change_choice - 1];
            //         b_standby[change_choice - 1] = temp;
            //     }
            //     else // 若全部角色都倒下,则失败,对方获胜
            //     {
            //         printf("A player wins!");
            //         return 0;
            //     }

            //     printf("Set %s as active character\n", b_ch.name);
            //     // game_flag = 0;
            //     break; // 直接退出当前轮
            // }

            // show the character's info
            show_ch(a_ch, b_ch);
            puts("------------------------------------------------");
        }

        // 结束阶段,召唤物发挥效果
        summon_take_effect(List, &a_ch, &b_ch, a_standby, b_standby);

        // 召唤物生效后,再判一次死亡
        if (ch_fall_down(&a_ch, &b_ch, a_standby, b_standby))
                return 0;//结束对局(程序)

        clear_status(&a_ch, &b_ch, a_standby, b_standby);
    }
}