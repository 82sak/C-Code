#include "models/menuManagement.hpp"
#include "models/menuInfo.hpp"
#include "models/excelUtils.hpp"
#include "models/menu.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <conio.h>

using namespace std;

void addNewProduct(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);

    string itemName;
    float  itemPrice;
    int   itemAmount;
    string itemCategory;

    cin.ignore();
    cout << "Enter Product Name : ";
    getline(cin, itemName);
    cout << "Enter Product Price : ";
    cin >> itemPrice;
    cout << "Enter Product Amount : ";
    cin >> itemAmount;
    cout << "Enter Product Category : ";
    cin >> itemCategory;

    products.emplace_back(itemName, itemPrice, itemAmount, itemCategory);
    writeExcelToMenuInfo(filename, products);
}

void updateProduct(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);

    string updateName;
    string newitemName;
    float  newItemPrice;
    int   newItemAmount;
    string newItemCategory;

    cin.ignore();
    cout << "Enter Product Name to Update : ";
    getline(cin, updateName);

    bool found = false;
    for(auto &product : products){
        if(product.getItemName() == updateName){
            found = true;
            cout << "Product found!\n";
            cout << "Product Name : " << product.getItemName() << endl;
            cout << "Product Price : " << product.getItemPrice() << endl;
            cout << "Product Amount : " << product.getItemAmount() << endl;
            cout << "Product Category : " << product.getItemCategory() << endl;
            cout << "Press Enter to continue...";
            cin.ignore();

            cout << "Enter Product Name : ";
            getline(cin, newitemName);
            cout << "Enter Product Price : ";
            cin >> newItemPrice;
            cout << "Enter Product Amount : ";
            cin >> newItemAmount;
            cout << "Enter Product Category : ";
            cin >> newItemCategory;

            product.setItemName(newitemName);
            product.setItemPrice(newItemPrice);
            product.setItemAmount(newItemAmount);
            product.setItemCategory(newItemCategory);

            writeExcelToMenuInfo(filename, products);
            break;
        }
    }
    if(!found){
        cout << "Product not found!\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
}
void deleteProduct(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);

    string deleteProductInfo;

    cin.ignore();
    cout << "Enter Product Name to Delete : ";
    getline(cin, deleteProductInfo);

    bool found = false;
    for(auto it = products.begin(); it != products.end(); it++){
        if(it->getItemName() == deleteProductInfo){
            found = true;
            products.erase(it);
            cout << "Product deleted successfully!\n";
            cin.ignore();
            break;
        }
    }
    if(!found){
        cout << "Product not found!\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    writeExcelToMenuInfo(filename, products);
}
void showAllProduct(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);

    system("cls");
    cout << "========== ALL Product ==========\n\n";

    if(products.empty()){
        cout << "No product found!";
    }else{
        int count = 1;
        for(const auto &product : products){
            cout << "[" << count << "]" <<"    Product Name : " << product.getItemName() << endl;
            cout << "    Product Price : " << product.getItemPrice() << endl;
            cout << "    Product Amount : " << product.getItemAmount() << endl;
            cout << "    Product Category : " << product.getItemCategory() << endl;
            count++;
        }
        cout << "Total Product : " << products.size() << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string maskingPassword(){
    string password = "";
    char ch;
    
    while (true) {
        ch = _getch();  // Read character without displaying it
        
        if (ch == 13) {  // Enter key (ASCII 13)
            cout << endl;
            break;
        }
        else if (ch == 8) {  // Backspace key (ASCII 8)
            if (!password.empty()) {
                password.pop_back();  // Remove last character
                cout << "\b \b";  // Move back, print space, move back again
            }
        }
        else {
            password += ch;  // Add character to password
            cout << '*';     // Display asterisk
        }
    }
    
    return password;
}
bool adminAuth(){
    int attempts = 3;
    
    while(attempts > 0) {
        system("cls");
        cout << "========== STAFF LOGIN ==========\n";
        cout << "Attempts remaining: " << attempts << "\n\n";
        
        string userName;
        string userPass;
        
        cin.ignore();
        cout << "Enter Username: ";
        getline(cin, userName);
        cout << "Enter Password: ";
        // getline(cin, userPass);
        userPass = maskingPassword();
        
        bool found = false;
        if(userName == "admin" && userPass == "password"){
            found = true;
            cout << "\n Login successful!\n";
                cout << "Press Enter to continue...";
                cin.get();
                return true;
        }
        if(!found) {
            attempts--;
            if(attempts > 0) {
                cout << "\n Invalid username or password!\n";
                cout << "Attempts remaining: " << attempts << "\n";
                cout << "Press Enter to try again...";
                cin.ignore();
            } else {
                cout << "\n Login failed! No attempts remaining.\n";
                cout << "Press Enter to return...";
                cin.get();
            }
        }
    }
    return false;
}
string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    
    stringstream ss;
    ss << put_time(localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void showSummaryOneDay(){
    string filename = "../../data/orderInfo.xlsx";
    vector<Order> orders  = readExcelFromOrderInfoToVector(filename);
    
    system("cls");
    cout << "========== RECENT ORDERS ==========\n\n";
    
    if(orders.empty()) {
        cout << "No orders!\n";
        cin.get();
        return;
    }
    
    string today = getCurrentTimestamp().substr(0, 10);
    
    auto yesterday_time = chrono::system_clock::now() - chrono::hours(24);
    time_t yesterday_time_t = chrono::system_clock::to_time_t(yesterday_time);
    stringstream ss;
    ss << put_time(localtime(&yesterday_time_t), "%Y-%m-%d");
    string yesterday = ss.str();
    
    cout << "From " << yesterday << " to " << today << "\n\n";
    
    int count = 0;
    float totalTax = 0;
    float total = 0;
    
    for(const auto &order : orders) {
        string orderDate = order.getItemOrderTimestamp().substr(0, 10);
        
        if(orderDate == yesterday || orderDate == today) {
            count++;
            float price = order.getItemOrderPrice() * order.getItemOrderAmount();
            float tax = (order.getItemOrderPrice() / 10) * order.getItemOrderAmount();
            total += price;
            totalTax += tax;
            
            cout << count << ". " << order.getItemOrderName() 
                 << " - $" << price 
                 << " (" << order.getItemOrderTimestamp() << ")\n";
        }
    }
    
    cout << "\nSubTotal: $" << total << "\n";
    cout << "Tax: $" << totalTax << "\n";
    cout << "\nTotal: $" << total + totalTax << "\n";
    cout << "\nPress Enter...";
    cin.ignore();
    cin.get();
}
void showSummaryOneWeek(){
    string filename = "../../data/orderInfo.xlsx";
    vector<Order> orders  = readExcelFromOrderInfoToVector(filename);
    
    system("cls");
    cout << "========== RECENT ORDERS ==========\n\n";
    
    if(orders.empty()) {
        cout << "No orders!\n";
        cin.get();
        return;
    }
    
    string today = getCurrentTimestamp().substr(0, 10);
    
    auto week_time = chrono::system_clock::now() - chrono::hours(168);
    time_t week_time_t = chrono::system_clock::to_time_t(week_time);
    stringstream ss;
    ss << put_time(localtime(&week_time_t), "%Y-%m-%d");
    string weekAgo = ss.str();
    
    cout << "From " << weekAgo << " to " << today << "\n\n";
    
    int count = 0;
    float totalTax = 0;
    float total = 0;
    
    for(const auto &order : orders) {
        string orderDate = order.getItemOrderTimestamp().substr(0, 10);
        
        if(orderDate >= weekAgo || orderDate <= today) {
            count++;
            float price = order.getItemOrderPrice() * order.getItemOrderAmount();
            float tax = (order.getItemOrderPrice() / 10) * order.getItemOrderAmount();
            total += price;
            totalTax += tax;
            
            cout << count << ". " << order.getItemOrderName() 
                 << " - $" << price 
                 << " (" << order.getItemOrderTimestamp() << ")\n";
        }
    }
    
    cout << "\nSubTotal: $" << total << "\n";
    cout << "Tax: $" << totalTax << "\n";
    cout << "\nTotal: $" << total + totalTax << "\n";
    cout << "\nPress Enter...";
    cin.ignore();
    cin.get();
};