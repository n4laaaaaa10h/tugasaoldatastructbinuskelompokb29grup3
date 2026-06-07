#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 100

struct Menu {
    int id;
    char name[50];
    int price;
    struct Menu* next; 
};

// Struct Hash Table Utama
struct MenuHashTable {
    struct Menu* table[TABLE_SIZE];
};

struct MenuHashTable* createHashTable() {
    struct MenuHashTable* ht = (struct MenuHashTable*)malloc(sizeof(struct MenuHashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void insertMenu(struct MenuHashTable* ht, int id, const char* name, int price) {
    int index = hashFunction(id);
    
    // Alokasi memori untuk menu baru
    struct Menu* newMenu = (struct Menu*)malloc(sizeof(struct Menu));
    newMenu->id = id;
    strcpy(newMenu->name, name);
    newMenu->price = price;
    newMenu->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newMenu;
    } else {
        newMenu->next = ht->table[index];
        ht->table[index] = newMenu;
    }
    printf("Menu '%s' berhasil ditambahkan!\n", name);
}

void viewAllMenus(struct MenuHashTable* ht) {
    printf("\n=== DAFTAR MENU RESTORAN ===\n");
    printf("%-5s | %-25s | %-10s\n", "ID", "Nama Menu", "Harga");
    printf("---------------------------------------------\n");
    
    bool isEmpty = true;
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Menu* curr = ht->table[i];
        while (curr != NULL) {
            printf("%-5d | %-25s | Rp %-10d\n", curr->id, curr->name, curr->price);
            curr = curr->next;
            isEmpty = false;
        }
    }
    if (isEmpty) {
        printf("Belum ada menu yang terdaftar.\n");
    }
    printf("---------------------------------------------\n");
}

struct Menu* searchMenu(struct MenuHashTable* ht, int id) {
    int index = hashFunction(id);
    struct Menu* curr = ht->table[index];
    
    while (curr != NULL) {
        if (curr->id == id) {
            return curr; // Menu ditemukan
        }
        curr = curr->next;
    }
    return NULL; // Menu tidak ditemukan
}

bool updateMenu(struct MenuHashTable* ht, int id, const char* newName, int newPrice) {
    struct Menu* target = searchMenu(ht, id);
    if (target != NULL) {
        strcpy(target->name, newName);
        target->price = newPrice;
        return true;
    }
    return false; // Gagal update karena ID tidak ada
}

bool deleteMenu(struct MenuHashTable* ht, int id) {
    int index = hashFunction(id);
    struct Menu* curr = ht->table[index];
    struct Menu* prev = NULL;
    
    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) {
                ht->table[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr); // Bebaskan memori
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false; // Gagal hapus karena ID tidak ada
}

#endif