#infdef QUEUE_H
#define QUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int orderID;
    char menuName[50];
    int quantity;
    char status[20];
    struct Order *next;
} Order;

//front and rear
Order *front = NULL;
Order *rear = NULL;

//create new order
Order* createOrder(int orderID, char menuName[], int quantity) {
    Order *newOrder = (Order*)malloc(sizeof(Order));
    newOrder->orderID = orderID;
    strcpy(newOrder->menuName, menuName);
    newOrder->quantity = quantity;
    strcpy(newOrder->status, "Waiting");
    newOrder->next = NULL;
    return newOrder;
}

//enqueue order (insert)
void enqueueOrder(int orderID, char menuName[], int quantity) {
    Order *newOrder = createOrder(orderID, menuName, quantity);

    if (rear == NULL) {
        front = rear = newOrder;
        return;
    }

    rear->next = newOrder;
    rear = newOrder;
}

//dequeue order (delete)
void dequeueOrder() {
    if (front == NULL) {
        printf("No orders in kitchen queue.\n");
        return;
    }

    Order *temp = front;
    printf("Order Completed:\n");
    printf("ID: %d | Menu: %s | Qty: %d\n",
           temp->orderID, temp->menuName, temp->quantity);

    front = front->next;
    free(temp);

    if (front == NULL)
        rear = NULL;
}

//display queue
void displayKitchenQueue() {
    if (front == NULL) {
        printf("Kitchen queue is empty.\n");
        return;
    }

    Order *temp = front;
    printf("\n--- ANTRIAN PESANAN DAPUR ---\n");
    while (temp != NULL) {
        printf("ID: %d | Menu: %s | Qty: %d | Status: %s\n",
               temp->orderID,
               temp->menuName,
               temp->quantity,
               temp->status);
        temp = temp->next;
    }
}

//status update
void startCooking() {
    if (front == NULL) {
        printf("No order to cook.\n");
        return;
    }

    strcpy(front->status, "Cooking");
    printf("Now Cooking:\n");
    printf("ID: %d | Menu: %s\n",
           front->orderID, front->menuName);
}

//main
int main() {
    int choice, orderID, quantity;
    char menuName[50];

    do {
        printf("\nSISTEM ANTRIAN DAPUR\n");
        printf("1. Tambah Pesanan \n");
        printf("2. Mulai Masak Pesanan Terdepan\n");
        printf("3. Pesanan Selesai (Dequeue)\n");
        printf("4. Lihat Antrian Dapur\n");
        printf("5. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Order ID: ");
                scanf("%d", &orderID);
                printf("Nama Menu: ");
                scanf(" %[^\n]", menuName);
                printf("Jumlah: ");
                scanf("%d", &quantity);
                enqueueOrder(orderID, menuName, quantity);
                printf("Pesanan masuk antrian dapur.\n");
                break;

            case 2:
                startCooking();
                break;

            case 3:
                dequeueOrder();
                break;

            case 4:
                displayKitchenQueue();
                break;

            case 5:
                printf("Sistem dapur ditutup.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 5);

    return 0;
}