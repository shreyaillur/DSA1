#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node** top, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    newNode->next = *top;
    *top = newNode;

    // Log the push operation
    FILE* log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "Pushed element: %d\n", data);
        fclose(log_file);
    }
}

int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1; // Return -1 to indicate an empty stack
    }
    Node* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);

    // Log the pop operation
    FILE* log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "Popped element: %d\n", data);
        fclose(log_file);
    }

    return data;
}

void generate_random_numbers(Node** top, int num_count) {
    srand(time(NULL));

    int i;  // Variable declaration moved outside the for loop

    for (i = 0; i < num_count; i++) {
        int random_num = rand() % 100 + 1;
        push(top, random_num);
    }
}

void display_stack(Node* top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements:\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    Node* top = NULL; // Initialize the stack

    // Set initialTop to 0
    int initialTop = 0;

    generate_random_numbers(&top, 10);
    display_stack(top);

    return 0;
}



