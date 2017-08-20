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

/* Função que verifica se um nó é NULL ou não */
int func_isNull(struct No* list){
    return (list == NULL);
}

/* Função que exibe todo o conteúdo da lista */
void func_print(struct No* list){
    if(func_isNull(list)){
        printf("\n\nNo more nodes!\n\n");
        return;
    }
    printf("\n\nID : %d", list->id);
    printf("\nNAME : %s", list->name);
    if(list->before != NULL) printf("\nBEFORE : %s", list->before->name);
    if(list->next != NULL) printf("\nNEXT : %s", list->next->name);
    func_print(list->next); /* Chamada recursiva da função */
}

/* Função que insere um novo nó na lista, mas não ordenadamente */
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
        printf("\nInsert was done!\n");
        return;
    }
    func_insert(&(*list)->last->next, (*list)->last, newId, newName);/* Chamada recursiva da função */
}

/* Função que recebe a entrada dos dados do novo nó e os envia para func_insert() */
void func_add(struct No** list){
    char* name = (char*)malloc(16 * sizeof(char));
    int id;
    printf("\nEnter the id: ");
    scanf("%d", &id);
    printf("\nEnter the name: ");
    scanf(" %s", name);
    func_insert(list, NULL, id, name);
}

/* Função de recuperação de um nó através do atributo name como chave */
struct No** func_search(struct No** list, char* keyName){
    if(!func_isNull(*list)){
        if(strcmp((*list)->name, keyName) == 0) return list;
        else return func_search(&(*list)->next, keyName);/* Chamada recursiva da função */
    }
    return NULL; /* Retornando NULL quando a chave não for encontrada na lista */
}

/* Função de atualização de um nó da lista */
void func_update(struct No** list){
    printf("\nUpdate the id: ");
    scanf("%d", &(*list)->id);
    printf("\nUpdate the name: ");
    scanf(" %s", (*list)->name);
    printf("\nDone!\n");
}

/* Função que remove um nó da lista após encontrá-lo com func_search()*/
void func_delete(struct No** list){
	/* A chave é o único nó da lista ou é o último nó da lista*/
	if((func_isNull((*list)->before) && func_isNull((*list)->next)) || func_isNull((*list)->next)){
		*list = func_setNull();
		printf("\nDone!\n");
		return;
	/* A chave é o primeiro nó da lista*/
	}else if(func_isNull((*list)->before)){
		(*list)->next->before = func_setNull();
		*list = (*list)->next;
		printf("\nDone!\n");
		return;
	}
	/* A chave é um nó interno da lista*/
	(*list)->next->before = (*list)->before; /* O anterior do próximo do nó atual passa a ser o anterior do nó atual*/
	(*list)->before->next = (*list)->next; /* O próximo do anterior do nó atual passa a ser o próximo do nó atual*/
	(*list)->before->next->before = (*list)->before;/* O anterior do próximo do anterior do nó atual passa a ser o anterior do nó atual*/
	printf("\nDone!\n");
	return;
}

/* Função principal */
int main(int argc, char* argv[]){
    
    struct No* myList;
    char answer;

    myList = func_setNull();
    
    /* Laço de apresentação do menu de funções do programa */
    do{
        printf("\n\nPress \'r\' or \'R\' to register.\nPress \'d\' or \'D\' to delete\nPress \'p\' or \'P\' to printer.\nPress \'s\' or \'S\' to search.\nPress \'u\' or \'U\' to update\nPress 'x' or 'X' to exit.\n>>>");
        scanf(" %c", &answer);
        if (answer == 'r' || answer == 'R'){
            func_add(&myList);
        } else if (answer == 'p' || answer == 'P'){
            func_print(myList);
        }else if (answer == 's' || answer == 'S'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name for search: ");
            scanf(" %s", name);
            if(func_search(&myList, name)) printf("\nThe key's in the list!\n");
            else printf("\nKey not found!\n");
        }else if (answer == 'u' || answer == 'U'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name to edit node: ");
            scanf(" %s", name);
            if(func_search(&myList, name)) func_update(func_search(&myList, name)); 
            else printf("\nKey not found!\n");
        }else if (answer == 'd' || answer == 'D'){
            char* name = (char*)malloc(16 * sizeof(char));
            printf("Enter the name to delete node: ");
            scanf(" %s", name);
            if(func_search(&myList, name)) func_delete(func_search(&myList, name)); 
            else printf("\nKey not found!\n");
        }else if (answer == 'x' || answer == 'X'){
            printf("\nThe end!\n"); 
        }
    }while(answer != 'x' && answer != 'X');

    return 0;
}