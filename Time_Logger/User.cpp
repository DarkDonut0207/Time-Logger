/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.cpp
 * Author: Drake
 * 
 * Created on May 5, 2021, 3:58 PM
 */

#include "User.h"

User::User() {
    ifstream userF;
    ifstream instrF;
    ifstream adminF;
    unsigned int id;
    string name;
    string adminUser;
    unsigned int encPswrd;
    userF.open("StudentIdMap.dat");
    instrF.open("InstructorIdMap.dat");
    adminF.open("adminData.dat");
    while(!userF.eof()) {
        userF >> id;
        userF.ignore(2);
        getline (userF,name);
        if (!name.empty() && name[name.size() - 1] == '\r') {
            name.erase(name.size() - 1);
        }
        uMap.insert(pair<unsigned int,string>(id, (name)));
    }
    while(!instrF.eof()) {
        instrF >> id;
        instrF.ignore(2);
        getline (instrF,name);
        if (!name.empty() && name[name.size() - 1] == '\r') {
            name.erase(name.size() - 1);
        }
        iMap.insert(pair<unsigned int,string>(id, (name)));
    }
    while(!adminF.eof()) {
        adminF >> adminUser;
        adminF >> encPswrd;
        aMap.insert(pair<string,unsigned int>(adminUser, (encPswrd)));
    }
    userF.close();
    instrF.close();
    adminF.close();
}

User::User(const User& orig) {
}

User::~User() {
}
unsigned int User::PswrdCnvrt(const string& str) {
    // Initialize variables
    unsigned int hash = static_cast<unsigned int>(str.length());
    for (int i=0; i<str.length(); i++) { // Loop through string
        // Compute hash
        hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
    }
    return hash; // Return value
}
void User::dispStudents() {
    cout << "Student List:\n";
    for(uMapItr = uMap.begin(); uMapItr != uMap.end(); ++uMapItr) {
        cout << left << setw(10) << uMapItr->first << " - " << uMapItr->second;
        cout << endl;
    }
}
void User::dispInstructors() {
    cout << "Instructor List:\n";
    for(iMapItr = iMap.begin(); iMapItr != iMap.end(); ++iMapItr) {
        cout << left << setw(10) << uMapItr->first << " - " << uMapItr->second;
        cout << endl;
    }
}
bool User::adminLogin() {
    string userName;
    string pswrd;
    unsigned int encPswrd;
    bool success = false;
    int choice = 2;
    do {
        choice = 2;
        cout << "Input Username: ";
        cin >> userName;
        cout << "Input password: ";
        cin >> pswrd;
        while (pswrd.length()>40) {
            cout << "Password is too long, re-input: ";
            cin >> pswrd;
        }
        encPswrd = this->PswrdCnvrt(pswrd);
        pswrd = "\0";
        aMapItr = aMap.find(userName);
        if (aMapItr==aMap.end()) {
            cout << "Email and password do not match.\n";
            cout << "(1): Re-enter info\n(2): Exit to login menu\nEnter Choice:";
            cin >> choice;
        } else if (aMapItr->second != encPswrd) {
            cout << "Email and password do not match.\n";
            cout << "(1): Re-enter info\n(2): Exit to login menu\nEnter Choice:";
            cin >> choice;
        } else success = true;
    }while (choice == 1);
    if (success) return true;
    else return false;
}
unsigned int User::studentLogin() {
    unsigned int ID;
    string name;
    cout << "Enter ID: ";
    cin >> ID;
    cout << "Enter Name: \n";
    getline(cin, name);
    uMapItr = uMap.find(ID);
    if (name == uMapItr->second) {
        cout << "Login Successful\n";
        return ID;
    } else return 0;
}