
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
int check_element(node* current, int x);
void insert_head(list* A, int x);
void remove_head(list* A);
void remove_tail(list* A);
void insert_tail(list* A, int x);
void ls_insert(list* A, int* elements, int t);
void ls_remove(list* A, int* elements, int t);
void ls_union(int name, list* B, list* C);
void ls_intersect(list*A, list* B, list* C);
void ls_diff(list*A, list* B, list* C);
void print_element(list* A, int x);
void print_list(list* A);
void end(list* A);



#endif