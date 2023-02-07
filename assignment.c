#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "prot.h"
struct task{  // create struct
    char task_name[100];
    char categories[100];
    int date, month, year;      
};

int date_validation(int date, int month, int year){  // function for date validation
    int check = 0;
    if(year>=0 && year<=99){
        //check month
        if(month>=1 && month<=12){
        //check days
            if((date>=1 && date<=31) && (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)){
                check = 1;
            }
            else if((date>=1 && date<=30) && (month==4 || month==6 || month==9 || month==11)){
                check = 1;
            }
            else if((date>=1 && date<=28) && (month==2)){
                check = 1;
            }
            else if(date==29 && month==2 && ((year+2000)%400==0 ||((year+2000)%4==0 && (year+2000)%100!=0))){
                check = 1;
            }
        }
    }
    return check;
}
void categories(char *cat){  // function to show all the categories and choose the category
    char categories[3][100]={"Urgent", "Moderate", "Low Priority"};
    int opt, flag = 0;
    while(flag==0){
        printf("Choose the category of the task:\n");
        printf("1.%s\n", categories[0]);
        printf("2.%s\n", categories[1]);
        printf("3.%s\n", categories[2]);
        printf("Enter the option: ");
        scanf("%d", &opt);
        getchar();
        switch (opt){
            case 1:
                strcpy(cat, categories[0]);  // copying the value of categories chosen to the cat variable
                flag=1;
                break;
            
            case 2:
                strcpy(cat, categories[1]);
                flag=1;
                break;
            
            case 3:
                strcpy(cat, categories[2]);
                flag=1;
                break;
            default:                                                                    
                printf("Invalid Option\n\n");
                break;
        }
    }
}
void add_task(){  // function to add task to the text file
    FILE *fp;
    struct task tsk;
    struct tm* local;  // calling local time
    char category[100];
    char date_added[100], due_date[100];
    int check=0, i;
    
    time_t now_time;
    now_time = time(NULL);
    local = localtime(&now_time);
    printf("\n========Add Task========\n");
    fp = fopen("myTask1.txt", "a");
    categories(category);
    printf("Enter the name of the task: ");
    gets(tsk.task_name);
    if(tsk.task_name[0]>=97 && tsk.task_name[0]<=122){
        tsk.task_name[0] = toupper(tsk.task_name[0]); 
    }
    
    while(1){
        while(1){
            printf("Enter the due date of the task(dd/mm/yy): ");
            scanf("%d/%d/%d",&tsk.date, &tsk.month, &tsk.year);
            getchar();
            check = date_validation(tsk.date, tsk.month, tsk.year);
            if(check!=1){
                printf("Invalid date format\n");
            }
            else{
                break;
            }
        }
        
        sprintf(due_date, "%d/%02d/%02d",tsk.year, tsk.month, tsk.date);  // changing and format to string
        sprintf(date_added, "%d/%02d/%02d",local->tm_year-100, local->tm_mon + 1, local->tm_mday);

        if(strcmp(due_date, date_added)>=0){
            break;
        }
        else{
            printf("The due date should not be earlier than the date added.\n\n");
        }
    }
    fprintf(fp, "%s:%s:%02d/%02d/%d:%02d/%02d/%d:\n", category, tsk.task_name, local->tm_mday, local->tm_mon + 1, local->tm_year-100,tsk.date, tsk.month, tsk.year);
    printf("\n========Adding Task========\n");

    fclose(fp);
}

