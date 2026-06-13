#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "sources/hash_table.h"
#include "sources/trie.h"
#include "sources/linked_list.h"
#include "sources/stack.h"
#include "sources/queue.h"
#include "sources/bst.h"

// Fungsi pembantu untuk membersihkan layar console
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk menekan enter sebelum lanjut
void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar(); // Menangkap karakter newline sisa
    getchar(); // Menunggu input enter dari user
}

int main() {
    // 1. Inisialisasi & Isi Data Master Menu (Hash Table)
    struct MenuHashTable* menuTable = createHashTable();
    insertMenu(menuTable, 101, "Nasi Goreng Spesial", 25000);
    insertMenu(menuTable, 102, "Mie Goreng Ayam", 22000);
    insertMenu(menuTable, 103, "Ayam Bakar Taliwang", 35000);
    insertMenu(menuTable, 201, "Es Teh Manis", 5000);
    insertMenu(menuTable, 202, "Jus Alpukat Kocok", 15000);

    // 2. Inisialisasi & Isi Data Pencarian (Trie)
    struct TrieNode* trieRoot = createTrieNode();
    insertTrie(trieRoot, "Nasi Goreng Spesial");
    insertTrie(trieRoot, "Mie Goreng Ayam");
    insertTrie(trieRoot, "Ayam Bakar Taliwang");
    insertTrie(trieRoot, "Es Teh Manis");
    insertTrie(trieRoot, "Jus Alpukat Kocok");

    // 3. Inisialisasi Antrean Dapur (Queue)
    struct KitchenQueue* kitchenQueue = createQueue();

    // 4. Inisialisasi & Isi Data Kasir (BST)
    Node* bstRoot = NULL;
    bstRoot = insertBST(bstRoot, 201, "Andi Wijaya", "Makanan", 25000);
    bstRoot = insertBST(bstRoot, 105, "Siti Rahma", "Minuman", 5000);
    bstRoot = insertBST(bstRoot, 304, "Budi Santoso", "Makanan", 35000);

    int mainChoice = 0;

    do {
        clearScreen();
        printf("===========================================\n");
        printf("   SISTEM MANAJEMEN KASIR - RESTORAN XYZ   \n");
        printf("===========================================\n");
        printf("1. Manajemen Master Menu (CRUD - Hash Table)\n");
        printf("2. Cari Menu (Auto-complete - Trie)\n");
        printf("3. Transaksi Baru / Keranjang (Linked List & Stack)\n");
        printf("4. Antrean Pesanan Dapur (Queue)\n");
        printf("5. Manajemen Data Menu Pohon (BST)\n");
        printf("6. Keluar Aplikasi\n");
        printf("===========================================\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: { // Sub-menu CRUD Hash Table
                int crudChoice;
                do {
                    clearScreen();
                    printf("=== MANAJEMEN MASTER MENU (HASH TABLE) ===\n");
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
                        getchar(); // bersihkan buffer newline
                        printf("Masukkan Nama Menu: ");  fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = 0; // hapus newline di akhir string
                        printf("Masukkan Harga Menu: "); scanf("%d", &price);

                        insertMenu(menuTable, id, name, price);
                        insertTrie(trieRoot, name); // Otomatis daftarkan ke trie autocomplete juga
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

            case 2: {
                clearScreen();
                printf("=== CARI MENU AUTO-COMPLETE (TRIE) ===\n");
                char query[50];
                printf("Ketik awal nama menu yang dicari: ");
                getchar(); // Bersihkan buffer
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0; // Hapus newline

                printf("\nRekomendasi menu untuk '%s':\n", query);
                // SINKRONISASI: Menggunakan printAutoSuggestions yang didefinisikan di trie.h
                int found = printAutoSuggestions(trieRoot, query); 
                if (!found) {
                    printf("Tidak ada menu dengan awalan tersebut.\n");
                }
                pressEnterToContinue();
                break;
            }

            case 3: { // TRANSAKSI BARU & KERANJANG (LINKED LIST & STACK)
                struct OrderCart* cart = createCart();
                struct UndoStack* undoStack = createStack();
                int txChoice;

                do {
                    clearScreen();
                    printf("===========================================\n");
                    printf("       MODE TRANSAKSI / KASIR BARU         \n");
                    printf("===========================================\n");
                    viewCart(cart); 

                    printf("\nOpsi Transaksi:\n");
                    printf("1. Tambah Menu ke Keranjang (Insert - Linked List)\n");
                    printf("2. Hapus Menu dari Keranjang (Delete - Linked List)\n");
                    printf("3. BATALKAN Input Terakhir (Undo - Stack)\n");
                    printf("4. Selesaikan Pembayaran & Kirim ke Dapur\n");
                    printf("5. Batalkan Seluruh Transaksi & Kembali\n");
                    printf("===========================================\n");
                    printf("Pilih opsi (1-5): ");
                    scanf("%d", &txChoice);

                    if (txChoice == 1) {
                        int id, qty;
                        viewAllMenus(menuTable); 
                        printf("Masukkan ID Menu yang dipesan: ");
                        scanf("%d", &id);

                        struct Menu* targetMenu = searchMenu(menuTable, id);
                        if (targetMenu != NULL) {
                            printf("Masukkan Jumlah (Quantity): ");
                            scanf("%d", &qty);
                            if (qty > 0) {
                                addToCart(cart, targetMenu, qty);
                                pushUndo(undoStack, id, qty); 
                            } else {
                                printf("Jumlah pesanan harus lebih dari 0!\n");
                            }
                        } else {
                            printf("ID Menu tidak ditemukan di daftar master menu.\n");
                        }
                        pressEnterToContinue();
                    }
                    else if (txChoice == 2) {
                        if (cart->head == NULL) {
                            printf("Keranjang masih kosong, tidak ada yang bisa dihapus.\n");
                        } else {
                            int id;
                            printf("Masukkan ID Menu yang ingin didelete dari keranjang: ");
                            scanf("%d", &id);
                            removeFromCart(cart, id);
                        }
                        pressEnterToContinue();
                    }
                    else if (txChoice == 3) {
                        struct UndoAction lastAction = popUndo(undoStack);
                        if (lastAction.menuId != -1) {
                            struct Menu* menuToUndo = searchMenu(menuTable, lastAction.menuId);
                            if (menuToUndo != NULL) {
                                removeFromCart(cart, lastAction.menuId);
                                printf("-> BERHASIL UNDO: Input '%d x %s' telah dibatalkan!\n", 
                                       lastAction.quantity, menuToUndo->name);
                            }
                        } else {
                            printf("Tidak ada aksi input yang bisa di-Undo.\n");
                        }
                        pressEnterToContinue();
                    }
                    else if (txChoice == 4) {
                        if (cart->head == NULL) {
                            printf("Gagal bayar! Keranjang masih kosong.\n");
                            pressEnterToContinue();
                        } else {
                            clearScreen();
                            printf("===========================================\n");
                            printf("             RINGKASAN PEMBAYARAN          \n");
                            printf("===========================================\n");
                            viewCart(cart);

                            int bayar;
                            printf("\nTotal yang harus dibayar: Rp %d\n", cart->totalPrice);
                            printf("Masukkan Uang Pembayaran : Rp ");
                            scanf("%d", &bayar);

                            if (bayar >= cart->totalPrice) {
                                printf("Kembalian                : Rp %d\n", bayar - cart->totalPrice);
                                printf("\n[SUKSES] Pembayaran Berhasil!\n");
                                printf("Pesanan secara otomatis dicetak dan dikirim ke Antrean Dapur.\n");

                                // Mengirim data ke antrean dapur (queue.h)
                                enqueueOrder(kitchenQueue, cart); 

                                clearCart(cart);
                                clearStack(undoStack);
                                txChoice = 5; 
                            } else {
                                printf("[GAGAL] Uang yang dibayarkan kurang Rp %d. Transaksi ditunda.\n", 
                                       cart->totalPrice - bayar);
                            }
                            pressEnterToContinue();
                        }
                    }
                    else if (txChoice == 5) {
                        clearCart(cart);
                        clearStack(undoStack);
                        free(cart);
                        free(undoStack);
                        printf("\nKembali ke Menu Utama. Sesi keranjang dibersihkan.\n");
                        pressEnterToContinue();
                    }

                } while (txChoice != 5);
                break;
            }

            case 4: { // ANTREAN PESANAN DAPUR (QUEUE)
                int kitchenChoice;
                do {
                    clearScreen();
                    printf("===========================================\n");
                    printf("        MANAJEMEN ANTREAN DAPUR (QUEUE)    \n");
                    printf("===========================================\n");

                    viewKitchenQueue(kitchenQueue); 

                    printf("\nOpsi Dapur:\n");
                    printf("1. Proses / Selesaikan Pesanan Terdepan (Dequeue)\n");
                    printf("2. Kembali ke Menu Utama\n");
                    printf("===========================================\n");
                    printf("Pilih opsi (1-2): ");
                    scanf("%d", &kitchenChoice);

                    if (kitchenChoice == 1) {
                        printf("\nMemproses pesanan...\n");
                        dequeueKitchen(kitchenQueue); 
                        pressEnterToContinue();
                    }
                    else if (kitchenChoice == 2) {
                        printf("\nKembali ke Menu Utama.\n");
                        pressEnterToContinue();
                    }
                    else {
                        printf("\nPilihan tidak valid!\n");
                        pressEnterToContinue();
                    }
                } while (kitchenChoice != 2);
                break;
            }

            case 5: { // MANAJEMEN DATA MENU (BST)
                int bstChoice;
                do {
                    clearScreen();
                    printf("===========================================\n");
                    printf("       MANAJEMEN DATA MENU POHON (BST)     \n");
                    printf("===========================================\n");
                    printf("1. Tambah Data Menu BST (Insert BST)\n");
                    printf("2. Cari Data Menu BST (Search BST)\n");
                    printf("3. Tampilkan Semua Menu Terurut (In-order Traversal)\n");
                    printf("4. Kembali ke Menu Utama\n");
                    printf("===========================================\n");
                    printf("Pilih opsi (1-4): ");
                    scanf("%d", &bstChoice);

                    if (bstChoice == 1) {
                        int id;
                        char name[50], category[20];
                        float price;
                        printf("Masukkan ID Menu Baru (Angka): ");
                        scanf("%d", &id);
                        getchar(); 

                        printf("Masukkan Nama Menu          : ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = 0; 

                        printf("Masukkan Kategori Menu      : ");
                        fgets(category, sizeof(category), stdin);
                        category[strcspn(category, "\n")] = 0;

                        printf("Masukkan Harga Menu         : ");
                        scanf("%f", &price);

                        bstRoot = insertBST(bstRoot, id, name, category, price);
                        printf("\n[SUKSES] Menu '%s' berhasil terdaftar di BST!\n", name);
                        pressEnterToContinue();
                    }
                    else if (bstChoice == 2) {
                        int id;
                        printf("Masukkan ID Menu yang dicari: ");
                        scanf("%d", &id);

                        Node* found = searchBST(bstRoot, id);
                        if (found != NULL) {
                            printf("\n--- DATA MENU BST DITEMUKAN ---\n");
                            printf("ID       : %d\n", found->id);
                            printf("Nama     : %s\n", found->name);
                            printf("Kategori : %s\n", found->category);
                            printf("Harga    : Rp %.2f\n", found->price);
                        } else {
                            printf("\n[GAGAL] Menu dengan ID %d tidak ditemukan.\n", id);
                        }
                        pressEnterToContinue();
                    }
                    else if (bstChoice == 3) {
                        printf("\n=== DAFTAR MENU POHON (TERURUT BERDASARKAN ID) ===\n");
                        printf("%-10s | %-25s | %-15s | %-12s\n", "ID Menu", "Nama Menu", "Kategori", "Harga");
                        printf("------------------------------------------------------------------------\n");

                        printInOrder(bstRoot); 

                        printf("------------------------------------------------------------------------\n");
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