#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* Criação da struct No para a lista */
struct No {
    int id;
    char* name;
    struct No* next; /* Aponta para o próximo elemento da lista */
    struct No* last; /* Aponta para o ultimo elemento inserido na lista */
};

/* Funções do programa */

struct No* func_setNull(){
    return NULL;
}

int func_isNull(struct No* list){
    return (list == NULL);
}

void func_print(struct No* list){
    if(func_isNull(list)){
        printf("\n\nNo more nodes!");
        return;
    }
    printf("\n\nID : %d", list->id);
    printf("\nNAME : %s", list->name);
    if(list->next != NULL) printf("\nNEXT : %s", list->next->name);
    func_print(list->next);
    return;
}

void func_insert(struct No** list, int newId, char* newName){
    if(func_isNull(*list)){
        *list = (struct No*)malloc(sizeof(struct No));
        if(func_isNull(*list)){
            printf("\nError! Memory allocation!");
            return;
        }
        (*list)->id = newId;
        (*list)->name = (char*)malloc(16 * sizeof(char));
        strcpy((*list)->name, newName);
        (*list)->next = func_setNull();
        (*list)->last = (*list);
        printf("Insert ok!");
        return;
    }
    func_insert(&(*list)->last->next, newId, newName);
}

void func_add(struct No** list){
    char* name = (char*)malloc(16 * sizeof(char));
    int id;

    printf("\nEnter the id: ");
    scanf("%d", &id);
    printf("\nEnter the name: ");
    scanf("%s", name);
    func_insert(list, id, name);
}

/* Função principal */
int main(int argc, char* argv[]){
    
    struct No* myList;
    
    char answer;
    
    myList = func_setNull();
    
    do{
        printf("\n\nPress \'r\' or \'R\' to register.\nPress \'p\' or \'P\' to printer.\nPress 'x' or 'X' to exit.\n>>>");
        scanf(" %c", &answer);
        if (answer == 'r' || answer == 'R'){
            func_add(&myList);
        } else if (answer == 'p' || answer == 'P'){
            func_print(myList);
        } else if (answer == 'x' || answer == 'X'){
            printf("The end!\n"); 
        }
    }while(answer != 'x' && answer != 'X');

    return 0;
}






















