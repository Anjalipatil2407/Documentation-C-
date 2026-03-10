#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

int transactionCount = 0;

// Function to show currencies
void showCurrencies() {
    cout << "\nAvailable Currencies:\n";
    cout << "1. INR\n";
    cout << "2. USD\n";
    cout << "3. EUR\n";
    cout << "4. GBP\n";
    cout << "5. JPY\n";
    cout << "6. AUD\n";
}

// Function to get currency name
string getCurrencyName(int choice) {
    if(choice == 1) return "INR";
    if(choice == 2) return "USD";
    if(choice == 3) return "EUR";
    if(choice == 4) return "GBP";
    if(choice == 5) return "JPY";
    if(choice == 6) return "AUD";
    return "Unknown";
}

// Exchange rates (basic fixed rates)
float getRate(int from, int to) {

    if (from == to) return 1;

    // Base INR rates
    if (from == 1 && to == 2) return 0.012;
    if (from == 1 && to == 3) return 0.011;
    if (from == 1 && to == 4) return 0.0095;
    if (from == 1 && to == 5) return 1.65;
    if (from == 1 && to == 6) return 0.018;

    if (from == 2 && to == 1) return 83;
    if (from == 3 && to == 1) return 90;
    if (from == 4 && to == 1) return 105;
    if (from == 5 && to == 1) return 0.60;
    if (from == 6 && to == 1) return 55;

    return 1; // simplified for demo
}

// Function to get current date and time
string getDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

// Convert currency
void convertCurrency() {
    int from, to;
    float amount;

    showCurrencies();
    cout << "\nEnter From Currency (1-6): ";
    cin >> from;

    cout << "Enter To Currency (1-6): ";
    cin >> to;

    cout << "Enter Amount: ";
    cin >> amount;

    float rate = getRate(from, to);
    float result = amount * rate;

    cout << fixed << setprecision(2);
    cout << "\nConverted Amount: " << result 
         << " " << getCurrencyName(to) << endl;

    ofstream file("transactions.txt", ios::app);

    file << "\n----------------------------------\n";
    file << "Date & Time: " << getDateTime();
    file << "From: " << getCurrencyName(from) << endl;
    file << "To: " << getCurrencyName(to) << endl;
    file << "Amount: " << amount << endl;
    file << "Converted Amount: " << result << endl;

    file.close();

    transactionCount++;

    cout << "\nTransaction Saved Successfully!\n";
}

// View transaction history
void viewTransactions() {
    ifstream file("transactions.txt");
    string line;

    cout << "\n------ Transaction History ------\n";

    while(getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Show total transactions
void showTotalTransactions() {
    cout << "\nTotal Transactions in this session: "
         << transactionCount << endl;
}

int main() {
    int choice;

    do {
        cout << "\n====== FOREX MANAGEMENT SYSTEM ======\n";
        cout << "1. Convert Currency\n";
        cout << "2. View Transactions\n";
        cout << "3. Show Total Transactions\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                convertCurrency();
                break;
            case 2:
                viewTransactions();
                break;
            case 3:
                showTotalTransactions();
                break;
            case 4:
                cout << "\nThank you for using Forex System!\n";
                break;
            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while(choice != 4);

    return 0;
}