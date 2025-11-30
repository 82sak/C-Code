#include "models/menu.hpp"
#include "models/menuManagement.hpp"
#include "models/menuInfo.hpp"
#include "models/excelUtils.hpp"
#include "models/orderInfo.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

#define RESET   "\033[0m"
#define BLUE   "\033[34m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

void displayMenuPage(){
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << GREEN << BOLD << "\t\t\t|          WELCOME TO MENU      |\n";
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << BLUE << BOLD << "\t\t\t1. Menu\n" << RESET;
    cout << BLUE << BOLD << "\t\t\t2. Cart\n" << RESET;
    cout << RED  << BOLD << "\t\t\t0. Exit\n" << RESET;
}

void displayCategory(){
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << GREEN << BOLD << "\t\t\t|            CATEGORIES         |\n";
    cout << GREEN << BOLD << "\t\t\t=================================\n";
    cout << BLUE << BOLD << "\t\t\t1. Food\n" << RESET;
    cout << BLUE << BOLD << "\t\t\t2. Drinks\n" << RESET;
    cout << RED  << BOLD << "\t\t\t0. Exit\n" << RESET;
}

vector<string> orderName;
vector<float> orderPrice;
vector<int> orderAmount;
vector<string> orderCategory;

void displayFood(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);
    string food = "food";

    system("cls");
    cout << "========== Food ==========\n\n";

    if(products.empty()){
        cout << "No product found!";
    }else{
        int count = 1;
        for(const auto &product : products){
            if(product.getItemCategory() == food){
                cout << "[" << count << "]" <<"    Product Name : " << product.getItemName() << endl;
                cout << "    Product Price : " << product.getItemPrice() << endl;
                count++;
            }
        }
    }

    string orderItem;
    int amount;
    cin.ignore();
    cout << "Enter Food Name to Order : ";
    getline(cin, orderItem);

    bool found = false;
    for(const auto &product : products){
        if(product.getItemName() == orderItem && product.getItemCategory() == food){
            found = true;
            cout << "Enter Amount : ";
            cin >> amount ;
            if(amount > product.getItemAmount()){
                cout << "Sorry, only " << product.getItemAmount() << " available\n";
                cin.ignore();
                cin.get();
            }else{
                orderName.push_back(orderItem);
                orderPrice.push_back(product.getItemPrice());
                orderAmount.push_back(amount);
                orderCategory.push_back(food);
            }
            
        }
    }
    if(!found){
        cout << " This kind of food is not exist in our restaurant";
        cin.ignore();
        cin.get();
    }

}

void displayDrink(){
    string filename = "../../data/productInfo.xlsx";
    vector<Product> products  = readExcelFromMenuInfoToVector(filename);
    string drink = "drink";

    system("cls");
    cout << "========== Food ==========\n\n";

    if(products.empty()){
        cout << "No product found!";
    }else{
        int count = 1;
        for(const auto &product : products){
            if(product.getItemCategory() == drink){
                cout << "[" << count << "]" <<"    Product Name : " << product.getItemName() << endl;
                cout << "    Product Price : " << product.getItemPrice() << endl;
                count++;
            }
        }
    }

    string orderItem;
    int amount;
    cin.ignore();
    cout << "Enter Drink Name to Order : ";
    getline(cin, orderItem);

    bool found = false;
    for(const auto &product : products){
        if(product.getItemName() == orderItem && product.getItemCategory() == drink){
            found = true;
            cout << "Enter Amount : ";
            cin >> amount ;
            if(amount > product.getItemAmount()){
                cout << "Sorry, only " << product.getItemAmount() << " available\n";
                cin.ignore();
                cin.get();
            }else {
                orderName.push_back(orderItem);
                orderPrice.push_back(product.getItemPrice());
                orderAmount.push_back(amount);
                orderCategory.push_back(drink);
            }
            
        }
    }
    if(!found){
        cout << "\nThis kind of food is not exist in our restaurant";
        cin.ignore();
        cin.get();
    }
}

inline string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    
    stringstream ss;
    ss << put_time(localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void displayCart(){
    system("cls");
    cout << "========== Cart ==========\n\n";

    float price;
    float total = 0;
    float tax;
    float totalTax = 0;
    bool cond = true;
    if(orderName.empty()){
        cout << "Your cart is empty!";
        cond = false;
    }else{
        for(int i = 0; i < orderName.size(); i++){
            cout << "Name : " << orderName[i] << endl;
            cout << "Price : " << orderPrice[i] << endl;
            cout << "Amount : " << orderAmount[i] << endl;
            cout << "============================\n";

            tax = (orderPrice[i] / 10) * orderAmount[i];
            price = orderPrice[i] * orderAmount[i];
            total += price;
            totalTax += tax;
        }
        cout << " SubTotal Price : $" << total << endl;
        cout << " Tax Price : $" << totalTax << endl;
        cout << " Total Price : $" << total + totalTax << endl;
    }

    while(cond){
        int option;
        cout << "\n1. Delete Item\n";
        cout << "2. Confirm\n";
        cout << "0. Exit\n";
        cout << "Choose an Option : ";
        cin >> option;
        if(option == 0){
            break;
        }
        switch(option){
            case 1:{
                string deleteItem;

                cin.ignore();
                cout << "Enter Item Name to Removed : ";
                getline(cin, deleteItem);
                bool found = false;
                for(int i = 0; i < orderName.size(); i++){
                    if(orderName[i] == deleteItem){
                        found = true;
                        orderName.erase(orderName.begin() + i);
                        orderPrice.erase(orderPrice.begin() + i);
                        orderAmount.erase(orderAmount.begin() + i);
                        orderCategory.erase(orderCategory.begin() + i);
                        cout << "\nItem removed from cart successfully!" ;
                        break;
                    }
                }
                if(!found){
                    cout << "Item not found";
                }
                cond = false;
            break;
            }
            case 2:{
                string filename = "../../data/orderInfo.xlsx";
                vector<Order> orders  = readExcelFromOrderInfoToVector(filename);

                string productInfo = "../../data/productInfo.xlsx";
                vector<Product> products  = readExcelFromMenuInfoToVector(productInfo);
                string timestamp = getCurrentTimestamp();

                for(int i = 0 ; i < orderName.size(); i++){
                    for( auto &product : products){
                        if(product.getItemName() == orderName[i]){
                            int newAmount = product.getItemAmount() - orderAmount[i];
                            product.setItemAmount(newAmount);
                            break;
                        }
                    }
                    orders.emplace_back(orderName[i], orderPrice[i], orderAmount[i], orderCategory[i], timestamp);
                }

                writeExcelToOrderInfo(filename, orders);
                writeExcelToMenuInfo(productInfo, products);
                orderName.clear();
                orderPrice.clear();
                orderAmount.clear();
                orderCategory.clear();
                cout << "\n Order placed successfully!\n";
                cout << "✓ Order time: " << timestamp << "\n";
                cout << "Thank you for your order!\n";
                cond = false;
                break;
            }
            default : {
                break;
            }
        }
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}