#infdef BST_H
#define BST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//bst node structure
typedef struct Node{
	int id;                //Menu item id
	char name[50];         //Item name
	char category[20];     //category 
	float price;           //item price
	struct Node *left;
	struct Node *right;
} Node;

//Create new Node
Node* createNode(int id, char name[], char category[], float price) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    
    strcpy(newNode->category, category);
    
    newNode->price = price;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//insert into BST
Node* insert(Node *root, int id, char name[], char category[], float price) {
    if (root == NULL)
        return createNode(id, name, category, price);

    if (id < root->id)
        root->left = insert(root->left, id, name, category, price);
    else if (id > root->id)
        root->right = insert(root->right, id, name, category, price);

    return root;
}

//Search item
Node* search(Node *root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

//display menu
void displayMenu(Node *root) {
    if (root != NULL) {
        displayMenu(root->left);
        printf("ID: %d | Name: %s | Category: %s | Price: %.2f\n",
               root->id, root->name, root->category, root->price);
        displayMenu(root->right);
    }
}

//find min value
Node* findMin(Node *root) {
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

//delete item
Node* deleteItem(Node *root, int id) {
	if (root == NULL)
    return root;
	
	if (id < root->id) {
        root->left = deleteItem(root->left, id);
    }
    else if (id > root->id) {
        root->right = deleteItem(root->right, id);
    }
	
	else{
		if (root->left == NULL) {
			Node *temp = root->right;
			free(root);
			return temp;
		}else if (root->right == NULL) {
			Node *temp = root->left;
			free(root);
			return temp;
		}
		
		//two children
		Node *temp = findMin(root->right);

        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->category, temp->category);
        root->price = temp->price;

        root->right = deleteItem(root->right, temp->id);
    }

    return root;
}

int main() {
    Node *root = NULL;
    int choice, id;
    char name[50];
    char category[20];
    float price;

    do {
        printf("\nRESTAURANT CASHIER\n");
        printf("1. Add Menu Item\n");
        printf("2. Search Menu Item\n");
        printf("3. Display Menu\n");
        printf("4. Delete Menu Item\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Item Name: ");
				scanf(" %[^\n]", name);
				
				printf("Enter Category: ");
				scanf(" %[^\n]", category);
				
				printf("Enter Price: ");
				scanf("%f", &price);
				
				root = insert(root, id, name, category, price);
                printf("Item added successfully!\n");
                break;

            case 2:
                printf("Enter Item ID to search: ");
                scanf("%d", &id);
                Node *found = search(root, id);
                if (found)
                    printf("Found: %s | Price: %.2f\n", found->name, found->price);
                else
                    printf("Item not found.\n");
                break;

            case 3:
                printf("\n--- MENU LIST ---\n");
                displayMenu(root);
                break;

            case 4:
                printf("Enter Item ID to delete: ");
                scanf("%d", &id);
                root = deleteItem(root, id);
                printf("Item deleted if it existed.\n");
                break;

            case 5:
                printf("Thank you! Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}