void task_status(int date, int month, int year, char *status){  // function to generate task status
    time_t now_time;
    struct tm* local;
    char now[100], due[100];
    time(&now_time);
    local = localtime(&now_time);
    sprintf(now, "%d/%02d/%02d", local-> tm_year-100, local->tm_mon+1, local->tm_mday);
    sprintf(due, "%d/%02d/%02d",year, month, date);

    if(strcmp(due, now)<0){  // comparing the value of the strings
        strcpy(status, "Late");
    }
    else if(strcmp(due, now)==0){
        strcpy(status, "Due Today");
    }
    else if(strcmp(due, now)>0){
        strcpy(status, "Pending");
    }
}
void display_all_taskname(char *chosen, int *opt, char *menu_type){  // function to display all task names and choose the task names
    FILE *fp;
    
    int line=1;
    char name[100][100];
    struct task view;
    struct task add;
    while(*opt!=0){
        strcpy(name[0], "***");
        line = 1;
        fp = fopen("myTask1.txt", "r");  // open file in read mode
        printf("Choose which task to be %s: \n\n", menu_type); 
        printf("0.Back\n");
        while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", view.categories, view.task_name, &add.date, &add.month, &add.year, &view.date, &view.month, &view.year) != EOF){  // scanning each line of the task until EOF
            printf("%d.%s\n", line++, view.task_name);
            strcpy(name[line-1], view.task_name);
        }
        printf("\nEnter the option: ");
        scanf("%d", opt);
        getchar();
        if (*opt<line){
            strcpy(chosen, name[*opt]);
            fclose(fp);
            return;
        }
        else{
            printf("Invalid option\n");
        }
        if(fp==NULL){
            printf("No task added yet.\n");
        }
    }
    
    
}

void view_task(){  // view task menu
    int op = -1, opt=-1, element;
    char symbol;
    FILE * fp;
    fp = fopen("myTask1.txt", "r");
    if(fp==NULL){
        printf("No task added yet!!");
        return;
    }
    fclose(fp);
    
    while(op!=0){
        opt = -1;
        printf("========View Task========\n");
        printf("0) Back\n");
        printf("1) View based on categories\n");
        printf("2) View specific task\n");
        printf("3) Sort by due date\n");
        printf("4) Sort by name\n");
        printf("5) Finished task\n");
        printf("Enter the option: ");
        scanf("%d", &op);
        getchar();
        printf("\n");

        switch(op){
            case 1:
            view_based_on_cat();
            printf("\n");
            break;

            case 2:
            view_based_name();
            printf("\n");
            break;

            case 3:
            element = 3;
            printf("In which order do you want to see?\n");
            printf("1. Ascending\n");
            printf("2. Descending\n");
            printf("Enter the option (1/2): ");
            scanf("%d", &opt);
            while(1){
                if (opt==1){
                    symbol = '>';
                    break;
                }
                else if(opt==2){
                    symbol = '<';
                    break;
                }
                else{
                    printf("Enter the correct option!!!");
                }
            }
            sort(symbol, element);  
            printf("\n");
            break;

            case 4:
            element = 1;
            printf("In which order do you want to see?\n");
            printf("1. Ascending\n");
            printf("2. Descending\n");
            printf("Enter the option (1/2): ");
            scanf("%d", &opt);
            while(1){
                if (opt==1){
                    symbol = '>';
                    break;
                }
                else if(opt==2){
                    symbol = '<';
                    break;
                }
                else{
                    printf("Enter the correct option!!!");
                }
            }
            sort(symbol, element);  
            printf("\n");
            break;

            case 5:
            view_done();
            printf("\n");
            break;

            case 0:  
            break;

            default:
            printf("INVALID OPTION\n\n");
        }
    }
}

