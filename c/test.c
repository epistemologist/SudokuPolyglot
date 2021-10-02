#include <stdio.h>
#include <string.h>

int main() {
    int test[5];
    memset(test, 0, sizeof(test));
    for (int i = 0; i < 5; i++) {
        printf("%d\n", test[i]);
    }
}
