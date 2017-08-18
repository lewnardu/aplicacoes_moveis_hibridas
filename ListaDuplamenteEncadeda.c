#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* Criação da struct No para a lista duplamente encadeada*/
struct No {
    int id;
    char* name;
    struct No* before; /* Aponta para nó anterior na lista */
    struct No* next; /* Aponta para o próximo nó da lista */
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
        printf("\n\nNo more nodes!\n\n");
        return;
    }
    printf("\n\nID : %d", list->id);
    printf("\nNAME : %s", list->name);
    if(list->before != NULL) printf("\nBEFORE : %s", list->before->name);
    if(list->next != NULL) printf("\nNEXT : %s", list->next->name);
    func_print(list->next);
}

void func_insert(struct No** list, struct No* before, int newId, char* newName){
    if(func_isNull(*list)){
        *list = (struct No*)malloc(sizeof(struct No));
        if(func_isNull(*list)){
            printf("\nError! Memory allocation.\n");
            return;
        }
        (*list)->id = newId;
        (*list)->name = (char*)malloc(16 * sizeof(char));
        strcpy((*list)->name, newName);
        (*list)->next = func_setNull();
        (*list)->before = before;
        (*list)->last = (*list);
        printf("Insert ok!\n");
        return;
    }
    func_insert(&(*list)->last->next, (*list)->last, newId, newName);
}

void func_add(struct No** list){
    char* name = (char*)malloc(16 * sizeof(char));
    int id;

    printf("\nEnter the id: ");
    scanf("%d", &id);
    printf("\nEnter the name: ");
    scanf("%s", name);

    func_insert(list, NULL, id, name);
}

struct No** func_search(struct No** list, char* keyName){
    if(!func_isNull(*list)){
        if(strcmp((*list)->name, keyName) == 0){
            return list;
        }else{
            func_search(&(*list)->next, keyName);    
        }
    }
    return NULL;
}


void func_update(struct No** list, char* keyName){
    struct No** myReturn = func_search(&(*list), keyName);
    if(!func_isNull(*myReturn)){
        char* name = (char*)malloc(16 * sizeof(char));
        int id;

        printf("\nUpdate the id: ");
        scanf("%d", &id);
        (*myReturn)->id = id;
        printf("\nUpdate the name: ");
        scanf("%s", name);
        strcpy((*myReturn)->name, name);
    }
}

void func_delete(struct No** list, char* keyName){
    
}

/* Função principal */
int main(int argc, char* argv[]){
    
    struct No* myList;
    char answer;

    myList = func_setNull();
    
    do{
        printf("\n\nPress \'r\' or \'R\' to register.\nPress \'p\' or \'P\' to printer.\nPress \'s\' or \'S\' to search.\nPress \'u\' or \'U\' to update\nPress 'x' or 'X' to exit.\n>>>");
        scanf(" %c", &answer);
        if (answer == 'r' || answer == 'R'){
            func_add(&myList);
        } else if (answer == 'p' || answer == 'P'){
            func_print(myList);
        }else if (answer == 's' || answer == 'S'){
            if(func_search(&myList, "Leonardo"))
                printf("\nChave encontrada!\n");
            else
                printf("\nNao encontrada!\n");
        }else if (answer == 'u' || answer == 'U'){
            func_update(&myList, "Leonardo"); 
        }else if (answer == 'x' || answer == 'X'){
            printf("The end!\n"); 
        }
    }while(answer != 'x' && answer != 'X');

    return 0;
}




