void view_based_name(){  // function to view specific task
    char chosen[100], status[50], op='y';
    int opt=-1;
    struct task view;
    struct task add;
    FILE *fp;
    while(op!='n' && opt !=0){
        display_all_taskname(chosen, &opt, "viewed");  // calling the function to display all task names
        if(opt==0){
            return;
        }
        fp = fopen("myTask1.txt", "r"); 
        while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", view.categories, view.task_name, &add.date, &add.month, &add.year, &view.date, &view.month, &view.year) != EOF){
            if(strcmp(chosen, view.task_name)==0){  // comparing the task name from the file with the chosen task name from the called function
                printf("Category\t: %s\n", view.categories);
                printf("Task name\t: %s\n", view.task_name);
                printf("Date added\t: %02d/%02d/%d\n", add.date, add.month, add.year);
                printf("Due date\t: %02d/%02d/%d\n", view.date, view.month, view.year);
                task_status(view.date, view.month, view.year, status);
                printf("Status\t\t: %s\n\n", status);  // printing all the tasks detail
                break;
            }
        }
        if(opt!=0){
            while(1){
                printf("Do you want to view another task?\n");
                printf("(y/n): ");
                scanf("%c", &op);
                getchar();
                if(op!='y'&& op !='n'){
                    printf("Invalid Input\n");
                }
                else{
                    printf("\n");
                    break;
                }
            }
        }
    }
    fclose(fp);
}
void view_done(){ // function to display done tasks
    FILE *fp;
    struct task view;
    struct task add, done;
    fp = fopen("done.txt", "r");
    if (fp==NULL){
        printf("No task done yet!!\n");
        return;
    }
    printf("|\t\tCategory\t\t|\t\tTask Name\t\t|\tDate Added\t|\t\tDue Date\t\t|\tStatus\t|\tDate Done\t|\n");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:DONE:%d/%d/%d:\n", view.categories, view.task_name, &add.date, &add.month, &add.year, &view.date, &view.month, &view.year, &done.date, &done.month, &done.year) != EOF){
        printf("\t        %-15s\t\t", view.categories);
        printf("\t\t%-20s\t\t", view.task_name);
        printf("%02d/%02d/%d", add.date, add.month, add.year);
        printf("\t\t\t%02d/%02d/%d\t", view.date, view.month, view.year);
        printf("\t        %-20s", "DONE");
        printf("%02d/%02d/%d\n", done.date, done.month, done.year);
    }
    fclose(fp);
}
void view_based_on_cat(){  // function to display tasks filtered by categories
    FILE *fp;
    struct task view;
    struct task add;
    char category[100], status[50], stored_name[100];
    int flag = 0, flag_task=0;
    categories(category);
    
    printf("=============Viewing task==========\n\n");
    printf("|\t\tCategory\t\t|\t\tTask Name\t\t|\t\tDate Added\t\t|\t\tDue Date\t\t|\t\tStatus\t\t|\n");
    
    fp = fopen("myTask1.txt", "r");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", view.categories, view.task_name, &add.date, &add.month, &add.year, &view.date, &view.month, &view.year) != EOF){
        if(strcmp(category, view.categories)==0){
            printf("\t        %-15s\t\t", category);
            printf("\t\t%-20s\t\t", view.task_name);
            printf("\t%02d/%02d/%d\t", add.date, add.month, add.year);
            printf("\t\t\t%02d/%02d/%d\t", view.date, view.month, view.year);
            task_status(view.date, view.month, view.year, status);
            printf("\t\t        %-20s\n", status);
            flag = 1;
        }
    }
    if(feof(fp) && flag ==0){
        printf("Task of the chosen category not found\n");
    }

    fclose(fp);
}

