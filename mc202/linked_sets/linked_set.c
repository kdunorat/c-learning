#include <stdio.h>
#include <stdlib.h>

#include "linked_set.h"


list* ls_create(){
    list* L = malloc(sizeof(list));
    if (L) {
        L->head = NULL;
        L->tail = NULL;
    }
    return L;
}

node* create_node(int x){
    node* new_node = malloc(sizeof(node));
    if (new_node) {
        new_node->value = x;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

// limpa o conteúdo  de uma lista, mas mantém a estrutura da lista.
void ls_clear(list* A) {
    if (A == NULL) return;
    node* current = A->head;
    while (current != NULL) {
        node* next_node = current->next;
        free(current);
        current = next_node;
    }
    A->head = NULL;
    A->tail = NULL;
}

// libera completamente a lista (nós e a própria estrutura).
void ls_free(list* A) {
    if (A == NULL) return;
    ls_clear(A); // Primeiro limpa o conteúdo
    free(A);     // Depois libera a estrutura
}



node* find_node(list* A, int x) {
    if (A == NULL) return NULL;
    node* current = A->head;
    while (current != NULL && current->value <= x) {
        if (current->value == x) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insert_sorted(list* A, int x) {
    if (A == NULL) return;

    if (A->head == NULL || x < A->head->value) {
        node* new_node = create_node(x);
        new_node->next = A->head;
        if (A->head != NULL) {
            A->head->prev = new_node;
        } else {
            A->tail = new_node;
        }
        A->head = new_node;
        return;
    }

    node* current = A->head;
    while (current->next != NULL && current->next->value < x) {
        current = current->next;
    }

    if (current->value == x || (current->next != NULL && current->next->value == x)) {
        return;
    }

    node* new_node = create_node(x);
    new_node->next = current->next;
    new_node->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = new_node;
    } else {
        A->tail = new_node;
    }
    current->next = new_node;
}

void ls_insert(list* A, int* elements, int t) {
    if (A == NULL) return;
    for (int i = 0; i < t; i++) {
        insert_sorted(A, elements[i]);
    }
}



void remove_node(list* A, int x) {
    if (A == NULL) return;
    node* node_to_remove = find_node(A, x);
    if (node_to_remove == NULL) {
        return;
    }

    node* prev_node = node_to_remove->prev;
    node* next_node = node_to_remove->next;

    if (prev_node != NULL) {
        prev_node->next = next_node;
    } else {
        A->head = next_node; // nova cabeça
    }

    if (next_node != NULL) {
        next_node->prev = prev_node;
    } else {
        A->tail = prev_node;
    }

    free(node_to_remove);
}

void ls_remove(list* A, int* elements, int t){
    if (A == NULL) return;
    for (int i = 0; i < t; i++) {
        remove_node(A, elements[i]); 
    }
}


list* ls_union(list* B, list* C) {
    list* A = ls_create();
    
    if (B != NULL) {
        node* current = B->head;
        while (current != NULL) {
            insert_sorted(A, current->value);
            current = current->next;
        }
    }
    
    if (C != NULL) {
        node* current = C->head;
        while (current != NULL) {
            insert_sorted(A, current->value);
            current = current->next;
        }
    }
    return A;
}
     
list* ls_intersect(list* B, list* C){
    list* A = ls_create();
    
    if (B == NULL || C == NULL) {
        return A;
    }

    node* current_b = B->head;
    while (current_b != NULL) {
        if (find_node(C, current_b->value) != NULL) {
            insert_sorted(A, current_b->value);
        }
        current_b = current_b->next;
    }
    return A;
}

list* ls_diff(list* B, list* C){
    list* A = ls_create();

    if (B == NULL) {
        return A;
    }

    node* current_b = B->head;
    while (current_b != NULL) {
        if (find_node(C, current_b->value) == NULL) {
            insert_sorted(A, current_b->value);
        }
        current_b = current_b->next;
    }
    return A;
}


void print_element(list* A, int x, int name){
    if (find_node(A, x) != NULL) {
        printf("%d esta em C%d\n", x, name);
    } else {
        printf("%d nao esta em C%d\n", x, name);
    }
}

void print_list(list* A, int name){
    printf("C%d = {", name);
    if (A != NULL) {
        node* current = A->head;
        while (current != NULL) {
            printf("%d", current->value);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
    }
    printf("}\n");
}
