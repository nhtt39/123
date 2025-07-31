#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Node {
    char bookTitle[MAX_LEN];
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void initStack(Stack* s) {
    s->top = NULL;
}

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isStackEmpty(Stack* s) {
    return s->top == NULL;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void push(Stack* s, char* title) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->bookTitle, title);
    newNode->next = s->top;
    s->top = newNode;
}

void enqueue(Queue* q, char* title) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->bookTitle, title);
    newNode->next = NULL;
    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char* pop(Stack* s) {
    if (isStackEmpty(s)) return NULL;
    Node* temp = s->top;
    char* title = (char*)malloc(MAX_LEN * sizeof(char));
    strcpy(title, temp->bookTitle);
    s->top = temp->next;
    free(temp);
    return title;
}

char* dequeue(Queue* q) {
    if (isQueueEmpty(q)) return NULL;
    Node* temp = q->front;
    char* title = (char*)malloc(MAX_LEN * sizeof(char));
    strcpy(title, temp->bookTitle);
    q->front = temp->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return title;
}

void viewRecentBook(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Khong co sach dang mo\n");
    } else {
        printf("Sach gan nhat: %s\n", s->top->bookTitle);
    }
}

void displayClosedBooks(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Khong co sach da dong\n");
        return;
    }
    Node* current = q->front;
    printf("Lich su dong sach:\n");
    while (current != NULL) {
        printf("- %s\n", current->bookTitle);
        current = current->next;
    }
}

void displayOpenBooks(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Khong co sach dang mo\n");
        return;
    }
    Node* current = s->top;
    printf("Cac sach dang mo:\n");
    while (current != NULL) {
        printf("- %s\n", current->bookTitle);
        current = current->next;
    }
}

void freeStack(Stack* s) {
    while (!isStackEmpty(s)) {
        pop(s);
    }
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
}

void displayMenu() {
    printf("\n--- QUAN LY SACH DIEN TU ---\n");
    printf("1. Mo sach moi\n");
    printf("2. Dong sach hien tai\n");
    printf("3. Xem sach dang doc gan nhat\n");
    printf("4. Lich su dong sach\n");
    printf("5. Khoi phuc sach\n");
    printf("6. Hien thi cac sach dang mo\n");
    printf("7. Thoat\n");
    printf("Nhap lua chon: ");
}

void openNewBook(Stack* s) {
    char title[MAX_LEN];
    printf("Nhap ten sach: ");
    fgets(title, MAX_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    push(s, title);
    printf("Da mo sach: %s\n", title);
}

void closeCurrentBook(Stack* s, Queue* q) {
    char* poppedTitle = pop(s);
    if (poppedTitle) {
        enqueue(q, poppedTitle);
        printf("Da dong sach: %s\n", poppedTitle);
        free(poppedTitle);
    } else {
        printf("Khong co sach dang mo de dong\n");
    }
}

void restoreBook(Stack* s, Queue* q) {
    char* dequeuedTitle = dequeue(q);
    if (dequeuedTitle) {
        push(s, dequeuedTitle);
        printf("Da khoi phuc sach: %s\n", dequeuedTitle);
        free(dequeuedTitle);
    } else {
        printf("Khong co sach da dong de khoi phuc\n");
    }
}

void exitProgram(Stack* s, Queue* q) {
    freeStack(s);
    freeQueue(q);
    printf("Da thoat chuong trinh\n");
}

int main() {
    Stack bookStack;
    Queue closedBooksQueue;
    initStack(&bookStack);
    initQueue(&closedBooksQueue);
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: openNewBook(&bookStack);
                break;
            case 2: closeCurrentBook(&bookStack, &closedBooksQueue);
                break;
            case 3: viewRecentBook(&bookStack);
                break;
            case 4: displayClosedBooks(&closedBooksQueue);
                break;
            case 5: restoreBook(&bookStack, &closedBooksQueue);
                break;
            case 6: displayOpenBooks(&bookStack);
                break;
            case 7: exitProgram(&bookStack, &closedBooksQueue);
                break;
            default: printf("Lua chon khong hop le\n");
        }
    } while (choice != 7);

    return 0;
}
