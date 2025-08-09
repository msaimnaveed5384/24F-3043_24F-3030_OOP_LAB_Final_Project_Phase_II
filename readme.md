# E-Commerce Management System

A console-based C++ application that simulates a complete e-commerce platform with Admin, Seller, and Buyer roles. This project demonstrates object-oriented programming concepts, file-based data persistence, and a modular approach to software design. It is ideal for learning about user management, product handling, order processing, and role-based access control in C++.

---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Technical Highlights](#technical-highlights)
- [How to Run](#how-to-run)
- [Future Improvements](#future-improvements)
- [License](#license)

---

## Features

### 1. Authentication and User Management
- **Registration** with validation for email, date of birth, password, and role selection.
- **Login** with role-based access control.
- **Roles:**
  - **Admin:** Full platform control.
  - **Seller:** Manage products and track revenue.
  - **Buyer:** Browse, search, add to cart, and checkout.

### 2. Admin Features
- Approve or reject products before they are visible to buyers.
- Manage buyers and sellers: approve sellers, update seller info, remove accounts.
- View reports:
  - Total platform revenue.
  - Most active buyers by order count.
- Delete products directly.
- View all registered buyers/sellers and their products.

### 3. Seller Features
- Add products in three categories:
  - **Electronics** (with warranty)
  - **Books** (with author name)
  - **Clothing** (with size)
- Update products: name, category, price, quantity, and category-specific details.
- Delete products.
- View only their listed products.
- Track revenue per product based on orders.

### 4. Buyer Features
- Browse all approved products.
- Search products by name.
- Shopping cart:
  - Add items (quantity fixed to 1 per add).
  - Remove items.
  - View cart contents.
- Checkout:
  - Generate an order with unique ID.
  - Update product quantities in inventory.
- View order history.

### 5. Order Management
- Orders are saved to `Order.txt` with details:
  - Order ID, buyer name, date.
  - Products purchased (ID, seller ID, name, category, price, quantity).
  - Shipping status (default: Pending).
  - Total order amount.

### 6. File-Based Data Persistence
- Data is stored and retrieved using text files:
  - `Admins.txt` – Admin accounts
  - `Seller.txt` – Seller accounts
  - `Buyer.txt` – Buyer accounts
  - `Products.txt` – All products (with category-specific info)
  - `Order.txt` – Order records

---

## Project Structure

```
├── main.cpp              # Application entry point
├── AuthSystem.h/.cpp     # Registration & Login logic
├── FileManager.h/.cpp    # File operations for products, users, and orders
├── User.h/.cpp           # User, Admin, Seller, Buyer classes
├── Product.h/.cpp        # Base and derived product classes
├── Cart.h/.cpp           # Shopping cart template
├── Order.h/.cpp          # Order management
├── *.txt                 # Data storage files
```

---

## Technical Highlights

- **Object-Oriented Programming:** Classes, inheritance, and polymorphism for modular code.
- **Operator Overloading:**  
  - `Cart::operator+=` to add products to cart.
  - `Cart::operator-=` to remove products from cart.
- **File I/O:** Persistent storage using standard C++ file streams.
- **Exception Handling:** Input validation and error handling.
- **Dynamic Casting:** Identify product category at runtime.

---

## How to Run

1. **Compile all `.cpp` files together.**  
   Example using g++:
   ```bash
   g++ main.cpp AuthSystem.cpp FileManager.cpp User.cpp Product.cpp Cart.cpp Order.cpp -o ecommerce
   ```
   *(Adjust the command if your file names or structure differ.)*

2. **Run the executable.**
   ```bash
   ./ecommerce
   ```

3. **Interact with the system.**
   - Use the main menu to Login, Register, or view Info.
   - Follow the role-specific menus for Admin, Seller, or Buyer features.

---

## Future Improvements

- Add shipping status updates for orders.
- Allow quantity selection for cart items.
- Implement discounts and promotions.
- Introduce a GUI interface for enhanced user experience.

---

## License

This project is open source and available under the [MIT License](LICENSE).
