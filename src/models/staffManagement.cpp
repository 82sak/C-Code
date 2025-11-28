#include "models/staffManagement.hpp"
#include "models/excelUtils.hpp"
#include "models/staffAccount.hpp"
#include <iostream>
#include <vector>
#include <conio.h>
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

void showAllStaff(){
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);

    system("cls");
    cout << "========== ALL STAFF ACCOUNTS ==========\n\n";

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

inline string maskingPassword(){
    string password = "";
    char ch;
    
    while (true) {
        ch = _getch(); 
        
        if (ch == 13) { 
            cout << endl;
            break;
        }
        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back(); 
                cout << "\b \b"; 
            }
        }
        else {
            password += ch;  
            cout << '*'; 
        }
    }
    
    return password;
}

bool staffAuth() {
    string filename = "../../data/staffInfo.xlsx";
    vector<User> users = readExcelFromStaffInfoToVector(filename);
    
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
        for(const auto &user : users) {
            if(user.getUserName() == userName && user.getUserPass() == userPass) {
                found = true;
                cout << "\n Login successful!\n";
                cout << "Welcome, " << user.getUserFullName() << "!\n";
                cout << "Press Enter to continue...";
                cin.get();
                return true;
            }
        }
        
        if(!found) {
            attempts--;
            if(attempts > 0) {
                cout << "\n Invalid username or password!\n";
                cout << "Attempts remaining: " << attempts << "\n";
                cout << "Press Enter to try again...";
                cin.get();
            } else {
                cout << "\n✗ Login failed! No attempts remaining.\n";
                cout << "Press Enter to return...";
                cin.get();
            }
        }
    }
    
    return false;
}