#include "characters.h"

void reaction(character * my_ch, character * rv_ch, character * my_st_ch, 
        character * rv_st_ch, int element, int element_attachment)
{
    switch (element){
        case 1://Cryo
            switch(element_attachment){
                case 2: // frozen
                (*rv_ch).hp -= 1;
                (*rv_ch).status = 1; // frozen
                (*rv_ch).application = 0;
                printf("##Frozen## %s recieces the Frozen status.\n", (*rv_ch).name);
                break;

                case 3: //pyro, 增幅反应(融化)
                (*rv_ch).hp -= 2;
                (*rv_ch).application = 0;
                puts("##Melt##");
                break;        
            }   
            break;
        case 2: // hydro
            switch (element_attachment){
                case 1:
                (*rv_ch).hp -= 1;
                (*rv_ch).status = 1; // frozen
                (*rv_ch).application = 0;
                printf("##Frozen## %s recieces the Frozen status.\n", (*rv_ch).name);
                break;

                case 3:
                (*rv_ch).hp -= 2;
                (*rv_ch).application = 0;
                puts("##Vaporize##");
                break;

            }
            break;
        case 3: // pyro
            switch (element_attachment){
                case 1:
                    (*rv_ch).hp -= 2;
                    (*rv_ch).application = 0;
                    puts("##Melt##");
                    break; 
                case 2:
                    (*rv_ch).hp -= 2;
                    (*rv_ch).application = 0;
                    puts("##Vaporize##");
                    break;
            }
            break;
    }
}


void application(character * my_ch, character * rv_ch, character * my_st_ch, character * rv_st_ch, 
                int element_attachment, int side)
{
    if ((*rv_ch).application == 0)// 对方角色没有元素附着
        (*rv_ch).application = element_attachment;
    else{
        reaction(my_ch, rv_ch, my_st_ch, rv_st_ch, (*rv_ch).application, element_attachment);
    }
}

// harmless application
void harmless_application(character * ch, int element_attachment)
{
    switch ((*ch).application)
    {
        case 0:// 本身没有元素
            (*ch).application = element_attachment;
            break;
        case 1: // Cryo
            switch (element_attachment){
                case 2:
                    (*ch).application = 0;
                    break;
                case 3:
                    (*ch).application = 0;
                    break;
            }
            break;
        case 2: // hydro
            switch (element_attachment){
                case 1:
                    (*ch).application = 0;
                    break;
                case 3:
                    (*ch).application = 0;
                    break;
            }
            break;
        case 3: // pyro
            switch (element_attachment){
                case 1:
                    (*ch).application = 0;
                    break;
                case 2:
                    (*ch).application = 0;
                    puts("##Vaporize but no harm##");
                    break;
            }
            break;
    }
}

// clear status of characters (only considering of Frozen)
void clear_status(character * a_ch, character * b_ch, character * a_st_ch, character * b_st_ch)
{
    // 现暂时只考虑冻结状态
    (*a_ch).status = 0;
    (*b_ch).status = 0;
    (*(a_st_ch)).status = 0;
    (*(a_st_ch+1)).status = 0;
    (*b_st_ch).status = 0;
    (*(b_st_ch+1)).status = 0;
}