void sort(char symbol, int element){  // function to sort the file
    char new_order[100][4][100];
    char temp[4][100];  
    char status[100];
    int i=0,j, k;
    int x, y, a, b, c; 
    struct task view;
    struct task add;
    FILE *fp;
    fp = fopen("myTask1.txt", "r");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", view.categories, view.task_name, &add.date, &add.month, &add.year, &view.date, &view.month, &view.year) != EOF){
        strcpy(new_order[i][0], view.categories);
        strcpy(new_order[i][1], view.task_name);
        sprintf(new_order[i][2], "%d/%02d/%02d", add.year, add.month, add.date); 
        sprintf(new_order[i][3], "%d/%02d/%02d", view.year, view.month, view.date);      
        i++;
    } // assigning the content of the text file into the new_order array to be sorted
    if(symbol=='>'){  // sorting algorithm for ascending order
        for(j = 0; j < i-1; j++){
            for(k = j+1; k < i; k++){
                if(strcmp(new_order[j][element],new_order[k][element]) > 0){
                    for(a=0; a<4; a++){
                        strcpy(temp[a], new_order[j][a]);
                    }
                    for(b=0; b<4; b++){
                        strcpy(new_order[j][b], new_order[k][b]);
                    }
                    for(c=0; c<4; c++){
                        strcpy(new_order[k][c], temp[c]);
                    }
                }
            }
        }
    }
    else if(symbol=='<'){  // sorting algorithm for descending order
        for(j = 0; j < i-1; j++){
            for(k = j+1; k < i; k++){
                if(strcmp(new_order[j][element],new_order[k][element]) < 0){
                    for(a=0; a<4; a++){
                        strcpy(temp[a], new_order[j][a]);
                    }
                    for(b=0; b<4; b++){
                        strcpy(new_order[j][b], new_order[k][b]);
                    }
                    for(c=0; c<4; c++){
                        strcpy(new_order[k][c], temp[c]);   
                    }
                }
            }
        }
    }
    printf("|\t\tCategory\t\t|\t\tTask Name\t\t|\t\tDate Added\t\t|\t\tDue Date\t\t|\t\tStatus\t\t|\n");
    for(x = 0; x<i; x++){  // displaying all the tasks from the sorted array
        printf("\t        %-15s\t\t", new_order[x][0]);
        printf("\t\t%-20s\t\t", new_order[x][1]);
        sscanf(new_order[x][2], "%d/%d/%d", &add.year, &add.month, &add.date);
        printf("\t%02d/%02d/%d\t", add.date, add.month, add.year);
        sscanf(new_order[x][3], "%d/%d/%d", &view.year, &view.month, &view.date);
        printf("\t\t\t%02d/%02d/%d\t", view.date, view.month, view.year);
        task_status(view.date, view.month, view.year, status);
        printf("\t\t        %-20s\n", status);  
        printf("\n");
    }
    fclose(fp); 
}

void edit_task(){ // function to edit task
    FILE *fp;
    FILE *temp;
    struct task edit;
    struct task add;
    struct tm* local;  // calling local time from system
    int op=-1, option=-1, flag = 0, check;
    char task_edit[100], task_chosen[100];
    char due_date[50], local_date[50];
    time_t now_time;
    now_time = time(NULL);
    local = localtime(&now_time);
    printf("\n========Edit Task========\n");
    display_all_taskname(task_chosen, &op, "edited");
    if (op==0){
        return;
    }
    strcpy(task_edit, task_chosen);
    fp = fopen("myTask1.txt", "r+");
    if (fp==NULL){
        printf("No file created yet\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", edit.categories, edit.task_name, &add.date, &add.month, &add.year, &edit.date, &edit.month, &edit.year) != EOF){
        if(strcmp(task_edit, edit.task_name)==0){  // editing only the chosen file
           
            while(option !=0){
                printf("\n0.Print to file and exit\n");
                printf("1.Category: %s\n", edit.categories);
                printf("2.Task name: %s\n", edit.task_name);
                printf("3.Due date: %02d/%02d/%d\n\n", edit.date, edit.month, edit.year);
                printf("Choose which one to be edited: ");
                scanf("%d", &option);
                getchar();
                switch (option){
                    case 0:
                    printf("");
                    break;

                    case 1:
                    categories(edit.categories);
                   
                    break;

                    case 2:
                    printf("Enter the new task name: ");
                    scanf("%[^\n]", edit.task_name);
                     if(edit.task_name[0]>=97 && edit.task_name[0]<=122){
                            edit.task_name[0] = toupper(edit.task_name[0]);
                            printf("%c\n", edit.task_name[0]);
                        }
                   
                    break;

                    case 3:
                    while (1)
                    {
                        while(1){
                            printf("Enter the new due date (dd/mm/yy): ");
                            scanf("%d/%d/%d", &edit.date, &edit.month, &edit.year);
                            getchar();
                            check = date_validation(edit.date, edit.month, edit.year);
                           
                            

                            if (check==1){
                                break;
                            }
                            else{
                                printf("Invalid Format\n");
                            }
                        }

                        sprintf(due_date, "%d/%02d/%02d",edit.year, edit.month, edit.date);
                        sprintf(local_date, "%d/%02d/%02d",local->tm_year-100, local->tm_mon + 1, local->tm_mday);

                        if(strcmp(due_date, local_date)>=0){
                            break;
                        }
                        else{
                            printf("The due date should not be earlier than the date added.\n\n");
                        }   
                    }
                    break;

                          
                    default:
                    printf("Invalid Option!!!\n");
                }
            }
        }
        fprintf(temp, "%s:%s:%02d/%02d/%d:%02d/%02d/%d:\n", edit.categories, edit.task_name, add.date, add.month, add.year, edit.date, edit.month, edit.year);
    } // reprinting all file to another temp file
    fclose(fp);
    fclose(temp);
    remove("myTask1.txt");  // remove the original file
    rename("temp.txt", "myTask1.txt");  // rename the new temp file to the original file
    printf("================Editing task================\n");

}

