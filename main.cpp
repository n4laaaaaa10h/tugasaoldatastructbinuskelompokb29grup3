#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash_table.h"
#include "trie.h"
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
        printf("SISTEM MANAJEMEN KASIR - RESTORAN ANOMALI\n");
        printf("1. Manajemen Master Menu\n");// (CRUD - Hash Table)
        printf("2. Cari Menu (Auto-complete - Trie)\n");
        printf("3. Transaksi Baru / Keranjang\n");// (Linked List & Stack)
        printf("4. Antrean Pesanan Dapur\n");// (Queue)
        printf("5. Manajemen Data Kasir\n");// (BST)
        printf("6. Keluar Aplikasi\n");
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
                printf("CARI MENU AUTO-COMPLETE\n");
                char query[50];
                printf("Masukkan kata kunci untuk mencari menu: ");
                getchar();
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0; // hapus newline

                printf("Hasil pencarian untuk '%s':\n", query);
                int found = printAutoSuggest(trieRoot, query);
                if (!found) {
                    printf("Tidak ada menu yang cocok dengan '%s'.\n", query);
                }
                pressEnterToContinue();
                break;

            case 3:
            struct OrderCart* cart = createCart();
            struc UndoStack* undoStack = createUndoStack();
            int txChoice;
            do {
                clearScreen();
                printf("TRANSAKSI BARU / KERANJANG\n");
                printf("1. Tambah Item ke Keranjang\n");
                printf("2. Lihat Keranjang\n");
                printf("3. Hapus Item dari Keranjang\n");
                printf("4. Undo Aksi Terakhir\n");
                printf("5. Checkout / Selesaikan Transaksi\n");
                printf("6. Kembali ke Menu Utama\n");
                printf("Pilih opsi (1-6): ");
                scanf("%d", &txChoice);
                
                if (txChoice == 1) {
                    int id, quantity;
                    printf("Masukkan ID Menu yang ingin ditambahkan: "); scanf("%d", &id);
                    struct Menu* menuItem = searchMenu(menuTable, id);
                    if (menuItem != NULL) {
                        printf("Masukkan jumlah: "); scanf("%d", &quantity);
                        addToCart(cart, menuItem, quantity);
                        pushUndo(undoStack, "add", menuItem, quantity);
                        printf("%d x %s berhasil ditambahkan ke keranjang.\n", quantity, menuItem->name);
                    } else {
                        printf("Menu dengan ID %d tidak ditemukan.\n", id);
                    }
                    pressEnterToContinue();
                } 
                else if (txChoice == 2) {
                    viewCart(cart);
                    pressEnterToContinue();
                } 
                else if (txChoice == 3) {
                    int id;
                    printf("Masukkan ID Menu yang ingin dihapus dari keranjang: "); scanf("%d", &id);
                    struct CartItem* removedItem = removeFromCart(cart, id);
                    if (removedItem != NULL) {
                        pushUndo(undoStack, "remove", removedItem->menu, removedItem->quantity);
                        printf("%s berhasil dihapus dari keranjang.\n", removedItem->menu->name);
                    } else {
                        printf("Item dengan ID %d tidak ditemukan di keranjang.\n", id);
                    }
                    pressEnterToContinue();
                } 
                else if (txChoice == 4) {
                    if (undoStack->top != -1) {
                        struct UndoAction* lastAction = popUndo(undoStack);
                        if (strcmp(lastAction->actionType, "add") == 0) {
                            removeFromCart(cart, lastAction->menu->id);
                            printf("Undo: %d x %s dihapus dari keranjang.\n", lastAction->quantity, lastAction->menu->name);
                        } else if (strcmp(lastAction->actionType, "remove") == 0) {
                            addToCart(cart, lastAction->menu, lastAction->quantity);
                            printf("Undo: %d x %s ditambahkan kembali ke keranjang.\n", lastAction->quantity, lastAction->menu->name);
                        }
                        free(lastAction);
                    } else {
                        printf("Tidak ada aksi untuk di-undo.\n");
                    }
                    pressEnterToContinue();
                }
                else if (txChoice == 5) {
                    if (cart->head == NULL) {
                        printf("Keranjang kosong! Tambahkan item sebelum checkout.\n");
                    } else {
                        int total = calculateTotal(cart);
                        printf("Total pembayaran: Rp %d\n", total);
                        printf("Transaksi selesai! Terima kasih.\n");
                        clearCart(cart);
                        clearUndoStack(undoStack);
                    }
                    pressEnterToContinue();
                }
            } while (txChoice != 6);
                break;

            case 4: {
                int kitchenChoice;
                do {
                    clearScreen();
                    printf("\n");

                    viewKitchenQueue(kitchenQueue);

                    printf("1. Lihat Antrean Pesanan\n");
                    printf("2. Proses Pesanan Berikutnya\n");
                    printf("3. Kembali ke Menu Utama\n");
                    printf("Pilih opsi (1-3): ");
                    scanf("%d", &kitchenChoice);

                    if (kitchenChoice == 1) {
                        viewKitchenQueue(kitchenQueue);
                        pressEnterToContinue();
                    } else if (kitchenChoice == 2) {
                        struct Order* nextOrder = dequeueOrder(kitchenQueue);
                        if (nextOrder != NULL) {
                            printf("Memproses pesanan untuk meja %d...\n", nextOrder->tableNumber);
                            free(nextOrder);
                        } else {
                            printf("Tidak ada pesanan dalam antrean.\n");
                        }
                        pressEnterToContinue();
                    }
                } while (kitchenChoice != 3);
                break;
            }
            case 5: {
                int bstChoice;
                do {
                    clearScreen();
                    printf("MANAJEMEN DATA KASIR\n");
                    printf("1. Registrasi Kasir Baru (Insert BST)\n");
                    printf("2. Cari Data Kasir Berdasarkan ID (Search BST)\n");
                    printf("3. Tampilkan Semua Kasir Terurut (In-order Traversal)\n");
                    printf("4. Kembali ke Menu Utama\n");
                    printf("Pilih opsi (1-4): ");
                    scanf("%d", &bstChoice);
                    
                    if (bstChoice == 1) {
                        int id;
                        char name[50], shift[20];
                        printf("Masukkan ID Kasir Baru (Angka): ");
                        scanf("%d", &id);
                        getchar(); // Bersihkan buffer newline
                        
                        printf("Masukkan Nama Kasir       : ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = 0; // Hapus newline
                        
                        printf("Masukkan Shift (Pagi/Siang/Malam): ");
                        fgets(shift, sizeof(shift), stdin);
                        shift[strcspn(shift, "\n")] = 0;
                        
                        bstRoot = insertCashier(bstRoot, id, name, shift);
                        printf("\n[SUKSES] Kasir '%s' berhasil terdaftar di sistem!\n", name);
                        pressEnterToContinue();
                    }
                    else if (bstChoice == 2) {
                        int id;
                        printf("Masukkan ID Kasir yang dicari: ");
                        scanf("%d", &id);
                        
                        struct Cashier* found = searchCashier(bstRoot, id);
                        if (found != NULL) {
                            printf("\n--- DATA KASIR DITEMUKAN ---\n");
                            printf("ID Kasir : %d\n", found->cashierId);
                            printf("Nama     : %s\n", found->name);
                            printf("Shift    : %s\n", found->shift);
                        } else {
                            printf("\n[GAGAL] Kasir dengan ID %d tidak ditemukan.\n", id);
                        }
                        pressEnterToContinue();
                    }
                    else if (bstChoice == 3) {
                        printf("\n=== DAFTAR KASIR (TERURUT BERDASARKAN ID) ===\n");
                        printf("%-10s | %-25s | %-15s\n", "ID Kasir", "Nama Kasir", "Shift");
                        printf("--------------------------------------------------------\n");
                        
                        printInOrder(bstRoot); 
                        
                        printf("--------------------------------------------------------\n");
                        pressEnterToContinue();
                    }
                    else if (bstChoice == 4) {
                        printf("\nKembali ke Menu Utama.\n");
                        pressEnterToContinue();
                    }
                    else {
                        printf("\nPilihan tidak valid!\n");
                        pressEnterToContinue();
                    }
                } while (bstChoice != 4);
                break;
            }
            
            case 6:
                printf("\nKeluar dari aplikasi kasir. Terima kasih!\n");
                break;
                
            default:
                printf("\nPilihan tidak valid! Silakan masukkan angka 1-6.\n");
                pressEnterToContinue();
                break;
        }
    } while (mainChoice != 6);
    
    return 0;
} 