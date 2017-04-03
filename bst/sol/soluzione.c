#include <stdio.h>
#include <stdlib.h>

struct tree_node {
    int val;
    int size;
    struct tree_node *left;
    struct tree_node *right;
};

int sz(struct tree_node* tree) {
    return tree == NULL ? 0 : tree->size;
}

struct tree_node* build_tree(int* data, int begin, int end) {
    if (begin >= end) return NULL;
    struct tree_node* root = malloc(sizeof(struct tree_node));
    int middle = (end+begin)/2;
    root->val = data[middle];
    root->size = end-begin;
    root->left = build_tree(data, begin, middle);
    root->right = build_tree(data, middle+1, end);
    return root;
}

int find(struct tree_node* tree, int val) {
    if (tree == NULL) return 0;
    if (tree->val == val) return 1;
    if (tree->val > val) return find(tree->left, val);
    return find(tree->right, val);
}

struct tree_node* insert(struct tree_node* tree, int val) {
    if (tree == NULL) {
        struct tree_node* root = malloc(sizeof(struct tree_node));
        root->val = val;
        root->size = 1;
        root->left = root->right = NULL;
        return root;
    }
    if (tree->val > val) tree->left = insert(tree->left, val);
    if (tree->val < val) tree->right = insert(tree->right, val);
    tree->size = sz(tree->left) + sz(tree->right) + 1;
    return tree;
}

int find_min(struct tree_node* tree) {
    if (tree->left != NULL) return find_min(tree->left);
    return tree->val;
}

struct tree_node* delete(struct tree_node* tree, int val) {
    if (tree == NULL) return NULL;
    if (tree->val == val) {
        if (tree->right == NULL) {
            struct tree_node* tmp = tree->left;
            free(tree);
            return tmp;
        } else {
            tree->val = find_min(tree->right);
            tree->right = delete(tree->right, tree->val);
            tree->size = sz(tree->left) + sz(tree->right) + 1;
            return tree;
        }
    }
    if (tree->val > val) tree->left = delete(tree->left, val);
    if (tree->val < val) tree->right = delete(tree->right, val);
    tree->size = sz(tree->left) + sz(tree->right) + 1;
    return tree;
}

int count_(struct tree_node* tree, int begin, int end, int il, int ir) {
    if (tree == NULL) return 0;
    if (il && ir) return tree->size;
    if (end <= tree->val) return count_(tree->left, begin, end, il, ir);
    if (begin > tree->val) return count_(tree->right, begin, end, il, ir);
    int lc = count_(tree->left, begin, end, il, 1);
    int rc = count_(tree->right, begin, end, 1, ir);
    return 1+lc+rc;
}

int count(struct tree_node* tree, int begin, int end) {
    return count_(tree, begin, end, 0, 0);
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
