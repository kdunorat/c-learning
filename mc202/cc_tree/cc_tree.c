#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
   int value;
   int index;

   struct Node* left;
   struct Node* right;
   
}Node;

typedef struct CartesianTree {
    Node *root;
} CartesianTree;

typedef struct QueueNode {
    Node* tree_node;
    int level;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void insert_node(CartesianTree* cc_tree, Node* new_node) {
    if (cc_tree->root == NULL) {
        cc_tree->root = new_node;
        return;
    }

    if (new_node->value < cc_tree->root->value) {
        new_node->left = cc_tree->root; // a antiga raiz passa a ser o filho esquerdo
        cc_tree->root = new_node;
        return;
    }

    Node* previous = cc_tree->root;
    Node* current = cc_tree->root->right;

    // avança enquanto o valor atual for <= ao novo valor
    // se current for null ele é o último
    while (current != NULL && current->value <= new_node->value) {
        previous = current;
        current = current->right;
    }

    // se quebrou o while e não chegou no final
    if (current != NULL) {
        // insere new_node entre previous e current
        new_node->left = current;
        previous->right = new_node;
    } else {
        // adiciona no final como maior elemento
        previous->right = new_node;
    }
}

CartesianTree* create_cc_tree(int* seq, int t){
    CartesianTree* cc_tree = malloc(sizeof(CartesianTree));
    cc_tree->root = NULL;
    for (int i=0; i<t; i++){
        Node* new_node =  malloc(sizeof(Node)); // sempre alocar dentro do for quando vc quer sempre um novo nó.
        new_node->value = seq[i];
        new_node->index = i;
        insert_node(cc_tree, new_node);
    }

    return cc_tree;
}


int queue_empty(Queue* q) {
    return q->front == NULL;
}


// para imprimir, percorrer a árvore em largura.
// para isso, precisa da pilha
void enqueue(Queue* q, Node* tree_node, int level) {
    QueueNode* new_node = malloc(sizeof(QueueNode));
    new_node->tree_node = tree_node;
    new_node->level = level;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

QueueNode* dequeue(Queue* q) {
    if (queue_empty(q)) return NULL;

    QueueNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    return temp;
}


void print_levels(Node* root) {
    if (!root) return;

    Queue q = {NULL, NULL};
    enqueue(&q, root, 0);

    int current_level = 0;
    while (!queue_empty(&q)) {
        QueueNode* node_info = dequeue(&q);
        Node* node = node_info->tree_node;

        if (node_info->level > current_level) {
            printf("\n"); // nova linha ao mudar de nível
            current_level = node_info->level;
        }

        printf("%d ", node->index);

        if (node->left)
            enqueue(&q, node->left, node_info->level + 1);
        if (node->right)
            enqueue(&q, node->right, node_info->level + 1);

        free(node_info);
    }

    printf("\n"); // linha em branco final

    // zera a fila
    q.front = NULL;
    q.rear = NULL;
}

void free_nodes(Node* root) {
    if (root == NULL) return;
    free_nodes(root->left);
    free_nodes(root->right);
    free(root);
}

void free_cart_tree(CartesianTree* tree) {
    if (tree == NULL) return;
    free_nodes(tree->root);
    free(tree);
}


int main() {
    int t;
    while (scanf("%d", &t) == 1 && t != 0) {
        printf("DEBUG: Lido t = %d\n", t);
        int *A = malloc(sizeof(int) * t);

        for (int i = 0; i < t; i++) {
            scanf(" %d", &A[i]);
        }
        printf("DEBUG: Vetor lido com sucesso\n");

        printf("DEBUG: Construindo árvore\n");
        CartesianTree *final_tree = create_cc_tree(A, t);
        printf("DEBUG: Árvore criada\n");

        printf("DEBUG: Iniciando print_levels\n");
        print_levels(final_tree->root);
        printf("DEBUG: Print_levels terminou\n");
        printf("\n");

        printf("DEBUG: Liberando árvore\n");
        free_cart_tree(final_tree);
        printf("DEBUG: Árvore liberada\n");

        printf("DEBUG: Liberando vetor\n");
        free(A);
        printf("DEBUG: Vetor liberado\n");
    }
    return 0;
}