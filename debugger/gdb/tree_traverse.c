#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Search for a node by value in the tree
struct Node* findNode(struct Node* root, int value) {
    if (root == NULL)
        return NULL;
    if (root->data == value)
        return root;

    struct Node* found = findNode(root->left, value);
    if (found) return found;
    return findNode(root->right, value);
}

// Inorder traversal
void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder traversal
void preorderTraversal(struct Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Postorder traversal
void postorderTraversal(struct Node* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    char input[100];

    printf("Enter tree nodes as: parent left_child right_child\n");
    printf("Use -1 for no child. Enter 'end' to finish input.\n");

    while (1) {
        printf("Input: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strcmp(input, "end") == 0)
            break;

        int parentVal, leftVal, rightVal;
        if (sscanf(input, "%d %d %d", &parentVal, &leftVal, &rightVal) != 3) {
            printf("Invalid format. Use: parent left right\n");
            continue;
        }

        // Create root if not yet created
        if (root == NULL) {
            root = createNode(parentVal);
        }

        struct Node* parent = findNode(root, parentVal);
        if (parent == NULL) {
            printf("Parent node %d not found. Skipping.\n", parentVal);
            continue;
        }

        if (leftVal != -1 && parent->left == NULL)
            parent->left = createNode(leftVal);
        if (rightVal != -1 && parent->right == NULL)
            parent->right = createNode(rightVal);
    }

    printf("\nInorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
