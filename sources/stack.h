#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_UNDO 50

// Struktur penampung histori aksi transaksi
struct UndoAction {
    int menuId;     // ID menu yang dimasukkan
    int quantity;   // Berapa jumlah yang dimasukkan
};

// Struktur Stack Utama
struct UndoStack {
    struct UndoAction actions[MAX_UNDO];
    int top; // Indeks posisi paling atas dari stack
};

// Fungsi membuat Stack baru
struct UndoStack* createStack() {
    struct UndoStack* stack = (struct UndoStack*)malloc(sizeof(struct UndoStack));
    stack->top = -1; // -1 menandakan stack kosong
    return stack;
}

// PUSH: Memasukkan riwayat transaksi terakhir ke puncak stack
void pushUndo(struct UndoStack* stack, int menuId, int qty) {
    if (stack->top >= MAX_UNDO - 1) {
        // Jika stack penuh, geser data lama ke bawah agar muat data baru
        for (int i = 0; i < stack->top; i++) {
            stack->actions[i] = stack->actions[i + 1];
        }
        stack->top--;
    }
    stack->top++;
    stack->actions[stack->top].menuId = menuId;
    stack->actions[stack->top].quantity = qty;
}

// POP: Mengambil riwayat paling terakhir (LIFO) untuk dibatalkan
struct UndoAction popUndo(struct UndoStack* stack) {
    struct UndoAction emptyAction = {-1, 0};
    if (stack->top == -1) {
        return emptyAction; // Mengembalikan tanda kalau stack kosong
    }
    struct UndoAction lastAction = stack->actions[stack->top];
    stack->top--; // Turunkan pointer top
    return lastAction;
}

// Mengosongkan riwayat stack jika transaksi sudah dibayar atau di-reset
void clearStack(struct UndoStack* stack) {
    stack->top = -1;
}

#endif