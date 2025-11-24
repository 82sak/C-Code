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
                // addmin function
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
                            break;
                        }
                        
                        default:
                            break;
                    }
                }
                break;
            }
            case 2:{
                // staff function
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
                        case 1: {
                            showMenu();
                            break;
                        }
                        case 2: {
                            // show receipt;
                            break;

                        }
                        default :{
                            break;
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