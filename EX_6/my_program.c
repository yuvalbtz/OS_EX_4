#include <stdio.h>
#include <stdlib.h>

void buggy_function() {
    int *arr = (int *)malloc(10 * sizeof(int));

    // Bug: Accessing array out of bounds
    for (int i = 0; i <= 10; i++) {
        arr[i] = i * 2;
    }

    printf("Buggy function completed.\n");

    // Bug: Memory leak, free is missing
}

int main() {
    printf("Starting my_program...\n");
    buggy_function();
    printf("my_program completed.\n");
    return 0;
}
