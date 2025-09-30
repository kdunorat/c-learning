#include <stdio.h>
#include <stdlib.h>

#include "linked_set.h"

int main(){
    int set_name, name_b, name_c;
    char cmd;
    int element, t; 
    
    // aloca o array de ponteiros e zera todos os 127 ponteiros (NULL).
    list** sets = calloc(127, sizeof(list*)); 
    if (sets == NULL) return 1; 

    while(1){
        // ignora espacos/newlines e le o comando e o nome.
        if (scanf(" %c %d", &cmd, &set_name) != 2) { 
            break; 
        }
        
        if (cmd == 'c'){
            // Se ja existir, liberamos o antigo (assumindo que ls_create faz o malloc).
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]); 
            }
            sets[set_name] = ls_create(); 
        }
        
        else if (cmd == 'i'){
            
            if (scanf("%d", &t) != 1) break; 
            
            int* elements = malloc(sizeof(int) * t);
            if (elements == NULL) break;
            
            for (int i=0; i<t; i++){
                scanf("%d", &element);
                elements[i] = element;
            }
            
            // passa o set que existe (dentro de sets)
            sets[set_name] = ls_insert(sets[set_name], elements, t); 
            free(elements); 
        }
        
        else if (cmd == 'r'){            
            if (scanf("%d", &t) != 1) break; 
            
            int* elements = malloc(sizeof(int) * t);
            if (elements == NULL) break;

            for (int i=0; i<t; i++){
                scanf("%d", &element);
                elements[i] = element;
            }
            
            ls_remove(sets[set_name], elements, t);
            free(elements);
        }
        
        else if (cmd == 'u'){
            // COMANDO UNIÃO: Cria um novo set (sets[set_name]) a partir de name_b e name_c
            if (scanf("%d %d", &name_b, &name_c) != 2) break;
            
            // Verifica se os sets de origem existem antes de passar
            if (sets[name_b] == NULL || sets[name_c] == NULL) {
                continue;
            }
            
            // Libera o set 'nameA' se ja existir antes de criar a uniao
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]);
            }
            
            sets[set_name] = ls_union(sets[name_b], sets[name_c]); 
        }
        
        else if (cmd == 'p'){
            // COMANDO PRINT: O set[set_name] TEM A GARANTIA DE EXISTIR.
            printf("ENTROU AQUI\n");
            print_list(sets[set_name], set_name);
        }
    }
    
    // --- MEMORY CLEANUP ---
    for (int i = 0; i < 127; i++) {
        if (sets[i] != NULL) {
            // Libera a memória de cada set.
            ls_free(sets[i]); 
        }
    }
    free(sets);

    return 0;
}