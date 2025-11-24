#include "models/staffManagement.hpp"
#include "models/excelUtils.hpp"
#include "models/staffAccount.hpp"
#include <iostream>
#include <vector>
#define RESET   "\033[0m"
#define BLUE   "\033[34m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"
// #include <tabulate/table.hpp>

using namespace std;
// using namespace tabulate;

void addNewStaffAccount(){
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);

    string userName;
    string userPass;
    string fullName;
    string gender;
    int age;

    cin.ignore();
    cout << "Enter Staff's account Name : ";
    getline(cin, userName);
    cout << "Enter Staff's account Password : ";
    getline(cin, userPass);
    cout << "Enter Staff Full Name : ";
    getline(cin, fullName);
    cout << "Enter Staff Gender : ";
    getline(cin, gender);
    cout << "Enter Staff Age : ";
    cin >> age;

    users.emplace_back(userName, userPass, fullName, gender, age);
    writeExcelToStaffInfo(filename, users);
}

void updateStaffAccount(){
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);

    string updateName;
    string newUserFullName;
    string newUserGender;
    int newUserAge;

    cin.ignore();
    cout << "Enter Staff's account Name to Update : ";
    getline(cin, updateName);

    bool found = false;
    for(auto &user : users){
        if(user.getUserName() == updateName){
            found = true;
            cout << "User found!\n";
            cout << "Name: " << user.getUserFullName() << "\n";
            cout << "Gender: " << user.getUserGender() << "\n";
            cout << "Age: " << user.getUserAge() << "\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();

            cout << "Enter Staff Full Name : ";
            getline(cin, newUserFullName);
            cout << "Enter Staff Gender : ";
            getline(cin, newUserGender);
            cout << "Enter Staff Age : ";
            cin >> newUserAge;

            user.setUserFullName(newUserFullName);
            user.setUserGender(newUserGender);
            user.setUserAge(newUserAge);

            writeExcelToStaffInfo(filename, users);
            break;  
        }
    }
    if(!found){
            cout << "User not found!\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
        }
    
}

void deleteStaffAccount(){
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);

    string deleteStaff;

    cout << "Enter Staff's Name to Delete : ";
    cin >> deleteStaff;

    bool found = false;
    for(auto it = users.begin(); it != users.end(); it++){
        if(it->getUserName() == deleteStaff ){
            found = true;
            users.erase(it);
            cout << "Staff's account deleted successfully!\n";
            cin.ignore();
            break;
        }
    }
    if(!found){
        cout << "Staff's account not found!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
    }
    writeExcelToStaffInfo(filename, users);
}

// void showAllStaff(const vector<User> &users){
//     Table table;
//     table.add_row({"Staff's Account Name","fullName", "Gender", "Age"});
//     for(const auto &user : users){
//         table.add_row({user.getUserName(), user.getUserFullName(), user.getUserGender(), to_string(user.getUserAge())});
//     }
//     table[0].format().font_style({FontStyle::bold});
//     cout << table << endl;
// };

void showAllStaff(){
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);

    system("cls");
    cout << BLUE << BOLD << "========== ALL STAFF ACCOUNTS ==========\n\n" <<RESET;

    if(users.empty()){
        cout << "No staff accounts found!\n";
    } else {
        int count = 1;
        for(const auto &user : users){
            cout << "[" << count << "] " << user.getUserFullName() << "\n";
            cout << "    Username: " << user.getUserName() << "\n";
            cout << "    Gender: " << user.getUserGender() << "\n";
            cout << "    Age: " << user.getUserAge() << "\n";
            cout << "\n";
            count++;
        }
        cout << "Total Staff: " << users.size() << "\n";
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}