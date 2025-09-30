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
        if (scanf(" %c", &cmd) != 1){
            break;
        }

        if (cmd == 't'){
            break;
        }

        if (scanf("%d", &set_name) != 1){
            break;
        }

        
        if (cmd == 'c'){
            // se ja existir, liberamos o antigo.
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
            if (scanf("%d %d", &name_b, &name_c) != 2) break;
            
            // libera o lugar do set A
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]);
            }
            
            sets[set_name] = ls_union(sets[name_b], sets[name_c]); 
        }

        else if (cmd == 'n'){
            if (scanf("%d %d", &name_b, &name_c) != 2) break;
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]);
            }
            sets[set_name] = ls_intersect(sets[name_b], sets[name_c]); 

        }

        else if (cmd == 'm'){
            if (scanf("%d %d", &name_b, &name_c) != 2) break;
            if (sets[set_name] != NULL) {
                ls_free(sets[set_name]);
            }
            sets[set_name] = ls_diff(sets[name_b], sets[name_c]); 

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
    for (int i = 0; i < 127; i++) {
        if (sets[i] != NULL) {
            ls_free(sets[i]); 
        }
    }
    free(sets);

    return 0;
}