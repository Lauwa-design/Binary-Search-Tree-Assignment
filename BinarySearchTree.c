#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

void InsertNode(struct Node** root, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    struct Node* current = *root;
    struct Node* previous = NULL;

    if (*root == NULL)
    {
        *root = newNode;
        return;
    }

    while (current != NULL)
    {
        previous = current;

        if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (value < previous->data)
    {
        previous->left = newNode;
    }
    else
    {
        previous->right = newNode;
    }
}

void inorder(struct Node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
struct Node* minValueNode(struct Node* node)
{
    struct Node* current = node;
    while (current && current->left != NULL)
       current = current->left;
       return current;
}

struct Node* delete_node(struct Node* root, int data)
{
    if (root == NULL)
        return root;

    if (data < root ->data)
        root->left = delete_node(root->left, data);

    else if (data > root->data)
        root->right = delete_node(root->right, data);

    else {
        if (root->left == NULL)
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

int height(struct Node* node) {
    if (node == NULL)
        return -1;
    else {
        int left_height = height(node->left);
        int right_height = height(node->right);
        if (left_height > right_height)
            return(left_height + 1);
        else
            return(right_height + 1);
    }
}
void print_level_and_height(struct Node* root, int data) {
    struct Node* current = root;
    int level = 0;
    while(current != NULL) {
        if(current->data == data) {
            printf("Node %d is at level %d and its height is %d.\n", data, level, height(current));
            return;
        } else if(data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
        level++;
    }
    printf("Node not found in the BST.\n");
}

int main()
 {
    struct Node* root = NULL;
    int values[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int no_values = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < no_values; i++)
    {
        InsertNode(&root, values[i]);
    }

    printf("Inorder traversal of the binary search tree: ");
    inorder(root);
    printf("\n");

     root = delete_node(root, 20);

    // after deletion
    printf("Inorder traversal of the binary search tree after deletion: ");
    inorder(root);
    printf("\n");

    printf("Height of the binary search tree after deletion: %d\n", height(root));

    print_level_and_height(root,5);

    return 0;
}
