#ifndef prot_h  // header file contaitning prototype of all the functions
#define prot_h

int date_validation(int date, int month, int year);
void categories();
void add_task();
void task_status(int date, int month, int year, char *status);
void display_all_taskname(char *chosen, int *opt, char *menu_type);
void view_task();
void view_based_on_cat();
void sort(char symbol, int element);
void view_done();
void view_based_name();
void edit_task();
void remove_task();
void done();

#endif 