#include <iostream>
#include <vector>
#include "models/staff.hpp"
#include "models/admin.hpp"
#include "models/menuManagement.hpp"
#include "models/menuInfo.hpp"
#include "models/excelUtils.hpp"


using namespace std;

#define RESET   "\033[0m"
#define BLUE   "\033[34m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

void displayStaffPage(){
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << GREEN << BOLD << "\t\t\t|      WELCOME TO STAFF PANEL   |\n";
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << BLUE << BOLD << "\t\t\t1. Show Menu\n" << RESET;
    cout << BLUE << BOLD << "\t\t\t2. Show Receipt\n" << RESET;
    cout << RED  << BOLD << "\t\t\t0. Exit\n" << RESET;
}

void showMenu(){
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

void showReceipt() {
    string filename = "../../data/orderInfo.xlsx";
    vector<Order> orders = readExcelFromOrderInfoToVector(filename);
    
    system("cls");
    cout << "========== ORDERS BY TRANSACTION ==========\n\n";
    
    if(orders.empty()) {
        cout << "No orders found!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    
    string currentTimestamp = "";
    float transactionTotal = 0;
    int transactionNum = 0;
    
    for(const auto &order : orders) {

        if(order.getItemOrderTimestamp() != currentTimestamp) {
            if(!currentTimestamp.empty()) {
                cout << "    -----------------------------------\n";
                cout << "    Transaction Total: $" << transactionTotal << "\n";
                cout << "========================================\n\n";
            }
            
            transactionNum++;
            currentTimestamp = order.getItemOrderTimestamp();
            transactionTotal = 0;
            
            cout << "Transaction " << transactionNum << "\n";
            cout << "Time: " << currentTimestamp << "\n";
            cout << "----------------------------------------\n";
        }
        
        float subtotal = order.getItemOrderPrice() * order.getItemOrderAmount();
        transactionTotal += subtotal;
        
        cout << "    " << order.getItemOrderName() 
             << " (" << order.getItemOrderCategory() << ")\n";
        cout << "    $" << order.getItemOrderPrice() 
             << " x " << order.getItemOrderAmount() 
             << " = $" << subtotal << "\n";
    }
    
    if(!currentTimestamp.empty()) {
        cout << "    -----------------------------------\n";
        cout << "    Transaction Total: $" << transactionTotal << "\n";
        cout << "========================================\n";
    }
    
    cout << "\nTotal Transactions: " << transactionNum << "\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}