#include <stdio.h>
#include <stdlib.h>

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
        return; // Lista vazia ou invalida
    }

    node* node_to_free = A->head; // Guarda o no para liberacao (CRITICO!)
    A->head = A->head->next; // Avanca a cabeca

    // 1. Ajuste do ponteiro da nova cabeca
    if (A->head != NULL) {
        A->head->prev = NULL; // A nova cabeca tem 'prev' NULL
    } else {
        // 2. A lista ficou vazia
        A->tail = NULL; // A cauda também é NULL
    }
    
    // 3. Libera a memoria do no antigo
    free(node_to_free);
    // A->size--; // Assumindo que você usa um contador de tamanho
}

node* find_node(list* A, int x) {
    node* current = A->head;
    while (current != NULL) {
        if (current->value == x) {
            return current; // No encontrado
        }
        current = current->next;
    }
    return NULL; // Nao encontrado
}

void remove_node(list* A, int x) {
    if (A == NULL || A->head == NULL) return;

    // 1. Busca o no a ser removido (usando uma funcao de busca)
    node* node_to_remove = find_node(A, x);

    if (node_to_remove == NULL) {
        return; // Elemento nao encontrado, nada para fazer
    }

    // 2. Caso Especial: Cabeca
    if (node_to_remove == A->head) {
        remove_head(A); // Chama a funcao especializada
        return;
    }

    // 3. Caso Especial: Cauda
    if (node_to_remove == A->tail) {
        // O tail vira o anterior do no removido
        A->tail = node_to_remove->prev;
        A->tail->next = NULL; 
    }
    
    // 4. Caso Geral: Meio
    else {
        // Ponteiro para o nó ANTERIOR do nó removido
        node_to_remove->prev->next = node_to_remove->next;
        
        // Ponteiro para o nó SEGUINTE do nó removido
        node_to_remove->next->prev = node_to_remove->prev;
    }
    
    // 5. Libera a memoria (apenas se nao foi liberada por remove_head)
    if (node_to_remove != A->head) { // remove_head ja liberou
        free(node_to_remove);
        // A->size--; 
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
        printf("%d nao esta em C%d", x, name);
    }
    else{
        printf("%d esta em C%d", x, name);
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
        // não ajustamos 'prev' aqui, só no final se necessário.
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

    // 'fast' avança duas vezes, 'slow' avança uma vez
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' agora está no final da primeira metade
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
        printf("A lista esta vazia.\n");
        return;
    }

    // Chama o Merge Sort, que altera o ponteiro L->head
    node_merge_sort(&(A->head));

    // --- RECONSTRUÇÃO DA LIGAÇÃO DUPLA (Opcional, mas necessário para manter a lista funcional) ---
    node* current = A->head;
    node* last = NULL;

    // Ajusta o 'prev' e encontra o novo 'tail'
    while (current != NULL) {
        current->prev = last;
        last = current;
        current = current->next;
    }
    // A nova cauda é o ultimo 'last'
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
    printf("}");

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
    
    // 2. Libera a propria estrutura de gerenciamento 'list'
    free(A);
}
void end(list* A){}