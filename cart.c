#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_name 50
#define max_products 10

typedef struct item {
    int id;
    char name[max_name];
    float price;
    int quantity;
    struct item* next;
} item;

typedef struct {
    item* top;
    int size;
} cart_stack;

typedef struct {
    int id;
    char name[max_name];
    float price;
    int stock;
} product;

product inventory[max_products];
int product_count = 0;

void initialize_inventory() {
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].price = 74999.99;
    inventory[0].stock = 10;

    inventory[1].id = 102;
    strcpy(inventory[1].name, "Smartphone");
    inventory[1].price = 37499.99;
    inventory[1].stock = 15;

    inventory[2].id = 103;
    strcpy(inventory[2].name, "Headphones");
    inventory[2].price = 7499.99;
    inventory[2].stock = 20;

    inventory[3].id = 104;
    strcpy(inventory[3].name, "Smartwatch");
    inventory[3].price = 14999.99;
    inventory[3].stock = 8;

    inventory[4].id = 105;
    strcpy(inventory[4].name, "Bluetooth Speaker");
    inventory[4].price = 5999.99;
    inventory[4].stock = 12;

    product_count = 5;
}

void display_products() {
    printf("\n=============== PRODUCT CATALOG ====================\n");
    printf("%-5s %-25s %-12s %-10s\n", "ID", "Name", "Price", "Stock");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < product_count; i++) {
        printf("%-5d %-25s Rs.%-10.2f %-10d\n", 
            inventory[i].id, 
            inventory[i].name, 
            inventory[i].price, 
            inventory[i].stock);
    }

    printf("------------------------------------------------------------\n\n");
}

product* find_product(int id) {
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].id == id) {
            return &inventory[i];
        }
    }
    return NULL;
}

cart_stack* create_cart() {
    cart_stack* cart = (cart_stack*)malloc(sizeof(cart_stack));
    cart->top = NULL;
    cart->size = 0;
    return cart;
}

int is_empty(cart_stack* cart) {
    return cart->top == NULL;
}

void push(cart_stack* cart, int id, const char* name, float price, int quantity) {
    item* new_item = (item*)malloc(sizeof(item));
    new_item->id = id;
    strcpy(new_item->name, name);
    new_item->price = price;
    new_item->quantity = quantity;

    new_item->next = cart->top;
    cart->top = new_item;
    cart->size++;

    printf("Added to cart: %s (Qty: %d)\n", name, quantity);
}

item* pop(cart_stack* cart) {
    if (is_empty(cart)) {
        return NULL;
    }

    item* temp = cart->top;
    cart->top = cart->top->next;
    cart->size--;

    printf("Removed from cart: %s\n", temp->name);
    return temp;
}

void display_cart(cart_stack* cart) {
    if (is_empty(cart)) {
        printf("Cart is empty!\n");
        return;
    }

    item* current = cart->top;
    float total = 0.0;

    printf("\n========== YOUR CART ==========\n");
    printf("%-5s %-30s %-10s %-10s %-10s\n", "ID", "Item", "Price", "Quantity", "Subtotal");
    printf("---------------------------------------------------------------------\n");

    while (current != NULL) {
        float subtotal = current->price * current->quantity;
        printf("%-5d %-30s Rs.%-9.2f %-10d Rs.%-9.2f\n", 
            current->id, current->name, current->price, 
            current->quantity, subtotal);

        total += subtotal;
        current = current->next;
    }

    printf("---------------------------------------------------------------------\n");
    printf("Total Items: %d\n", cart->size);
    printf("Total Amount: Rs.%.2f\n", total);
    printf("=============================\n\n");
}

void checkout(cart_stack* cart) {
    if (is_empty(cart)) {
        printf("Cannot checkout. Cart is empty!\n");
        return;
    }

    float total = 0.0;
    item* current = cart->top;

    while (current != NULL) {
        total += current->price * current->quantity;
        current = current->next;
    }

    printf("\n========== CHECKOUT ==========\n");
    printf("Total Amount: Rs.%.2f\n", total);
    printf("Thank you for your purchase!\n");
    printf("====================\n\n");

    current = cart->top;
    while (current != NULL) {
        product* product_ptr = find_product(current->id);
        if (product_ptr != NULL) {
            product_ptr->stock -= current->quantity;
        }
        current = current->next;
    }

    while (!is_empty(cart)) {
        item* item_ptr = pop(cart);
        free(item_ptr);
    }
}

void clear_cart(cart_stack* cart) {
    while (!is_empty(cart)) {
        item* item_ptr = pop(cart);
        free(item_ptr);
    }
    printf("Cart has been cleared!\n");
}

void add_to_cart_from_inventory(cart_stack* cart) {
    int product_id, quantity;

    display_products();

    printf("Enter product ID to add to cart (0 to cancel): ");
    scanf("%d", &product_id);

    if (product_id == 0) {
        printf("Operation cancelled.\n");
        return;
    }

    product* product_ptr = find_product(product_id);

    if (product_ptr == NULL) {
        printf("Product with ID %d not found!\n", product_id);
        return;
    }

    printf("Enter quantity (available: %d): ", product_ptr->stock);
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }

    if (quantity > product_ptr->stock) {
        printf("Not enough stock! Only %d available.\n", product_ptr->stock);
        return;
    }

    push(cart, product_ptr->id, product_ptr->name, product_ptr->price, quantity);
}

int main() {
    cart_stack* cart = create_cart();
    int choice;

    initialize_inventory();

    do {
        printf("\nE-COMMERCE CART SYSTEM\n");
        printf("1. Display Products\n");
        printf("2. Add Item\n");
        printf("3. Remove Last Added Item\n");
        printf("4. Display Cart\n");
        printf("5. Checkout\n");
        printf("6. Clear Cart\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_products();
                break;

            case 2:
                add_to_cart_from_inventory(cart);
                break;

            case 3: {
                item* removed = pop(cart);
                if (removed != NULL) {
                    free(removed);
                } else {
                    printf("Cart is already empty!\n");
                }
                break;
            }

            case 4:
                display_cart(cart);
                break;

            case 5:
                checkout(cart);
                break;

            case 6:
                clear_cart(cart);
                break;

            case 0:
                printf("Thank you for shopping with us!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    clear_cart(cart);
    free(cart);

    return 0;
}

