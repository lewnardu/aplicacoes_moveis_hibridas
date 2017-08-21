#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Dados{
    int id;
    char* name;
};

/* Criação da struct No para a lista */
struct No {
    struct Dados info;
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
    printf("\n\nID : %d", list->info.id);
    printf("\nNAME : %s", list->info.name);
    if(!func_isNull(list->next)) printf("\nNEXT : %s", list->next->info.name);
    func_print(list->next);
    return;
}

void func_insert(struct No** list, struct Dados myInfo){
    if(func_isNull(*list)){
        *list = (struct No*)malloc(sizeof(struct No));
        if(func_isNull(*list)){
            printf("\nError! Memory allocation!");
            return;
        }
        (*list)->info = myInfo;
        (*list)->next = func_setNull();
        (*list)->last = (*list);
        printf("Done!");
        return;
    }
    func_insert(&(*list)->last->next, myInfo);
}

void func_add(struct No** list){
    struct Dados myInfo;
    printf("\nEnter the id: ");
    scanf("%d", &myInfo.id);
    printf("\nEnter the name: ");
    myInfo.name = (char*)malloc(16 * sizeof(char));
    scanf("%s", myInfo.name);
    func_insert(list, myInfo);
}

/* Função de recuperação de um nó através do atributo name como chave */
struct No** func_search(struct No** list, char* keyName){
    if(!func_isNull(*list)){
        if(strcmp((*list)->info.name, keyName) == 0) return list;
        else return func_search(&(*list)->next, keyName);/* Chamada recursiva da função */
    }
    return NULL; /* Retornando NULL quando a chave não for encontrada na lista */
}

/* Função de atualização de um nó da lista */
void func_update(struct No** list){
    printf("\nUpdate the id: ");
    scanf("%d", &(*list)->info.id);
    printf("\nUpdate the name: ");
    scanf(" %[^\n]", (*list)->info.name);
    printf("\nDone!\n");
}

/* Função que remove um nó da lista após encontrá-lo com func_search()*/
void func_delete(struct No** list){
    /* A chave é o único nó da lista ou é o último nó da lista*/
    if(func_isNull((*list)->next)){
        *list = func_setNull();
        printf("\nDone!\n");
        return;
    }
    /* A chave é um nó interno da lista*/
    *list = (*list)->next;
    printf("\nDone!\n");
    return;
}

/* Função principal */
int main(int argc, char* argv[]){
    
    struct No* myList;
    
    char answer;
    
    myList = func_setNull();
    
    do{
        printf("\n\nPress \'r\' or \'R\' to register.\nPress \'d\' or \'D\' to delete\nPress \'p\' or \'P\' to printer.\nPress \'s\' or \'S\' to search.\nPress \'u\' or \'U\' to update\nPress 'x' or 'X' to exit.\n>>>");
        scanf(" %c", &answer);
        if (answer == 'r' || answer == 'R'){
            func_add(&myList);
        }else if (answer == 'p' || answer == 'P'){
            func_print(myList);
        }else if (answer == 's' || answer == 'S'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name for search: ");
            scanf(" %[^\n]", name);
            if(func_search(&myList, name)) printf("\nThe key's in the list!\n");
            else printf("\nKey not found!\n");
        }else if (answer == 'u' || answer == 'U'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name to edit node: ");
            scanf(" %[^\n]", name);
            if(func_search(&myList, name)) func_update(func_search(&myList, name)); 
            else printf("\nKey not found!\n");
        }else if (answer == 'd' || answer == 'D'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name to delete node: ");
            scanf(" %[^\n]", name);
            if(func_search(&myList, name)) func_delete(func_search(&myList, name)); 
            else printf("\nKey not found!\n");
        }else if (answer == 'x' || answer == 'X'){
            printf("The end!\n"); 
        }
    }while(answer != 'x' && answer != 'X');

    return 0;
}
