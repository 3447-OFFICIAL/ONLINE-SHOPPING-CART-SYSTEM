#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <memory> // Include for smart pointers

using namespace std;

// Abstract base class for products
class Product {
public:
    virtual ~Product() = default; // Virtual destructor for proper cleanup of derived classes
    virtual string getName() const = 0; // Pure virtual function to get the product name
    virtual float getPrice() const = 0; // Pure virtual function to get the product price
};

// Derived class for general products
class GeneralProduct : public Product {
private:
    int id;
    string name;
    float price;

public:
    GeneralProduct(int id, const string& name, float price) 
        : id(id), name(name), price(price) {}

    string getName() const override {
        return name;
    }

    float getPrice() const override {
        return price;
    }
};

// Class to represent an item in the shopping cart
class CartItem {
public:
    shared_ptr<Product> product; // Use shared_ptr for polymorphism
    int quantity;

    CartItem(shared_ptr<Product> product, int quantity) 
        : product(product), quantity(quantity) {}
};

// Class to represent a shopping cart
class ShoppingCart {
public:
    vector<CartItem> items;

    void addItem(shared_ptr<Product> product, int quantity) {
        items.push_back(CartItem(product, quantity));
        cout << product->getName() << " has been added to the cart.\n";
    }

    void viewCart() const {
        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        float total = 0.0;
        cout << "\nYour Cart:\n";
        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].product->getName() 
                 << " - Quantity: " << items[i].quantity
                 << ", Price: $" << fixed << setprecision(2) 
                 << items[i].product->getPrice() * items[i].quantity << "\n";
            total += items[i].product->getPrice() * items[i].quantity;
        }
        cout << "Total: $" << fixed << setprecision(2) << total << "\n";
    }

    void modifyCart() {
        if (items.empty()) {
            cout << "Your cart is empty. Nothing to modify.\n";
            return;
        }

        viewCart();
        int itemIndex, newQuantity;
        cout << "Enter the item number to modify (1 to " << items.size() << "): ";
        if (!(cin >> itemIndex) || itemIndex < 1 || itemIndex > items.size()) {
            cout << "Invalid item number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter new quantity (0 to remove item): ";
        if (!(cin >> newQuantity) || newQuantity < 0) {
            cout << "Invalid quantity!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (newQuantity == 0) {
            items.erase(items.begin() + (itemIndex - 1));
            cout << "Item removed from the cart.\n";
        } else {
            items[itemIndex - 1].quantity = newQuantity;
            cout << "Item quantity updated.\n";
        }
    }

    void checkout() {
        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        float total = 0.0;
        for (const auto& item : items) {
            total += item.product->getPrice() * item.quantity;
        }

        cout << "Proceeding to checkout. Total amount: $" << fixed << setprecision(2) << total << "\n";
        processPayment(total);

        items.clear(); // Clear the cart after checkout
        cout << "Order confirmed! Thank you for shopping.\n";
    }

private:
    void processPayment(float totalAmount) {
        string cardNumber;
        cout << "Enter your card number for payment: ";
        cin >> cardNumber;
        cout << "Processing payment of $" << fixed << setprecision(2) << totalAmount << "...\n";
        cout << "Payment successful!\n";
    }
};

// Class to represent a User
class User {
public:
    string name;
    ShoppingCart cart;

    User(string name) : name(name) {}
};

// Function prototypes
void displayProducts(const vector<shared_ptr<Product>>& products);
void addToCart(User& user, const vector<shared_ptr<Product>>& products);
vector<shared_ptr<Product>> loadProductsFromFile(const string& fileName);

int main() {
    try {
        // Load products from file
        vector<shared_ptr<Product>> products = loadProductsFromFile("products.txt");

        User user("John Doe");

        int choice;
        cout << "Welcome " << user.name << " to the Online Shopping Cart System\n";

        do {
            cout << "\n1. Display Products\n";
            cout << "2. Add to Cart\n";
            cout << "3. View Cart\n";
            cout << "4. Modify Cart\n";
            cout << "5. Checkout\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    displayProducts(products);
                    break;
                case 2:
                    addToCart(user, products);
                    break;
                case 3:
                    user.cart.viewCart();
                    break;
                case 4:
                    user.cart.modifyCart();
                    break;
                case 5:
                    user.cart.checkout();
                    break;
                case 6:
                    cout << "Exiting the system. Thank you for shopping!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

// Function to display available products
void displayProducts(const vector<shared_ptr<Product>>& products) {
    cout << "\nAvailable Products:\n";
    for (const auto& product : products) {
        cout << "Name: " << product->getName() 
             << ", Price: $" << fixed << setprecision(2) << product->getPrice() << "\n";
    }
}

// Function to add product to cart
void addToCart(User& user, const vector<shared_ptr<Product>>& products) {
    int productId, quantity;

    displayProducts(products);

    cout << "Enter the Product ID to add to cart: ";
    if (!(cin >> productId) || productId < 1 || productId > products.size()) {
        cout << "Invalid Product ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter quantity: ";
    if (!(cin >> quantity) || quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    user.cart.addItem(products[productId - 1], quantity); // Adjust index for 0-based array
}

// Function to load products from file
vector<shared_ptr<Product>> loadProductsFromFile(const string& fileName) {
    vector<shared_ptr<Product>> products;
    ifstream file(fileName);

    if (!file) {
        throw runtime_error("Failed to open the products file.");
    }

    int id;
    string line;
    string name;
    float price;

    while (getline(file, line)) {
        stringstream ss(line);
        if (ss >> id >> price) {
            // Remaining part of the line is the product name
            getline(ss >> ws, name); 
            products.push_back(make_shared<GeneralProduct>(id, name, price));
        }
    }

    file.close();
    return products;
}
