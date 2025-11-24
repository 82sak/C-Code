#include "models/staff.hpp"
#include <iostream>
#include "models/admin.hpp"
#include "models/menuInfo.hpp"
#include <vector>
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
    cout << BLUE << BOLD << "[[========== ALL Product ==========]]\n\n" RESET;

    if(products.empty()){
        cout << "No product found!";
    }else{
        int count = 1;
        for(const auto &product : products){
            cout << "[" << count << "]" <<" Product Name : "   << product.getItemName();
            
            cout << "    Product Price : " << GREEN << " $ " << RESET<< product.getItemPrice() <<endl;
            // cout << "    Product Amount : " << product.getItemAmount() << endl;
            
            count++;
        }
        cout << "Total Product : " << products.size() << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
};