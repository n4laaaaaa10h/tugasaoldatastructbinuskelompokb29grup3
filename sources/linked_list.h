#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h" // Membutuhkan referensi struct Menu dari Hash Table

// Node untuk item di dalam keranjang belanja
struct CartItem {
    struct Menu* menuRef; // Menunjuk ke menu asli yang ada di Hash Table
    int quantity;
    struct CartItem* prev;
    struct CartItem* next;
};

// Struktur Utama untuk Keranjang Belanja
struct OrderCart {
    struct CartItem* head;
    struct CartItem* tail;
    int totalPrice;
};

// Fungsi membuat keranjang baru yang kosong
struct OrderCart* createCart() {
    struct OrderCart* cart = (struct OrderCart*)malloc(sizeof(struct OrderCart));
    cart->head = NULL;
    cart->tail = NULL;
    cart->totalPrice = 0;
    return cart;
}

// 1. INSERT: Menambahkan menu ke dalam keranjang belanja
void addToCart(struct OrderCart* cart, struct Menu* menu, int qty) {
    if (menu == NULL || qty <= 0) return;

    // Cek apakah menu ini sudah ada di keranjang, jika ada tinggal tambah Qty
    struct CartItem* curr = cart->head;
    while (curr != NULL) {
        if (curr->menuRef->id == menu->id) {
            curr->quantity += qty;
            cart->totalPrice += (menu->price * qty);
            printf("%d x '%s' ditambahkan lagi ke keranjang.\n", qty, menu->name);
            return;
        }
        curr = curr->next;
    }

    // Jika belum ada, buat node baru (Insert di Tail)
    struct CartItem* newItem = (struct CartItem*)malloc(sizeof(struct CartItem));
    newItem->menuRef = menu;
    newItem->quantity = qty;
    newItem->next = NULL;
    newItem->prev = NULL;

    if (cart->head == NULL) { // Jika keranjang masih kosong
        cart->head = newItem;
        cart->tail = newItem;
    } else { // Tempel di paling belakang
        cart->tail->next = newItem;
        newItem->prev = cart->tail;
        cart->tail = newItem;
    }
    
    cart->totalPrice += (menu->price * qty);
    printf("%d x '%s' berhasil dimasukkan ke keranjang!\n", qty, menu->name);
}

// 2. READ: Menampilkan isi keranjang belanja secara realtime
void viewCart(struct OrderCart* cart) {
    printf("\n--- ISI KERANJANG BELANJA CURRENTLY ---\n");
    if (cart->head == NULL) {
        printf("Keranjang masih kosong.\n");
        return;
    }

    struct CartItem* curr = cart->head;
    printf("%-5s | %-25s | %-5s | %-12s\n", "ID", "Nama Menu", "Qty", "Subtotal");
    printf("-------------------------------------------------------\n");
    while (curr != NULL) {
        int subtotal = curr->menuRef->price * curr->quantity;
        printf("%-5d | %-25s | %-5d | Rp %-12d\n", 
               curr->menuRef->id, curr->menuRef->name, curr->quantity, subtotal);
        curr = curr->next;
    }
    printf("-------------------------------------------------------\n");
    printf("TOTAL HARGA: Rp %d\n", cart->totalPrice);
}

// 3. DELETE: Menghapus satu item dari keranjang belanja
void removeFromCart(struct OrderCart* cart, int menuId) {
    if (cart->head == NULL) return;

    struct CartItem* curr = cart->head;
    while (curr != NULL) {
        if (curr->menuRef->id == menuId) {
            // Kurangi totalPrice keranjang
            cart->totalPrice -= (curr->menuRef->price * curr->quantity);

            // Pengondisian pemutusan pointer linked list
            if (curr == cart->head && curr == cart->tail) { // Hanya ada 1 item
                cart->head = NULL;
                cart->tail = NULL;
            } else if (curr == cart->head) { // Hapus di Head
                cart->head = curr->next;
                cart->head->prev = NULL;
            } else if (curr == cart->tail) { // Hapus di Tail
                cart->tail = curr->prev;
                cart->tail->next = NULL;
            } else { // Hapus di Tengah
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            printf("Menu '%s' berhasil dihapus dari keranjang.\n", curr->menuRef->name);
            free(curr);
            return;
        }
        curr = curr->next;
    }
    printf("Menu dengan ID %d tidak ditemukan di keranjang.\n", menuId);
}

// Menghapus seluruh isi keranjang (Clear Cart) setelah checkout/batal
void clearCart(struct OrderCart* cart) {
    struct CartItem* curr = cart->head;
    while (curr != NULL) {
        struct CartItem* temp = curr;
        curr = curr->next;
        free(temp);
    }
    cart->head = NULL;
    cart->tail = NULL;
    cart->totalPrice = 0;
}

#endif