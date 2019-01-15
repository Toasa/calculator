#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

static char *input;
static char *p;

int add();

void skip() {
    while (*p == ' ' || *p == '\t') {
        p++;
    }
}

void expect(char c) {
    if (*p == c) {
        p++;
        return;
    }
    printf("expected %c, but got %c\n", c, *p);
    exit(1);
}

int num() {
    skip();
    int n;

    if (*p == '(') {
        p++;
        n = add();
        expect(')');
        skip();
        return n;
    }

    n = (*p++ - '0');
    while (isdigit(*p)) {
        n = 10 * n + (*p++ - '0');
    }
    skip();
    return n;
}

int mul() {
    int n = num();
    while (*p == '*' || *p == '/') {
        if (*p == '*') {
            if (*(p + 1) == '*') {
                p += 2;
                n = (int)pow(n, num());
            } else {
                p++;
                n = n * num();
            }
        }
        if (*p == '/') {
            p++;
            n = n / num();
        }
    }
    return n;
}

int add() {
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
    p = malloc(sizeof(char) * 1000);
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
        p = input;
        printf("%d\n", add());
        printf(">>> ");
        i = 0;
    }

    return 0;
}
