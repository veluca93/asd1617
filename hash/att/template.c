#include <stdio.h>
#include <stdlib.h>

static const int prime = 1000000007;

struct hash_table {
    int a, b; // Parametri per la funzione di hash
    int n_bucket; // Numero di bucket presenti nella tabella di hash
    // Riempite con ulteriori campi necessari
};

int hash(struct hash_table* ht, int val) {
    // Come visto a lezione. Nota: ((a%prime)+prime)%prime serve per evitare
    // scherzi se a è negativo.
    return ((((ht->a*(long long)val+ht->b) % prime) + prime ) % prime) % ht->n_bucket;
}

struct hash_table* create_hash_table(int expected_size) {
    // Costruisce una tabella di hash vuota che si aspetta di contenere
    // fino a O(expected_size) elementi
    return NULL;
}

int find(struct hash_table* ht, int val) {
    // Restituisce 1 se val è presente in ht, 0 altrimenti
    return 0;
}

void insert(struct hash_table* ht, int val) {
    // Inserisce val nella tabella di hash ht
}

void delete(struct hash_table* ht, int val) {
    // Elimina val dalla tabella di hash ht
}

int main() {
    int o, i;
    scanf("%d", &o);
    struct hash_table* ht = create_hash_table(o);
    for (i=0; i<o; i++) {
        char op;
        int num;
        scanf(" %c%d", &op, &num);
        if (op == 'f') {
            printf("%d\n", find(ht, num));
        } else if (op == 'i') {
            insert(ht, num);
        } else if (op == 'd') {
            delete(ht, num);
        }
    }
    return 0;
}
