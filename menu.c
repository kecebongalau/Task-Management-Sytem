#include <stdio.h>
#include "menu.h"
#include "prot.h"
void menu(){  // Function for main menu
    int opt = -1;

    while(opt!=0){  // Looping the main menu 
        printf("========Personal Task System========\n");
        printf("1) Add Task\n");
        printf("2) View Task\n");
        printf("3) Edit Task\n");
        printf("4) Remove Task\n");
        printf("5) Mark as done\n");
        printf("0) Exit Program\n");
        printf("Enter the option: ");
        scanf("%d", &opt);
        getchar();
        printf("\n");

        switch(opt){
            case 1:
            add_task();
            printf("\n");
            break;

            case 2:
            view_task();
            printf("\n");
            break;

            case 3:
            edit_task();  
            printf("\n");
            break;

            case 4:
            remove_task();
            printf("\n");
            break;

            case 5:
            done();
            break;

            case 0:
            printf("Thank you for using this program\n");   
            break;

            default:
            printf("INVALID OPTION\n\n");
        }
    }
}