#include <stdio.h>
#include <stdlib.h>

#include "linked_set.h"


list* ls_create(){
    list* L = malloc(sizeof(list));
    L->head = L->tail = NULL;
    return L;
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
    new_node->next = A->head;
    A->head = new_node;
}

void insert_tail(list *A, int x) {
    node* new_node = create_node(x);
    
    if (A->tail == NULL) { 
        A->head = new_node;
        A->tail = new_node;
    } else {
        new_node->prev = A->tail;
        A->tail->next = new_node;
        A->tail = new_node;
    }
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

list* ls_insert(list* A, int* elements, int t) {
    int start_index = 0;

    if (A->head == NULL) {
        insert_head(A, elements[0]);
        start_index = 1; 
    }
    
    // percorre o array de entrada
    for (int i = start_index; i < t; i++) {
        node* current = A->head;
        
        if (check_element(current, elements[i])) { 
            insert_tail(A, elements[i]);
        }
    }
    
    return A;
}

void remove_head(list* A) {
    if (A == NULL || A->head == NULL) {
        return;
    }

    node* node_to_free = A->head; // node pra liberar
    A->head = A->head->next; // avança a cabeça

    
    if (A->head != NULL) {
        A->head->prev = NULL; // a nova cabeça tem prev null
    } else {
        // se a lista ficou vazia a cauda também é null
        A->tail = NULL;
    }
    
    
    free(node_to_free);
}

node* find_node(list* A, int x) {
    node* current = A->head;
    while (current != NULL) {
        if (current->value == x) {
            return current; // nó encontrado
        }
        current = current->next;
    }
    return NULL; // nao encontrado
}

void remove_node(list* A, int x) {
    if (A == NULL || A->head == NULL) return;

    // busca o nó a ser removido
    node* node_to_remove = find_node(A, x);

    if (node_to_remove == NULL) {
        return; // elemento nao encontrado, não faz nada
    }

    // se for a cabeça
    if (node_to_remove == A->head) {
        remove_head(A); 
        return;
    }

    // se for a cauda
    if (node_to_remove == A->tail) {
        A->tail = node_to_remove->prev;
        A->tail->next = NULL; 
    }
    
    // caso geral: meio da lista
    else {
        node_to_remove->prev->next = node_to_remove->next;
        node_to_remove->next->prev = node_to_remove->prev;
    }
    
    if (node_to_remove != A->head) { // remove_head ja liberou
        free(node_to_remove);
    }
}

void ls_remove(list* A, int* elements, int t){
    if (A != NULL){ 
        for (int i=0; i<t; i++){
            remove_node(A, elements[i]); 
        }
    }
}

list* ls_union(list* B, list* C) {
    list* A = ls_create(); // cria novo conjunto para resultado
    
    if (A == NULL) return NULL; 

    // copia os elementos de B para A usando o insert_tail 
    node* current_b = B->head;
    while (current_b != NULL) {
        insert_tail(A, current_b->value); 
        current_b = current_b->next;
    }

    // adiciona os elementos de C que A ainda não tem
    node* current_c = C->head;
    while (current_c != NULL) {
        if (check_element(A->head, current_c->value)) {
            insert_tail(A, current_c->value);
        }
        
        current_c = current_c->next;
    }

    return A;
}
     
list* ls_intersect(list* B, list* C){
    list* A = ls_create();
    node* current_c = C->head;
    while (current_c != NULL) {
        if (!check_element(B->head, current_c->value)) {
            insert_tail(A, current_c->value);
        }
        current_c = current_c->next;
    }
    return A;
}

list* ls_diff(list* B, list* C){
    list* A = ls_create();
    node* current_b = B->head;
    while (current_b != NULL) {
        if (check_element(C->head, current_b->value)) {
            insert_tail(A, current_b->value);
        }
        current_b = current_b->next;
    }
    return A;
}

void print_element(list* A, int x, int name){
    if (check_element(A->head, x)){
        
        printf("%d nao esta em C%d\n", x, name);
    }
    else{
        printf("%d esta em C%d\n", x, name);
    }
}

node* node_sorted_merge(node* a, node* b) {
    node* result = NULL;

    // casos base
    if (a == NULL) return b;
    if (b == NULL) return a;

    // compara o valor e define a recursão
    if (a->value <= b->value) {
        result = a;
        result->next = node_sorted_merge(a->next, b);
        // não ajustamos prev aqui, só no final se necessário.
    } else {
        result = b;
        result->next = node_sorted_merge(a, b->next);
    }
    return result;
}

void node_split_halves(node* source, node** front_ref, node** back_ref) {
    node* fast;
    node* slow;
    slow = source;
    fast = source->next;

    // fast avança duas vezes, slow avança uma vez
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // slow agora está no final da primeira metade
    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL; // quebra a lista na ligação.
}

void node_merge_sort(node** head_ref) {
    node* head = *head_ref;
    node* a; // metade da frente
    node* b; // metade de trás

    // caso base: 0 ou 1 elemento
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    // divide
    node_split_halves(head, &a, &b);

    // ordena as duas metades recursivamente
    node_merge_sort(&a);
    node_merge_sort(&b);

    // merge e atualiza a cabeça da lista
    *head_ref = node_sorted_merge(a, b);
}

void print_list(list* A, int name){
    if (A == NULL || A->head == NULL) {
        return;
    }

    //chama o Merge Sort, que altera o ponteiro L->head
    node_merge_sort(&(A->head));

    node* current = A->head;
    node* last = NULL;

    // ajusta prev e encontra novo tail
    while (current != NULL) {
        current->prev = last;
        last = current;
        current = current->next;
    }
    // a nova cauda é o ultimo last
    A->tail = last; 
    

    current = A->head;
    
    printf("C%d = {", name);
    while (current != NULL) {
        
        printf("%d", current->value);

        if (current->next != NULL){
            printf(", ");
        }
        current = current->next;
    }
    printf("}\n");

}

void ls_free(list* A) {
    if (A == NULL) return;

    node* current = A->head;
    node* next_node;
    
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    
    // libera a propria estrutura
    free(A);
}
void end(list* A){}