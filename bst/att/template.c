#include <stdio.h>
#include <stdlib.h>

struct tree_node {
    // Aggiungete altri campi se ritenete che servano!
    int val;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* build_tree(int* data, int begin, int end) {
    // Costruisce un albero binario di ricerca che contiene i valori
    // presenti nell'array (ordinato) data, nelle posizioni da begin a end.
    return NULL;
}

int find(struct tree_node* tree, int val) {
    // Cerca il valore val nell'albero radicato in tree. Restituisce
    // 0 se non trova il valore, 1 altrimenti.
    return 0;
}

struct tree_node* insert(struct tree_node* tree, int val) {
    // Inserisce il valore val nell'albero radicato in tree, se non era già
    // presente. Restituisce la radice dell'albero così ottenuto.
    return NULL;
}

struct tree_node* delete(struct tree_node* tree, int val) {
    // Elimina il valore val dall'albero radicato in tree. Restituisce
    // la radice dell'albero così ottenuto.
    return NULL;
}

int count(struct tree_node* tree, int begin, int end) {
    // Restituisce il numero di elementi nel range [begin, end) presenti
    // nell'albero radicato in tree.
    return 0;
} 

int main() {
    int n, o, i;
    scanf("%d%d", &n, &o);
    int* data = malloc(sizeof(int)*n);
    for (i=0; i<n; i++) {
        scanf("%d", &data[i]);
    }
    struct tree_node* vals = build_tree(data, 0, n);
    for (i=0; i<o; i++) {
        char op;
        int num, num2;
        scanf(" %c%d", &op, &num);
        if (op == 'f') {
            printf("%d\n", find(vals, num));
        } else if (op == 'i') {
            vals = insert(vals, num);
        } else if (op == 'd') {
            vals = delete(vals, num);
        } else if (op == 'r') {
            scanf("%d", &num2); 
            printf("%d\n", count(vals, num, num2));
        }
    }
    return 0;
}
