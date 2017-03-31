#include <stdio.h>
#include <stdlib.h>

struct tree_node {
    int id;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* build_tree(int root, int* left, int* right) {
    if (root == -1) return NULL;
    struct tree_node* ret = malloc(sizeof(*ret));
    ret->id = root;
    ret->left = build_tree(left[root], left, right);
    ret->right = build_tree(right[root], left, right);
    return ret;
}

int height(struct tree_node* tree) {
    if (tree == NULL) return -1;
    int height_left = height(tree->left);
    int height_right = height(tree->right);
    return (height_left < height_right) ? (height_right+1) : (height_left+1);
}

void free_tree(struct tree_node* tree) {
    if (tree == NULL) return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

int main() {
    int num, root;
    scanf("%d%d", &num, &root);
    int* left = malloc(sizeof(int)*num);
    int* right = malloc(sizeof(int)*num);
    int i;
    for (i=0; i<num; i++) {
        int id, l, r;
        scanf("%d%d%d", &id, &l, &r);
        left[id] = l;
        right[id] = r;
    }
    struct tree_node* tree = build_tree(root, left, right);
    printf("%d\n", height(tree));
    free_tree(tree);
}
