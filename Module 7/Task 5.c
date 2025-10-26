#include <stdio.h>

int main(void) {
    int a[10] = { 25, 17, 31, 13, 2, 44, 1, 8, 99, 50 };
    int n = 10;
    int i, j, tmp;

    printf("Before:\n");
    for (i = 0; i < n; ++i) printf("%d ", a[i]);
    printf("\n");

    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j+1]) {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }

    printf("After:\n");
    for (i = 0; i < n; ++i) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