void remove_task(){ // function to remove a task
    FILE *fp;
    FILE *temp;
    struct task edit;
    struct task add;
    int op=-1, option=-1, flag = 0;
    char task_edit[100], task_chosen[100];
    printf("\n========Remove Task========\n");
    display_all_taskname(task_chosen, &op, "deleted");
    if (op==0){
        return;
    }
    strcpy(task_edit, task_chosen);
    fp = fopen("myTask1.txt", "r");
    if (fp==NULL){
        printf("No file created yet\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    printf("\n");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", edit.categories, edit.task_name, &add.date, &add.month, &add.year, &edit.date, &edit.month, &edit.year) != EOF){
        if(strcmp(task_edit, edit.task_name)==0){
            continue;  // the rest of the coding inside the loop will be skipped and the loop is continued
        }
        fprintf(temp, "%s:%s:%02d/%02d/%d:%02d/%02d/%d:\n", edit.categories, edit.task_name, add.date, add.month, add.year, edit.date, edit.month, edit.year);
    }
    fclose(fp);
    fclose(temp);
    remove("myTask1.txt");
    rename("temp.txt", "myTask1.txt");
    if(op!=0){
        printf("================Deleting task================\n");
    }
}

void done(){  // function to mark a file as done
    FILE *fp;
    FILE *temp;
    FILE *done;
    struct tm* ptr;
    struct task edit;
    struct task add;
    int op=-1, option=-1, flag = 0;
    char task_edit[100], task_chosen[100];
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    printf("\n========Mark as Done========\n");
    display_all_taskname(task_chosen, &op, "marked as done");
    if (op==0){
        return;
    }
    
    strcpy(task_edit, task_chosen);
    fp = fopen("myTask1.txt", "r");
    if (fp==NULL){
        printf("No file created yet\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    done = fopen("done.txt", "a");
    printf("\n");
    while(fscanf(fp, "%[^:]:%[^:]:%d/%d/%d:%d/%d/%d:\n", edit.categories, edit.task_name, &add.date, &add.month, &add.year, &edit.date, &edit.month, &edit.year) != EOF){
        if(strcmp(task_edit, edit.task_name)==0){  // printing the task into "done.txt"
            fprintf(done, "%s:%s:%02d/%02d/%d:%02d/%02d/%d:DONE:%02d/%02d/%d:\n", edit.categories, edit.task_name, add.date, add.month, add.year, edit.date, edit.month, edit.year, ptr->tm_mday, ptr->tm_mon+1, ptr->tm_year-100);
        }
        else{  //printing the task to the old file
            fprintf(temp, "%s:%s:%02d/%02d/%d:%02d/%02d/%d:\n", edit.categories, edit.task_name, add.date, add.month, add.year, edit.date, edit.month, edit.year);
        }
        
    }
    fclose(fp);
    fclose(temp);
    fclose(done);
    remove("myTask1.txt");
    rename("temp.txt", "myTask1.txt");
    if(op!=0){
        printf("================Marking as Done================\n");
    }
}


