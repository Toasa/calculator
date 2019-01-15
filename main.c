#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static char *input;
static char *p;

void skip() {
    while (*p == ' ' || *p == '\t') {
        p++;
    }
}

int num() {
    skip();
    int n = (*p++ - '0');
    while (isdigit(*p)) {
        n = 10 * n + (*p++ - '0');
    }
    return n;
}

int mul() {
    skip();
    int n = num();
    while (*p == '*' || *p == '/') {
        if (*p == '*') {
            p++;
            n = n * num();
        }
        if (*p == '/') {
            p++;
            n = n / num();
        }
    }
    return n;
}

int add() {
    skip();
    int n = mul();
    while (*p == '+' || *p == '-') {
        if (*p == '+') {
            p++;
            n = n + mul();
        }
        if (*p == '-') {
            p++;
            n = n - mul();
        }
    }
    return n;
}

int main() {
    printf("Howdy? toasa\n");
    printf("If you quit, press q\n");
    input = malloc(sizeof(char) * 1000);
    int i = 0;
    char c;
    printf(">>> ");
    for (c = getchar(); c != 'q'; c = getchar()) {
        while (c != '\n') {
            input[i] = c;
            i++;
            c = getchar();
        }
        input[i] = '\0';
        p = malloc(sizeof(char) * 1000);
        p = input;
        printf("%d\n", add());
        printf(">>> ");
        i = 0;
    }

    return 0;
}