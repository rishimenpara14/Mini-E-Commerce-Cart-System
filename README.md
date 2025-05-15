# 🛒 Mini E-Commerce Cart System

A simple terminal-based shopping cart system built in **C/C++**, using a **stack data structure** implemented with a **singly linked list**. This project simulates e-commerce operations like adding/removing products, viewing the cart, and performing checkout — ideal for learning data structures in a practical way.

---

## ✨ Features

- 🛍️ Display available products  
- ➕ Add item to cart (Push operation)  
- ❌ Remove last added item (Pop operation)  
- 📦 View all items in the cart  
- 💳 Checkout and calculate total  
- 🧹 Clear all cart items  
- 🚪 Exit the application

---

## 🛠️ Tech Stack

- **Languages:** C / C++
- **Data Structure:** Stack using Singly Linked List
- **Interface:** Command-Line Interface (CLI)
- **Compiler:** GCC / G++

---

## ⚙️ How It Works

This project models a shopping cart as a **stack** data structure:

| Operation         | Stack Action  |
|------------------|---------------|
| Add Item         | PUSH          |
| Remove Last Item | POP           |
| Display Cart     | Traverse      |
| Checkout         | Traverse + Clear Stack |

Each new item is added to the **top** of the stack. Checkout shows all items and total cost, then clears the cart.

---
## 🚀 Installation

### 📥 Clone the Repository

```bash
git clone https://github.com/your-username/mini-ecommerce-cart.git
cd mini-ecommerce-cart
```
---

### ▶️ How to Run
## Run C Version
```bash
gcc cart.c -o cart
./cart
```
## Run C++ Version
```bash
g++ cart.cpp -o cart
./cart
```
