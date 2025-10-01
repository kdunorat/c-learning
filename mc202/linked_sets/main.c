#include <stdio.h>
#include <stdlib.h>

#include "linked_set.h"

int main(){
    int set_name, name_b, name_c;
    char cmd;
    int element, t; 
    
    list** sets = calloc(128, sizeof(list*)); 
    if (sets == NULL) return 1; 

    while(1){
        if (scanf(" %c", &cmd) != 1) break;
        if (cmd == 't') break;

        if (scanf("%d", &set_name) != 1) break;

        if (cmd == 'c'){
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]); 
            }
            sets[set_name] = ls_create(); 
        }
        
        else if (cmd == 'i'){
            if (scanf("%d", &t) != 1) break; 
            int* elements = malloc(sizeof(int) * t);
            if (elements == NULL) break;
            for (int i=0; i<t; i++) scanf("%d", &elements[i]);
            
            ls_insert(sets[set_name], elements, t); 
            free(elements); 
        }
        
        else if (cmd == 'r'){            
            if (scanf("%d", &t) != 1) break; 
            int* elements = malloc(sizeof(int) * t);
            if (elements == NULL) break;
            for (int i=0; i<t; i++) scanf("%d", &elements[i]);
            
            ls_remove(sets[set_name], elements, t);
            free(elements);
        }
        
        else if (cmd == 'u' || cmd == 'n' || cmd == 'm'){
            if (scanf("%d %d", &name_b, &name_c) != 2) break;
            
            list* temp_result = NULL;

            // calcula o resultado primeiro, usando os conjuntos originais
            if (cmd == 'u') {
                temp_result = ls_union(sets[name_b], sets[name_c]);
            } else if (cmd == 'n') {
                temp_result = ls_intersect(sets[name_b], sets[name_c]);
            } else { // cmd == 'm'
                temp_result = ls_diff(sets[name_b], sets[name_c]);
            }

            // agora, liberta o conjunto de destino antigo, se ele existir
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]);
            }
            
            // atribui o novo resultado ao conjunto de destino
            sets[set_name] = temp_result;
        }

        else if (cmd == 'e'){
            scanf("%d", &element);
            print_element(sets[set_name], element, set_name);
        }
        
        else if (cmd == 'p'){
            print_list(sets[set_name], set_name);
        }
    }
    
    // limpeza de memória
    for (int i = 0; i < 128; i++) {
        if (sets[i] != NULL) {
            ls_free(sets[i]); 
        }
    }
    free(sets);

    return 0;
}