# Online Shopping Cart System

## Overview

The **Online Shopping Cart System** is a console-based C++ application that enables users to view products, add items to a shopping cart, modify cart contents, and proceed to checkout with payment. It demonstrates object-oriented programming principles, including inheritance and polymorphism, with a focus on clean, modular code and error handling.

## Features

- **Display Products**: View a list of available products with names and prices.
- **Add to Cart**: Add selected products to the shopping cart with a specified quantity.
- **View Cart**: Display all items in the cart, their quantities, and total cost.
- **Modify Cart**: Change item quantities or remove items from the cart.
- **Checkout**: Process payment for all items in the cart.
- **Persistent Product Data**: Loads product data from a file, making it easy to modify products without changing the code.

## Installation

1. **Clone the Repository**
    ```bash
    git clone https://github.com/username/online-shopping-cart-system.git
    cd online-shopping-cart-system
    ```

2. **Compile the Program**
    Compile with any C++ compiler, e.g., `g++`:
    ```bash
    g++ -o shopping_cart main.cpp
    ```

3. **Run the Program**
    ```bash
    ./shopping_cart
    ```

## Usage

1. **Add Products File**: Ensure you have a `products.txt` file in the project directory with products listed in the following format:

    ```
    1 Apple 0.99
    2 Banana 0.59
    3 Orange 1.25
    ```

2. **Run the Application**:
   - **Main Menu**:
     - `1. Display Products`: View all available products.
     - `2. Add to Cart`: Add products by entering their ID and desired quantity.
     - `3. View Cart`: Display the items currently in the cart.
     - `4. Modify Cart`: Adjust quantities or remove items.
     - `5. Checkout`: Enter card details for payment and confirm the order.
     - `6. Exit`: Exit the application.

3. **Error Handling**: The program handles invalid inputs and displays error messages if inputs are not as expected.

## Code Structure

- **Classes**:
  - `Product`: Abstract base class representing a generic product.
  - `GeneralProduct`: Derived class representing a standard product with name and price attributes.
  - `CartItem`: Represents an item in the shopping cart with product and quantity.
  - `ShoppingCart`: Manages a collection of `CartItem`s, provides methods to add, view, modify, and checkout items.
  - `User`: Contains a `ShoppingCart` instance and user details.

- **Functions**:
  - `loadProductsFromFile()`: Reads product details from `products.txt`.
  - `displayProducts()`: Displays available products.
  - `addToCart()`: Adds a selected product to the user's cart.
  - `viewCart()`, `modifyCart()`, `checkout()`: Handle cart interactions.

## Example

```
Welcome John Doe to the Online Shopping Cart System

1. Display Products
2. Add to Cart
3. View Cart
4. Modify Cart
5. Checkout
6. Exit
Enter your choice: 1

Available Products:
ID: 1, Name: Apple, Price: $0.99
ID: 2, Name: Banana, Price: $0.59
ID: 3, Name: Orange, Price: $1.25
```

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests with improvements.

1. Fork the project.
2. Create a new feature branch (`git checkout -b feature/new-feature`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature/new-feature`).
5. Open a pull request.

## License

This project is open-source and available under the [MIT License](LICENSE).
