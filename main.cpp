#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash_table.h"
// #include "trie.h"
// #include "linked_list.h"
// #include "stack.h"
// #include "queue.h"
// #include "bst.h"

// function livesaver sumpah
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar(); 
    getchar(); 
}

int main() {
    ///ini teh template doang.
    struct MenuHashTable* menuTable = createHashTable();
    insertMenu(menuTable, 101, "Nasi Goreng Spesial", 25000);
    insertMenu(menuTable, 102, "Mie Goreng Ayam", 22000);
    insertMenu(menuTable, 103, "Ayam Bakar Taliwang", 35000);
    insertMenu(menuTable, 201, "Es Teh Manis", 5000);
    insertMenu(menuTable, 202, "Jus Alpukat Kocok", 15000);

    struct TrieNode* trieRoot = createTrieNode();
    insertTrie(trieRoot, "Nasi Goreng Spesial");
    insertTrie(trieRoot, "Mie Goreng Ayam");
    insertTrie(trieRoot, "Ayam Bakar Taliwang");
    insertTrie(trieRoot, "Es Teh Manis");
    insertTrie(trieRoot, "Jus Alpukat Kocok");
    
    int mainChoice = 0;
    
    do {
        clearScreen();
        printf("===========================================\n");
        printf("   SISTEM MANAJEMEN KASIR - RESTORAN ANOMALI   \n");
        printf("===========================================\n");
        printf("1. Manajemen Master Menu (CRUD - Hash Table)\n");
        printf("2. Cari Menu (Auto-complete - Trie)\n");
        printf("3. Transaksi Baru / Keranjang (Linked List & Stack)\n");
        printf("4. Antrean Pesanan Dapur (Queue)\n");
        printf("5. Manajemen Data Kasir (BST)\n");
        printf("6. Keluar Aplikasi\n");
        printf("===========================================\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &mainChoice);
        
        switch (mainChoice) {
            case 1: {
                int crudChoice;
                do {
                    clearScreen();
                    printf("=== MANAJEMEN MASTER MENU ===\n");
                    printf("1. Tambah Menu Baru (Insert)\n");
                    printf("2. Lihat Semua Menu (Read)\n");
                    printf("3. Update Data Menu (Update)\n");
                    printf("4. Hapus Menu (Delete)\n");
                    printf("5. Kembali ke Menu Utama\n");
                    printf("Pilih opsi (1-5): ");
                    scanf("%d", &crudChoice);
                    
                    if (crudChoice == 1) {
                        int id, price;
                        char name[50];
                        printf("Masukkan ID Menu baru (Angka): "); scanf("%d", &id);
                        getchar();
                        printf("Masukkan Nama Menu: ");  fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = 0; // hapus newline di akhir string
                        printf("Masukkan Harga Menu: "); scanf("%d", &price);
                        
                        insertMenu(menuTable, id, name, price);
                        pressEnterToContinue();
                    } 
                    else if (crudChoice == 2) {
                        viewAllMenus(menuTable);
                        pressEnterToContinue();
                    } 
                    else if (crudChoice == 3) {
                        int id, newPrice;
                        char newName[50];
                        printf("Masukkan ID Menu yang ingin diubah: "); scanf("%d", &id);
                        struct Menu* found = searchMenu(menuTable, id);
                        if (found != NULL) {
                            getchar();
                            printf("Data Lama: %s (Rp %d)\n", found->name, found->price);
                            printf("Masukkan Nama Baru: "); fgets(newName, sizeof(newName), stdin);
                            newName[strcspn(newName, "\n")] = 0;
                            printf("Masukkan Harga Baru: "); scanf("%d", &newPrice);
                            
                            updateMenu(menuTable, id, newName, newPrice);
                            printf("Menu berhasil diperbarui!\n");
                        } else {
                            printf("Menu dengan ID %d tidak ditemukan.\n", id);
                        }
                        pressEnterToContinue();
                    } 
                    else if (crudChoice == 4) {
                        int id;
                        printf("Masukkan ID Menu yang ingin dihapus: "); scanf("%d", &id);
                        if (deleteMenu(menuTable, id)) {
                            printf("Menu dengan ID %d berhasil dihapus!\n", id);
                        } else {
                            printf("Gagal! Menu dengan ID %d tidak ditemukan.\n", id);
                        }
                        pressEnterToContinue();
                    }
                } while (crudChoice != 5);
                break;
            }

            case 2:
                clearScreen();
                printf("=== CARI MENU AUTO-COMPLETE ===\n");
                printf("[Fitur ini akan menggunakan fungsi dari trie.h]\n");
                printf("Fitur ini sedang disiapkan...\n");
                pressEnterToContinue();
                break;
