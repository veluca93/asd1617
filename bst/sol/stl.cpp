#include <stdio.h>
#include <stdlib.h>
#include <set>

int main() {
    int n, o, i;
    scanf("%d%d", &n, &o);
    int* data = (int*) malloc(sizeof(int)*n);
    for (i=0; i<n; i++) {
        scanf("%d", &data[i]);
    }
    std::set<int> vals(data, data+n);
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
        } else if (op == 'r') {
            scanf("%d", &num2);
            auto start = vals.lower_bound(num);
            auto end = vals.lower_bound(num2);
            printf("%d\n", (int) std::distance(start, end));
        }
    }
}
