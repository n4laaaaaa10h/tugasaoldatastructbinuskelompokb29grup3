#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h" // Kita butuh ini karena antrean menyimpan data keranjang belanja (OrderCart)

// Node untuk menyimpan antrean pesanan dapur
struct OrderTicket {
    int ticketId;
    struct OrderCart* cartDetails; // Menyimpan seluruh item pesanan dari kasir
    struct OrderTicket* next;
};

// Struktur Utama Queue (FIFO)
struct KitchenQueue {
    struct OrderTicket* front;
    struct OrderTicket* rear;
    int totalQueueCount;
};

// Fungsi membuat Antrean Dapur baru yang kosong
struct KitchenQueue* createQueue() {
    struct KitchenQueue* q = (struct KitchenQueue*)malloc(sizeof(struct KitchenQueue));
    q->front = NULL;
    q->rear = NULL;
    q->totalQueueCount = 0;
    return q;
}

// 1. ENQUEUE: Memasukkan pesanan kasir yang sudah dibayar ke antrean dapur paling belakang
void enqueueOrder(struct KitchenQueue* q, struct OrderCart* cart) {
    if (cart == NULL || cart->head == NULL) return;

    // Membuat tiket antrean baru
    struct OrderTicket* newTicket = (struct OrderTicket*)malloc(sizeof(struct OrderTicket));
    
    // Alokasi keranjang baru khusus untuk dapur agar tidak hilang saat keranjang di main dibersihkan
    newTicket->cartDetails = createCart();
    struct CartItem* currItem = cart->head;
    while (currItem != NULL) {
        addToCart(newTicket->cartDetails, currItem->menuRef, currItem->quantity);
        currItem = currItem->next;
    }
    
    q->totalQueueCount++;
    newTicket->ticketId = q->totalQueueCount;
    newTicket->next = NULL;

    // Jika antrean masih kosong
    if (q->rear == NULL) {
        q->front = newTicket;
        q->rear = newTicket;
    } else {
        q->rear->next = newTicket;
        q->rear = newTicket;
    }
    printf("Pesanan berhasil diteruskan ke Dapur! [Nomor Tiket Antrean: #%d]\n", newTicket->ticketId);
}

// 2. DEQUEUE: Mengeluarkan/menyelesaikan pesanan terdepan yang sudah selesai dimasak
void dequeueKitchen(struct KitchenQueue* q) {
    if (q->front == NULL) {
        printf("Tidak ada antrean pesanan aktif di dapur saat ini.\n");
        return;
    }

    struct OrderTicket* temp = q->front;
    printf("[SELESAI] Tiket Antrean #%d telah disajikan ke pelanggan!\n", temp->ticketId);

    // Geser pointer depan ke antrean berikutnya
    q->front = q->front->next;

    // Jika setelah digeser antrean menjadi kosong
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Bebaskan memori tiket dan isi keranjang belanja di dalamnya
    clearCart(temp->cartDetails);
    free(temp->cartDetails);
    free(temp);
}

// 3. READ/VIEW: Melihat daftar antrean pesanan aktif yang harus dimasak dapur
void viewKitchenQueue(struct KitchenQueue* q) {
    if (q->front == NULL) {
        printf("[INFO] Dapur Bersih! Belum ada antrean pesanan masuk.\n");
        return;
    }

    printf("Daftar Antrean Dapur Aktif:\n");
    struct OrderTicket* currTicket = q->front;
    while (currTicket != NULL) {
        printf("\n----------------------------------------\n");
        printf(" TIKET PESANAN #%d\n", currTicket->ticketId);
        printf("----------------------------------------\n");
        
        struct CartItem* item = currTicket->cartDetails->head;
        while (item != NULL) {
            printf("- %d x %s\n", item->quantity, item->menuRef->name);
            item = item->next;
        }
        currTicket = currTicket->next;
    }
    printf("\n----------------------------------------\n");
}

#endif