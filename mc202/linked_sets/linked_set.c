#include <stdio.h>
#include<stdlib.h>

#include "linked_set.h"


list* ls_create(){
    list* L = malloc(sizeof(list));
    L->head = L->tail = NULL;
    return L;
    // sets[name] = L;
}
node* create_node(int x){
    node* new_node = malloc(sizeof(node));
    new_node->value = x;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert_head(list *A, int x){
    node* new_node = create_node(x);
    if (A->head != NULL){
    A->head->prev = new_node;
    }
    else{
    A->tail = new_node; // a cauda também é o  novo nó caso a lista esteja vazia
    }
    A->head = new_node;
}

void insert_tail(list *A, int x){
    node* new_node = create_node(x);
    new_node->prev = A->tail;
    A->tail->next = new_node;
    A->tail = new_node;
}

int check_element(node* current, int x){
    // retorna 1 se o elemento x não estiver na lista.
    while (current != NULL){
            if (x == current->value){
                return 0;
            }
            current = current->next;
    }
    return 1;
}

void ls_insert(list* A, int* elements, int t){
    if (A->head == NULL){
        insert_head(A, elements[0]);
    }
    
    for (int i=0; i<t; i++){
        node* current = A->head;
        if (check_element(current, elements[i])){
            insert_tail(A, elements[i]);
        }
    }
}

void remove_head(list* A){
    A->head = A->head->next; // a cabeça vira o próximo elemento da cabeça atual
    if(A->head == NULL){
        A->head->prev = NULL;
    }
    else{
        A->tail == NULL; // caso a lista fique vazia
    }
}

void remove_node(list* A, int x){
    node* node_to_remove = A->head;
    if (!check_element(node_to_remove, x)){
        if (node_to_remove == A->head){
            remove_head(A);
        }
        else{
            node_to_remove->prev->next = node_to_remove->next;
            node_to_remove->next->prev = node_to_remove->prev;
        }

        if (node_to_remove->next == NULL){
            A->tail = node_to_remove->prev;
        }
        free(node_to_remove);
    }
    
}

void ls_remove(list* A, int* elements, int t){
    if (A->head != NULL){
        for (int i; i<t; i++){
            remove_node(A, elements[i]);
        }
    }
}

list* ls_union(list* B, list* C){
    list* A = ls_create();
    A = B;
    if (B->head == NULL){
        A = C;  
    }
    else if(!(B->head == NULL && C->head == NULL)){
        
        node* current_c = C->head;
        for (int i=0; current_c->next!=NULL; i++){
        node* current_a = A->head;
        if (check_element(current_a, current_c->value)){
            insert_tail(A, current_c->value);
        }
        current_c = current_c->next;
    }

    }
    return A;
}
     
void ls_intersect(list*A, list* B, list* C){}
void ls_diff(list*A, list* B, list* C){}
void print_element(list* A, int x){}
void print_list(list* A){}
void end(list* A){}