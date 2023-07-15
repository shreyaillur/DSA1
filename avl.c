#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct Node* insert(struct Node* root, int key);
struct Node* delete(struct Node* root, int key);

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct Node* delete(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);

            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void savePreorderToFile(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->key);
        savePreorderToFile(root->left, file);
        savePreorderToFile(root->right, file);
    }
}

void saveInorderToFile(struct Node* root, FILE* file) {
    if (root != NULL) {
        saveInorderToFile(root->left, file);
        fprintf(file, "%d ", root->key);
        saveInorderToFile(root->right, file);
    }
}

void savePostorderToFile(struct Node* root, FILE* file) {
    if (root != NULL) {
        savePostorderToFile(root->left, file);
        savePostorderToFile(root->right, file);
        fprintf(file, "%d ", root->key);
    }
}

void display(struct Node* root, int level) {  int i;
    if (root != NULL) {
        display(root->right, level + 1);
        printf("\n");
        if (root == NULL) {

            for (i = 0; i < level; i++) {
                printf("\t");
            }
            printf("----->");
        } else {
            for ( i = 0; i < level; i++) {
                printf("\t");
            }
            printf("%d", root->key);
        }
        display(root->left, level + 1);
    }
}

int main() {
    struct Node* root = NULL;

    srand(time(0));

    int choice, key,i;

    int numRandomNumbers;  /* Variable to store the number of random numbers*/

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &numRandomNumbers);

    /* Generate random numbers and insert them into the AVL tree*/
    for ( i = 0; i < numRandomNumbers; i++) {
        key = rand() % 100;  /* Generate a random number between 0 and 99*/
    root = insert(root, key);
    }

    while (1) {
        printf("\n--------------------------------------\n");
        printf("AVL Tree Menu:\n");
        printf("--------------------------------------\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Save Preorder Traversal to File\n");
        printf("5. Save Inorder Traversal to File\n");
        printf("6. Save Postorder Traversal to File\n");
        printf("7. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("--------------------------------------\n");

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Key %d inserted successfully.\n", key);
                break;

            case 2:
                if (root == NULL) {
                    printf("The tree is empty.\n");
                } else {
                    printf("Enter the key to delete: ");
                    scanf("%d", &key);
                    root = delete(root, key);
                    printf("Key %d deleted successfully.\n", key);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("The tree is empty.\n");
                } else {
                    printf("AVL Tree:\n");
                    display(root, 1);
                    printf("\n");
                }
                break;

            case 4: {
                FILE* file = fopen("preorder.txt", "w");
                if (file == NULL) {
                    printf("Error opening file.\n");
                } else {
                    savePreorderToFile(root, file);
                    fclose(file);
                    printf("Preorder traversal saved to file 'preorder.txt' successfully.\n");
                }
                break;
            }

            case 5: {
                FILE* file = fopen("inorder.txt", "w");
                if (file == NULL) {
                    printf("Error opening file.\n");
                } else {
                    saveInorderToFile(root, file);
                    fclose(file);
                    printf("Inorder traversal saved to file 'inorder.txt' successfully.\n");
                }
                break;
            }

            case 6: {
                FILE* file = fopen("postorder.txt", "w");
                if (file == NULL) {
                    printf("Error opening file.\n");
                } else {
                    savePostorderToFile(root, file);
                    fclose(file);
                    printf("Postorder traversal saved to file 'postorder.txt' successfully.\n");
                }
                break;
            }

            case 7:
                printf("Exiting the program...\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
