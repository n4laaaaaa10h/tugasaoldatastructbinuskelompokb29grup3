#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BST Node Structure untuk Manajemen Data Kasir/Menu Berbasis BST
typedef struct Node {
    int id;                // Item ID
    char name[50];         // Item Name
    char category[20];     // Category 
    float price;           // Item Price
    struct Node *left;
    struct Node *right;
} Node;

// Fungsi membuat Node BST baru
Node* createNode(int id, char name[], char category[], float price) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    
    // Perbaikan BUG: Menyalin string nama menu ke struct
    strcpy(newNode->name, name);
    strcpy(newNode->category, category);
    
    newNode->price = price;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 1. INSERT: Memasukkan data baru ke dalam BST secara rekursif
Node* insertBST(Node *root, int id, char name[], char category[], float price) {
    if (root == NULL)
        return createNode(id, name, category, price);

    if (id < root->id)
        root->left = insertBST(root->left, id, name, category, price);
    else if (id > root->id)
        root->right = insertBST(root->right, id, name, category, price);

    return root;
}

// 2. SEARCH: Mencari data berdasarkan ID di dalam BST
Node* searchBST(Node *root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return searchBST(root->left, id);
    else
        return searchBST(root->right, id);
}

// 3. READ / IN-ORDER TRAVERSAL: Menampilkan data terurut dari ID terkecil
void printInOrder(Node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%-10d | %-25s | %-15s | Rp %.2f\n",
               root->id, root->name, root->category, root->price);
        printInOrder(root->right);
    }
}

// Fungsi pembantu untuk mencari nilai terkecil (digunakan saat delete node dengan 2 anak)
Node* findMin(Node *root) {
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

// 4. DELETE: Menghapus data dari BST berdasarkan ID
Node* deleteItemBST(Node *root, int id) {
    if (root == NULL)
        return root;
    
    if (id < root->id) {
        root->left = deleteItemBST(root->left, id);
    }
    else if (id > root->id) {
        root->right = deleteItemBST(root->right, id);
    }
    else {
        // Node ditemukan
        // Kasus 1 & 2: Node tidak punya anak atau hanya punya 1 anak
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        
        // Kasus 3: Node memiliki 2 anak
        Node *temp = findMin(root->right);

        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->category, temp->category);
        root->price = temp->price;

        root->right = deleteItemBST(root->right, temp->id);
    }

    return root;
}

#endif