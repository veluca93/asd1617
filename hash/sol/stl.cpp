#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>

int main() {
    int o, i;
    scanf("%d", &o);
    std::unordered_set<int> vals;
    for (i=0; i<o; i++) {
        char op;
        int num, num2;
        scanf(" %c%d", &op, &num);
        if (op == 'f') {
            if (vals.count(num)) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else if (op == 'i') {
            vals.insert(num);
        } else if (op == 'd') {
            vals.erase(num);
        }
    }
}
