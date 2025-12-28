#include "helper_shell.h"

void list_init(cmd_list *list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

//allocates a new node to start the list
int add_to_list(cmd_list *list, cmd_t *cmd){
    int index = 0;
    
}