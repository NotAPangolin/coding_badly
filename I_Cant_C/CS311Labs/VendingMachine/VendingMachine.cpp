// ============================================================================
// vending_machine_starter.cpp
// A simple vending machine simulation -- your job is to fill in the TODO
// functions below. main() is already written and tells you exactly how
// each function will be called and what it needs to do.
//
// Build:  g++ -std=c++17 -Wall -o vending vending_machine_starter.cpp
// Run:    ./vending
// Needs:  products.txt in the same folder.
//
// This file compiles as-is (the stubs return harmless placeholder values),
// but the program won't behave correctly until you implement each TODO.
// ============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// ----------------------------------------------------------------------------
// Constants -- don't change these.
// ----------------------------------------------------------------------------
const int MAX_PRODUCTS = 50;
const string INVENTORY_FILE = "products.txt";
const string LOG_FILE = "transactions.log";

// ----------------------------------------------------------------------------
// ENUM: possible outcomes of trying to buy something.
// ----------------------------------------------------------------------------
enum TransactionStatus { SUCCESS, INSUFFICIENT_FUNDS, OUT_OF_STOCK, INVALID_SELECTION };

// ENUM: the coin values we know how to make change with, in cents.
enum CoinValue { QUARTER = 25, DIME = 10, NICKEL = 5, PENNY = 1 };

// Parallel arrays that describe the coins we hand back as change.
const CoinValue DENOMINATIONS[4] = { QUARTER, DIME, NICKEL, PENNY };
const string DENOM_NAMES[4] = { "Quarters", "Dimes", "Nickels", "Pennies" };

// ----------------------------------------------------------------------------
// STRUCT: plain data container -- no member functions belong here.
// ----------------------------------------------------------------------------
struct Product {
    int code;
    string name;
    double price;
    int quantity;
};

// ----------------------------------------------------------------------------
// Function prototypes -- do not change these signatures. main() and the
// grading tests depend on them matching exactly.
// ----------------------------------------------------------------------------
int loadInventory(const string& filename, Product inventory[], int maxSize);
void saveInventory(const string& filename, const Product inventory[], int count);
void printMenu(const Product inventory[], int count);
void printInventoryPtr(const Product* inventory, int count);
Product* findProductByCode(Product inventory[], int count, int code);
TransactionStatus dispensePurchase(Product* product, double payment);
int makeChange(double changeOwedDollars, int coinCounts[4]);
void printChange(const int coinCounts[4]);
void logTransaction(const string& filename, const Product& product, double payment, TransactionStatus status);
double getValidPayment();

// ============================================================================
// main -- already complete. Read through it before writing any functions;
// it tells you what every function is supposed to do.
// ============================================================================
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = loadInventory(INVENTORY_FILE, inventory, MAX_PRODUCTS);

    if (productCount == 0) {
        cout << "Could not load " << INVENTORY_FILE << ". Exiting.\n";
        return 1;
    }

    cout << "=== Welcome to the CS Vending Machine ===\n";

    bool running = true;
    while (running) {
        printMenu(inventory, productCount);
        cout << "\nEnter a product code to buy, 'I' to inspect inventory (pointers), "
            << "or 0 to quit: ";

        string input;
        cin >> input;

        if (input == "0") {
            running = false;
            continue;
        }
        if (input == "I" || input == "i") {
            printInventoryPtr(inventory, productCount);
            continue;
        }

        int code = 0;
        try {
            code = stoi(input);
        }
        catch (...) {
            cout << "That's not a valid entry.\n";
            continue;
        }

        Product* selected = findProductByCode(inventory, productCount, code);
        if (selected == nullptr) {
            cout << "Invalid selection.\n";
            logTransaction(LOG_FILE, Product{ code, "UNKNOWN", 0.0, 0 }, 0.0, INVALID_SELECTION);
            continue;
        }

        cout << "You selected " << selected->name << " ($"
            << fixed << setprecision(2) << selected->price << ").\n";
        double payment = getValidPayment();

        TransactionStatus status = dispensePurchase(selected, payment);
        logTransaction(LOG_FILE, *selected, payment, status);

        switch (status) {
        case SUCCESS: {
            double changeOwed = payment - selected->price;
            cout << "Dispensing " << selected->name << ". Your change: $"
                << fixed << setprecision(2) << changeOwed << "\n";
            int coinCounts[4] = { 0, 0, 0, 0 };
            makeChange(changeOwed, coinCounts);
            printChange(coinCounts);
            break;
        }
        case INSUFFICIENT_FUNDS:
            cout << "Insufficient funds. Payment returned.\n";
            break;
        case OUT_OF_STOCK:
            cout << "Sorry, " << selected->name << " is sold out.\n";
            break;
        default:
            cout << "Something went wrong with that transaction.\n";
        }
        cout << "----------------------------------------\n";
    }

    saveInventory(INVENTORY_FILE, inventory, productCount);
    cout << "Inventory saved. Goodbye!\n";
    return 0;
}

