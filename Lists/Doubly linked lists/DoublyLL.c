#include "DoublyLL.h"

//------------------------------------------

void initList(List *list) {
    list -> first = NULL;
    list -> end = NULL;
    list -> size = 0;
}//initList

//------------------------------------------

bool isEmpty(List *list) {
    return (list -> size == 0);
    //return (list -> first == NULL);
}//isEmpty

//------------------------------------------

int sizeList(List *list) {
    return (list -> size);
}

//------------------------------------------

void printList(List *list) {
    printf("List = { ");
    Pointer walk;
    for(walk = list -> first; walk != NULL; walk = walk -> next) {
        printf("%d ", walk -> element);
    }
    printf("}\n");
}//printList

//------------------------------------------

void reversePrintList(List *list) {
    printf("Reverse List = { ");
    Pointer walk;
    for(walk = list -> end; walk != NULL; walk = walk -> previous) {
        printf("%d ", walk -> element);
    }
    printf("}\n");
}//reversePrintList

//------------------------------------------

void destroyList(List *list) {
    Pointer walk;
    for(walk = list -> first; walk != NULL; walk = walk -> next) {
        free(walk);
    }
}//destroyList

//------------------------------------------

bool search(List *list, int key) {
    if(!isEmpty(list)) {
        Pointer aux = list -> first;
        while(aux != NULL && key > aux -> element) {
            aux = aux -> next;
        }
        if(aux == NULL || aux -> element > key) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}//search

//------------------------------------------
void insert(List *list, int x) {
    //Create a pointer to list node and bind the value passed as argument as a key of this new node 
    Pointer newNode = malloc(sizeof(Pointer));
    newNode -> element = x;
    //case 1: First element
    if(isEmpty(list)) {
        newNode -> next = list -> first;
        newNode -> previous = NULL;
        list -> first = newNode;
        list -> end = newNode; //para a duplamente encadeada, teremos um ponteiro para o fim da lista, como se trata do primeiro elemento, ele recebe tanto o inicio quanto o fim
    } else if(x < list -> first -> element) {
        //case 2: x lower than the first element
        newNode -> next = list -> first;
        newNode -> previous = list -> first -> previous;
        list -> first -> previous = newNode;
        list -> first = newNode;
    } else {
        //case 3: Not the first element 
        //case 3.1: last element
        if(x > list -> end -> element) {
            //The auxiliar will be assign to the node that end points to
            //The end will be assgn to the new node
            Pointer aux = list -> end;
            list -> end = newNode;
            newNode -> next = NULL;
            newNode -> previous = aux;
            aux -> next = newNode;
        } else {
            //case 3.2: medium element
            Pointer aux = list -> first;
            while(aux -> next != NULL && x > aux -> next -> element) {
                aux = aux -> next;
            }
            newNode -> next = aux -> next;
            newNode -> previous = aux;
            aux -> next = newNode;
            newNode -> next -> previous = newNode;
        }    
    }
    //Increase the size list
    list -> size++;
}
        
//------------------------------------------

//4 casos:
//1) Lista vazia
//2) Elemento a ser removido é menor que o primeiro da lista
//3) Elemento a ser removido é o primeiro
//4) Elemento a ser removido é o primeiro e único na lista
//5) Elemento a ser removido não é o primeiro 
//  5.1) Elemento não está na lista depois de percorrer
//  5.2) Elemento está na lista depois de percorrer
//  5.2.1) Elemento é o último da lista
//  5.2.2) Elemento não é o último da lista

bool removeElement(List *list, int key, int *item) {
    //case 1 and 2
    if(isEmpty(list) || key < list -> first -> element) {
        printf("Unable to remove element (empty list or non-existent element)\n");
        return false;     
    }
    //case 3
    if(list -> first -> element == key) {
        if(list -> size == 1) { //para a duplamente encadeada, devemos tratar do caso da fila ter apenas 1 elemento, afim de evitar o caso do 'anterior' do NULL apontar para NULL
            //case 4
            *item = list -> first -> element;
            free(list -> first);
            list -> first = NULL;
            list -> end = NULL;
            list -> size--;
            return true;
        }
        Pointer aux = list -> first;
        list -> first = aux -> next;
        list -> first -> previous = NULL; //para a duplamente encadeada, precisamos fazer o ponteiro 'anterior' do novo primeiro elemento apontar para NULL
        *item = aux -> element;
        free(aux);
        list -> size--;
        return true;
    }
    //case 5
    Pointer walk = list -> first;
    while(walk -> next != NULL && (key > walk -> next -> element)) {
        walk = walk -> next;
    }
    //case 5.1
    if(walk == NULL || key < walk -> next -> element) {
        printf("The element does not exist in the list\n");
        return false;
    }
    //case 5.2
    //case 5.2.1
    Pointer aux = walk -> next;
    if(list -> end -> element == key) {
        walk -> next = aux -> next;
        list -> end = walk; // na duplamente encadeada, precisamos fazer o ponteiro para o final receber o elemento anterior ao que estamos retirando
        *item = aux -> element;
        free(aux);
    } else {
        //case 5.2.2
        walk -> next = aux -> next;
        walk -> next -> previous = walk;
        *item = aux -> element;
        free(aux);
    }
    list -> size--;
    return true;
}//removeElement

//----------------------------------------