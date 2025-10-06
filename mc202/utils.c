#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* slice_array_left(const int* seq, int end_index, int* new_size_ptr) {
    // faz: seq[:end_index]
    
    // calcula o novo tamanho
    int new_size = end_index; 
    
    if (seq == NULL || new_size <= 0) {
        *new_size_ptr = 0; // define o tamanho como 0
        return NULL;       // retorna nulo, sem subvetor válido
    }

    // aloca memória para o subvetor
    int* sub_array = malloc(new_size * sizeof(int));
    

    // copia os dados
    // memcpy(destino, fonte, número_de_bytes_a_copiar)
    size_t bytes_to_copy = new_size * sizeof(int);
    memcpy(sub_array, seq, bytes_to_copy);

    // retorna o novo tamanho para a função chamadora
    *new_size_ptr = new_size;

    
    return sub_array;
}

int* slice_array_right(const int* seq, int total_size, int start_index, int* new_size_ptr) {
    // faz: seq[end_index+1:]

    // o novo tamanho é o total menos o número de elementos antes do início.
    int new_size = total_size - start_index - 1;
    
    // casos limite
    if (seq == NULL || new_size <= 0 || start_index >= total_size) {
        *new_size_ptr = 0;
        return NULL; 
    }

  
    int* sub_array = malloc(new_size * sizeof(int));
    
    if (sub_array == NULL) {
        *new_size_ptr = 0;
        return NULL;
    }

    // seq + start_index é o endereço do primeiro elemento a copiar.
    const int* source_ptr = seq + start_index + 1;


    size_t bytes_to_copy = new_size * sizeof(int);
    memcpy(sub_array, source_ptr, bytes_to_copy);

    // retorna o novo tamanho e o ponteiro
    *new_size_ptr = new_size;
    return sub_array;
}

int find_min_idx(int* seq, int t){
    int min_index = 0;
    int min_value = seq[0];
    
    for (int i=1; i<t; i++){
        if (seq[i] < min_value){
            min_value = seq[i];
            min_index = i;
        }
    }

    return min_index;

}


// Node* recursive_cart_tree(int* seq, int t, int offset) {
//     if (t <= 0)
//         return NULL;

//     int min_index = find_min_idx(seq, t);

//     Node* root = malloc(sizeof(Node));
//     root->value = seq[min_index];
//     root->index = offset + min_index; // índice real no vetor original

//     int new_size_left;
//     int* left_subarray = slice_array_left(seq, min_index, &new_size_left);
//     root->left = recursive_cart_tree(left_subarray, new_size_left, offset); // mesmo offset

//     int new_size_right;
//     int* right_subarray = slice_array_right(seq, t, min_index + 1, &new_size_right);
//     root->right = recursive_cart_tree(right_subarray, new_size_right, offset + min_index + 1); // deslocamento ajustado

//     free(left_subarray);
//     free(right_subarray);

//     return root;
// }