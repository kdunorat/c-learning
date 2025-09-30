
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
node* find_node(list* A, int x);
void remove_node(list* A, int x);
void insert_tail(list* A, int x);
list* ls_insert(list* A, int* elements, int t);
void ls_remove(list* A, int* elements, int t);
list* ls_union(list* B, list* C);
list* ls_intersect(list* B, list* C);
list* ls_diff(list* B, list* C);
void print_element(list* A, int x, int name);
node* node_sorted_merge(node* a, node* b);
void node_split_halves(node* source, node** front_ref, node** back_ref);
void node_merge_sort(node** head_ref);
void print_list(list* A, int name);
void ls_free(list* A);
void end(list* A);



#endif