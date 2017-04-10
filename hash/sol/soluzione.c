#include <stdio.h>
#include <stdlib.h>

static const int prime = 1000000007;

struct list_t {
    int v;
    struct list_t* next;
};

int list_find(struct list_t* list, int val) {
    if (list == NULL) return 0;
    if (list->v == val) return 1;
    return list_find(list->next, val);
}

struct list_t* list_insert(struct list_t* list, int val) {
    if (list == NULL) {
        list = malloc(sizeof(struct list_t));
        list->next = NULL;
        list->v = val;
        return list;
    }
    if (list->v == val) return list;
    list->next = list_insert(list->next, val);
    return list;
}

struct list_t* list_delete(struct list_t* list, int val) {
    if (list == NULL) return NULL;
    if (list->v == val) {
        struct list_t* tmp = list->next;
        free(list);
        return tmp;
    }
    list->next = list_delete(list->next, val);
    return list;
}

struct hash_table {
    int a, b; // Parametri per la funzione di hash
    int n_bucket; // Numero di bucket presenti nella tabella di hash
    // Riempite con ulteriori campi necessari
    struct list_t** data;
};

int hash(struct hash_table* ht, int val) {
    // Come visto a lezione
    return ((((ht->a*(long long)val+ht->b) % prime) + prime ) % prime) % ht->n_bucket;
}

struct hash_table* create_hash_table(int expected_size) {
    // Costruisce una tabella di hash vuota che si aspetta di contenere
    // fino a O(expected_size) elementi
    int i;
    struct hash_table* ht = malloc(sizeof(struct hash_table));
    ht->a = rand();
    ht->b = rand();
    ht->n_bucket = expected_size/2;
    ht->data = malloc(sizeof(struct list_t*) * ht->n_bucket);
    for (i=0; i<ht->n_bucket; i++)
        ht->data[i] = NULL;
    return ht;
}

int find(struct hash_table* ht, int val) {
    // Restituisce 1 se val è presente in ht, 0 altrimenti
    return list_find(ht->data[hash(ht, val)], val);
}

void insert(struct hash_table* ht, int val) {
    // Inserisce val nella tabella di hash ht
    ht->data[hash(ht, val)] = list_insert(ht->data[hash(ht, val)], val);
}

void delete(struct hash_table* ht, int val) {
    // Elimina val dalla tabella di hash ht
    ht->data[hash(ht, val)] = list_delete(ht->data[hash(ht, val)], val);
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
