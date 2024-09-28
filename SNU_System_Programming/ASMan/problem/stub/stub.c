#include <stdio.h>

unsigned int compute(){
    volatile unsigned int res = 0;
    return res;
}

int main(void) {
    unsigned int res;

    res = compute();
    printf("%d\n", res);
    return 0;
}
