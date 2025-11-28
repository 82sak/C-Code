#include <iostream>
#include <vector>
#include "ui/homepage.hpp"
#include "models/admin.hpp"
#include "models/menu.hpp"
#include "models/staff.hpp"
#include "models/excelUtils.hpp"
#include "models/staffAccount.hpp"
#include "models/staffManagement.hpp"
#include "models/menuInfo.hpp"
#include "models/menuManagement.hpp"
 
using namespace std;

int main(){
    system("cls");

    loadingScreen();
    
    while(true){
        system("cls");
        int option;
        homePage();
        
        cout << "Choose an Option : ";
        cin >> option;
        
        if(option == 0){
            break;
        }
        switch(option){
            case 1:{
                // adminAuth
                // addmin function
                if(adminAuth()){
                    while(true){
                        system("cls");

                        int option;
                        displayAdminPage();

                        cout << "Choose an option : ";
                        cin >> option;

                        if(option == 0){
                            break;
                        }

                        switch (option){
                            case 1:{
                                // Menu Management
                                while(true){
                                    system("cls");

                                    int option;
                                    displayMenuManagementPage();
                                    cout << "Choose an option : ";
                                    cin >> option;

                                    if(option == 0){
                                        break;
                                    }
                                    switch(option){
                                        case 1:{
                                            // Add new product
                                            addNewProduct();
                                            break;
                                        }
                                        case 2:{
                                            // update product
                                            updateProduct();
                                            break;
                                        }
                                        case 3:{
                                            // delete product
                                            deleteProduct();
                                            break;
                                        }
                                        case 4:{
                                            // show all product
                                            showAllProduct();
                                            break;
                                        }
                                        default:{
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            case 2: {
                                // Staff Management
                                while(true){
                                    system("cls");
                                    int option;
                                    displayStaffManagementPage();
                                    cout << "Choose an option : ";
                                    cin >> option;
                                    if(option == 0){
                                        break;
                                    }
                                    switch (option){
                                        case 1: {
                                            // addNewStaffAccount();
                                            addNewStaffAccount();
                                            break;
                                        }
                                        case 2:{
                                            // update staff
                                            updateStaffAccount();
                                            break;
                                        }
                                        case 3:{
                                            // delete staff
                                            deleteStaffAccount();
                                            break;
                                        }
                                        case 4:{
                                            // show all staff
                                            showAllStaff();
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                                break;
                            }
                            case 3:{
                                //  Sales summary
                                while(true){
                                    system("cls");
                                    int option;
                                    displaySalesSummary();
                                    cout << "Choose an option : ";
                                    cin >> option;
                                    if(option == 0){
                                        break;
                                    }
                                    switch (option)
                                    {
                                    case 1:{
                                        // 1d
                                        showSummaryOneDay();
                                        break;
                                    }
                                    case 2:{
                                        // 1week
                                        showSummaryOneWeek();
                                        break;
                                    }
                                    case 3:{
                                        // 1month
                                        break;
                                    }
                                    default:
                                        break;
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                break;
            }
            case 2:{
                // Auth
                // staff function
                if(staffAuth()){
                    while(true){
                        system("cls");
                        int option;
                        
                        displayStaffPage();
                        cout << "Choose an option : ";
                        cin >> option;
                        if(option == 0){
                            break;
                        }
                        switch(option){
                            case 1:{
                                // show menu
                                showMenu();
                                break;
                            }
                            case 2:{
                                // show receipt
                                showReceipt();
                                break;
                            }
                            default:{
                                cout << "Invalid option";
                            }
                        }
                    }
                }
                break;
            }
            case 3:{
                // menu function
                while(true){
                    system("cls");
                    int option;
                    
                    displayMenuPage();
                    cout << "Choose an option : ";
                    cin >> option;
                    if(option == 0){
                        break;
                    }
                    switch (option){
                        case 1:{
                            // display category
                            while(true){
                                system("cls");
                                int option;

                                displayCategory();
                                cout << "Choose an Option : ";
                                cin >> option;
                                if(option == 0){
                                    break;
                                }
                                switch (option){
                                    case 1:{
                                        // Food
                                        displayFood();
                                        break;
                                    }
                                    case 2:{
                                        // drink
                                        displayDrink();
                                        break;
                                    }
                                    
                                    default:
                                        break;
                                    }
                            }
                            break;
                        }
                        case 2:{
                            // cart
                            displayCart();
                            break;
                        }
                        default:
                            break;
                    }
                }
                

                break;
            }
            default :{
                cout << "Invalide option";
            }
        }
    }
    

    return 0;
}