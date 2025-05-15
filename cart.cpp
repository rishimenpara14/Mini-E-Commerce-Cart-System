#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define MAX_NAME 50
#define MAX_PRODUCTS 10

class Item {
public:
    int id;
    string name;
    float price;
    int quantity;
    Item* next;

    Item(int i, const string& n, float p, int q) : id(i), name(n), price(p), quantity(q), next(nullptr) {}
};

class CartStack {
public:
    Item* top;
    int size;

    CartStack() : top(nullptr), size(0) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int id, const string& name, float price, int quantity) {
        Item* newItem = new Item(id, name, price, quantity);
        newItem->next = top;
        top = newItem;
        size++;
        cout << "Added to cart: " << name << " (Qty: " << quantity << ")\n";
    }

    Item* pop() {
        if (isEmpty()) return nullptr;
        Item* temp = top;
        top = top->next;
        size--;
        cout << "Removed from cart: " << temp->name << "\n";
        return temp;
    }

    void clear() {
        while (!isEmpty()) {
            Item* temp = pop();
            delete temp;
        }
        cout << "Cart has been cleared!\n";
    }
};

class Product {
public:
    int id;
    string name;
    float price;
    int stock;

    Product() : id(0), name(""), price(0.0f), stock(0) {}
    Product(int i, const string& n, float p, int s) : id(i), name(n), price(p), stock(s) {}
};

Product inventory[MAX_PRODUCTS];
int productCount = 0;

void initializeInventory() {
    inventory[0] = Product(101, "Laptop", 74999.99f, 10);
    inventory[1] = Product(102, "Smartphone", 37499.99f, 15);
    inventory[2] = Product(103, "Headphones", 7499.99f, 20);
    inventory[3] = Product(104, "Smartwatch", 14999.99f, 8);
    inventory[4] = Product(105, "Bluetooth Speaker", 5999.99f, 12);
    productCount = 5;
}

void displayProducts() {
    cout << "\n=============== PRODUCT CATALOG ====================\n";
    cout << left << setw(6) << "ID"
         << setw(25) << "Name"
         << setw(14) << "Price"
         << setw(8) << "Stock" << "\n";
    cout << "------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < productCount; i++) {
        cout << left << setw(6) << inventory[i].id
             << setw(25) << inventory[i].name
             << "Rs." << setw(10) << inventory[i].price
             << setw(8) << inventory[i].stock << "\n";
    }
    cout << "------------------------------------------------------------\n\n";
}

Product* findProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) return &inventory[i];
    }
    return nullptr;
}

void displayCart(CartStack* cart) {
    if (cart->isEmpty()) {
        cout << "Cart is empty!\n";
        return;
    }

    cout << "\n========== YOUR CART ==========\n";
    cout << left << setw(6) << "ID"
         << setw(30) << "Item"
         << setw(12) << "Price"
         << setw(10) << "Quantity"
         << setw(12) << "Subtotal" << "\n";
    cout << "-----------------------------------------------------------------\n";

    float total = 0.0f;
    Item* current = cart->top;
    cout << fixed << setprecision(2);

    while (current != nullptr) {
        float subtotal = current->price * current->quantity;
        cout << left << setw(6) << current->id
             << setw(30) << current->name
             << "Rs." << setw(10) << current->price
             << setw(10) << current->quantity
             << "Rs." << setw(10) << subtotal << "\n";
        total += subtotal;
        current = current->next;
    }
    cout << "-----------------------------------------------------------------\n";
    cout << "Total Items: " << cart->size << "\n";
    cout << "Total Amount: Rs." << total << "\n";
    cout << "=============================\n\n";
}

void addToCartFromInventory(CartStack* cart) {
    displayProducts();

    int productId, quantity;
    cout << "Enter product ID to add to cart (0 to cancel): ";
    cin >> productId;
    if (productId == 0) {
        cout << "Operation cancelled.\n";
        return;
    }

    Product* productPtr = findProduct(productId);
    if (productPtr == nullptr) {
        cout << "Product with ID " << productId << " not found!\n";
        return;
    }

    cout << "Enter quantity (available: " << productPtr->stock << "): ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Invalid quantity!\n";
        return;
    }
    if (quantity > productPtr->stock) {
        cout << "Not enough stock! Only " << productPtr->stock << " available.\n";
        return;
    }

    cart->push(productPtr->id, productPtr->name, productPtr->price, quantity);
}

void checkout(CartStack* cart) {
    if (cart->isEmpty()) {
        cout << "Cannot checkout. Cart is empty!\n";
        return;
    }

    float total = 0.0f;
    Item* current = cart->top;
    while (current != nullptr) {
        total += current->price * current->quantity;
        current = current->next;
    }

    cout << "\n========== CHECKOUT ==========\n";
    cout << "Total Amount: Rs." << fixed << setprecision(2) << total << "\n";
    cout << "Thank you for your purchase!\n";
    cout << "====================\n\n";

    // Deduct stock
    current = cart->top;
    while (current != nullptr) {
        Product* productPtr = findProduct(current->id);
        if (productPtr != nullptr) {
            productPtr->stock -= current->quantity;
        }
        current = current->next;
    }

    cart->clear();
}

int main() {
    CartStack* cart = new CartStack();
    initializeInventory();

    int choice;
    do {
        cout << "\nE-COMMERCE CART SYSTEM\n";
        cout << "1. Display Products\n";
        cout << "2. Add Item\n";
        cout << "3. Remove Last Added Item\n";
        cout << "4. Display Cart\n";
        cout << "5. Checkout\n";
        cout << "6. Clear Cart\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts();
                break;
            case 2:
                addToCartFromInventory(cart);
                break;
            case 3: {
                Item* removed = cart->pop();
                if (removed != nullptr) {
                    delete removed;
                } else {
                    cout << "Cart is already empty!\n";
                }
                break;
            }
            case 4:
                displayCart(cart);
                break;
            case 5:
                checkout(cart);
                break;
            case 6:
                cart->clear();
                break;
            case 0:
                cout << "Thank you for shopping with us!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    cart->clear();
    delete cart;
    return 0;
}