// ============================================================================
// TODO 1 -- FILE I/O + ARRAYS
// Open `filename` for reading. Each line has: code name price quantity
// Read values straight into inventory[count] using >>, incrementing count
// each time, until either the file runs out or count reaches maxSize.
// Return the number of products successfully read (0 if the file wouldn't
// open).
// ============================================================================
int loadInventory(const string& filename, Product inventory[], int maxSize) {
    // TODO: open an ifstream on filename, check it opened, loop reading
    // into inventory[count], close the file, return count.
    return 0;
}

// ============================================================================
// TODO 2 -- FILE I/O + ARRAYS
// Open `filename` for writing (this OVERWRITES the file). Write one line
// per product in the same "code name price quantity" format loadInventory
// expects, so the two functions round-trip correctly.
// ============================================================================
void saveInventory(const string& filename, const Product inventory[], int count) {
    // TODO: open an ofstream on filename, loop over inventory[0..count),
    // write each product on its own line, close the file.
}

// ============================================================================
// TODO 3 -- FILE I/O
// Open `filename` in APPEND mode (look up ios::app) and write one line
// describing this transaction attempt: the product's code and name, the
// payment amount, and the status (convert the enum to a string first,
// e.g. with a switch). Close the file when done.
// ============================================================================
void logTransaction(const string& filename, const Product& product, double payment, TransactionStatus status) {
    // TODO: open in append mode, build a status string from the enum,
    // write one line, close the file.
}

// ============================================================================
// TODO 4 -- ARRAYS
// Print a formatted table of every product: code, name, price, quantity.
// Use inventory[i] to access each element; count tells you how far to loop.
// ============================================================================
void printMenu(const Product inventory[], int count) {
    // TODO: loop i from 0 to count-1, print inventory[i]'s fields, nicely
    // formatted (setw/setprecision are your friends here).
    for (int i = 0; i < count; i++) {
        //code, name, price, qty

        cout << setw(8) << inventory[i].name << setw(6) << "$" << inventory[i].price << "available: " << setw(4) << inventory[i].quantity;
    }
}

// ============================================================================
// TODO 5 -- POINTERS + ARRAYS
// Do the SAME thing printMenu conceptually does (list each product's name
// and quantity), but walk the array using a pointer and pointer arithmetic
// (ptr++) instead of the [] operator. Start with a pointer set to
// `inventory` and dereference it with -> to get each product's fields.
// ============================================================================
void printInventoryPtr(const Product* inventory, int count) {
    // TODO: const Product* ptr = inventory; loop count times, print
    // ptr->name and ptr->quantity, then ptr++.
    for (int i = 0; i < count; i++) {
        //code, name, price, qty

        cout << setw(8) << inventory[i].name << setw(6) << "$" << inventory[i].price << "available: " << setw(4) << inventory[i].quantity;
    }
}

// ============================================================================
// TODO 6 -- POINTERS + ARRAYS
// Search inventory[0..count) for a product whose code matches `code`.
// If found, return a pointer to that array element (&inventory[i]) so the
// caller can modify it directly. If not found, return nullptr.
// ============================================================================
Product* findProductByCode(Product inventory[], int count, int code) {
    // TODO: loop, compare inventory[i].code to code, return &inventory[i]
    // on a match; return nullptr if the loop finishes with no match.
    return nullptr;
}

// ============================================================================
// TODO 7 -- POINTERS
// `product` points at one element inside the caller's inventory array.
// If product->quantity is 0, return OUT_OF_STOCK.
// If payment is less than product->price, return INSUFFICIENT_FUNDS.
// Otherwise decrement product->quantity through the pointer (this must
// change the real array element, not a copy) and return SUCCESS.
// ============================================================================
TransactionStatus dispensePurchase(Product* product, double payment) {
    // TODO: check quantity, check payment, update product->quantity,
    // return the right TransactionStatus.
    return INVALID_SELECTION;
}

// ============================================================================
// TODO 8 -- ARRAYS + ENUM
// changeOwedDollars is something like 0.75. Convert it to whole cents
// (watch out for floating point rounding -- round() from <cmath> helps),
// then for each of the 4 denominations in DENOMINATIONS (already in
// biggest-to-smallest order), figure out how many of that coin fit into
// the remaining cents, store that count in coinCounts[i], and subtract
// what you used from the remaining cents. Return the total number of
// coins used.
// ============================================================================
int makeChange(double changeOwedDollars, int coinCounts[4]) {
    // TODO: convert to cents, loop i = 0..3 using DENOMINATIONS[i] as the
    // coin value, fill coinCounts[i], track total coins, return total.
    return 0;
}

// ============================================================================
// TODO 9 -- ARRAYS
// Print each denomination in coinCounts that is greater than 0, using
// DENOM_NAMES[i] for the label (e.g. "  Quarters: 2").
// ============================================================================
void printChange(const int coinCounts[4]) {
    // TODO: loop i = 0..3, if coinCounts[i] > 0 print DENOM_NAMES[i] and
    // the count.
}

// ============================================================================
// Given as an example -- a plain function with no array/pointer/file/struct
// involved, so you can see the style being used elsewhere in this file.
// ============================================================================
double getValidPayment() {
    double amount;
    do {
        cout << "Insert payment: $";
        cin >> amount;
        if (amount <= 0) {
            cout << "Please enter a positive amount.\n";
        }
    } while (amount <= 0);
    return amount;
}
