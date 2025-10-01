
#ifndef LINKED_SET // não foi definido?
#define LINKED_SET // define


typedef struct node {

  int value; // dado contido no nó

  struct node* next; // next armazena um ponteiro do tipo node
  struct node* prev; // prev armazena um ponteiro do tipo node

} node;

typedef struct list {
  // a lista contem apenas o endereço do primeiro e o ultimo nó
  node* head;
  node* tail;

} list;

list* ls_create();
node* create_node(int x);
node* find_node(list* A, int x);
void remove_node(list* A, int x);
void insert_sorted(list* A, int x);
void ls_insert(list* A, int* elements, int t);
void ls_remove(list* A, int* elements, int t);
list* ls_union(list* B, list* C);
list* ls_intersect(list* B, list* C);
list* ls_diff(list* B, list* C);
void print_element(list* A, int x, int name);
void print_list(list* A, int name);
void ls_free(list* A);


#endif