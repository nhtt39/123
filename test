#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char action;
    char value;
} Operation;

typedef struct {
    Operation data[MAX];
    int top;
} Stack;

typedef struct {
    char data[MAX];
    int length;
} String;

void initStack(Stack *s) {
    s->top = -1;
}

void initString(String *s) {
    s->length = 0;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, Operation op) {
    if (!isFull(s)) {
        s->data[++s->top] = op;
    }
}

Operation pop(Stack *s) {
    Operation op = {'\0', '\0'};
    if (!isEmpty(s)) {
        op = s->data[s->top--];
    }
    return op;
}

void insert(String *s, char c, Stack *undo, Stack *redo) {
    if (s->length < MAX) {
        s->data[s->length++] = c;
        Operation op = {'I', c};
        push(undo, op);
        initStack(redo);
    }
}

void undo(String *s, Stack *undo, Stack *redo) {
    Operation op = pop(undo);
    if (op.action == 'I') {
        s->length--;
        push(redo, op);
    }
}

void redo(String *s, Stack *undo, Stack *redo) {
    Operation op = pop(redo);
    if (op.action == 'I') {
        s->data[s->length++] = op.value;
        push(undo, op);
    }
}

void display(String *s) {
    printf("Van ban hien tai: ");
    for (int i = 0; i < s->length; i++) {
        printf("%c", s->data[i]);
    }
    printf("\n");
}

int main() {
    String text;
    Stack undo, redo;
    char command[10], c;

    initString(&text);
    initStack(&undo);
    initStack(&redo);

    while (1) {
        printf("Nhap lenh (INSERT/UNDO/REDO/HIEN THI/THOAT): ");
        scanf("%s", command);

        if (strcmp(command, "INSERT") == 0) {
            scanf(" %c", &c);
            insert(&text, c, &undo, &redo);
        } else if (strcmp(command, "UNDO") == 0) {
            undo(&text, &undo, &redo);
        } else if (strcmp(command, "REDO") == 0) {
            redo(&text, &undo, &redo);
        } else if (strcmp(command, "HIEN") == 0) {
            display(&text);
        } else if (strcmp(command, "THOAT") == 0) {
            break;
        } else {
            printf("Lenh khong hop le!\n");
        }
    }

    return 0;
}
