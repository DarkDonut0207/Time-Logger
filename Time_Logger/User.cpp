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
    string user;
    unsigned int encPswrd;
    userF.open("StudentIdMap.dat");
    instrF.open("InstructorIdMap.dat");
    adminF.open("adminData.dat");
    while(!userF.eof()) {
        userF >> id;
        userF >> user;
        sMap.insert(pair<unsigned int,string>(id, (user)));
    }
    while(!instrF.eof()) {
        instrF >> user;
        instrF >> encPswrd;
        iMap.insert(pair<string,unsigned int>(user, (encPswrd)));
    }
    while(!adminF.eof()) {
        adminF >> user;
        adminF >> encPswrd;
        aMap.insert(pair<string,unsigned int>(user, (encPswrd)));
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
    cout << left << setw(10) << "ID" << " - Name\n";
    for(sMapItr = sMap.begin(); sMapItr != sMap.end(); ++sMapItr) {
        cout << left << setw(10) << sMapItr->first << " - " << sMapItr->second;
        cout << endl;
    }
}
void User::dispInstructors() {
    cout << "Instructor List:\n";
    for(iMapItr = iMap.begin(); iMapItr != iMap.end(); ++iMapItr) {
        cout << left << setw(10) << iMapItr->first << endl;
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
string User::instructLogin() {
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
    if (success) return userName;
    else return "\0";
}
unsigned int User::studentLogin() {
    unsigned int ID;
    string name;
    bool success = false;
    int choice = 2;
    do {
        choice = 2;
        cout << "Enter Student ID: ";
        cin >> ID;
        cout << "Enter Email: \n";
        cin.ignore();
        getline(cin, name);
        sMapItr = sMap.find(ID);
        if (sMapItr==sMap.end()) {
            cout << "ID and Name do not match.\n";
            cout << "(1): Re-enter info\n(2): Exit to login menu\nEnter Choice:";
            cin >> choice;
        } else if (sMapItr->second != name) {
            cout << "ID and Name do not match.\n";
            cout << "(1): Re-enter info\n(2): Exit to login menu\nEnter Choice:";
            cin >> choice;
        } else {
            cout << "Login Successful\n";
            success = true;
        }
    }while (choice == 1);
    if (success) return ID;
    else return 0;
}
string User::getStuName(unsigned int ID) {
    return sMap[ID]; // Returns the name associated to the given ID
}
void User::modStudents(int choice) {
    unsigned int ID;
    string email;
    int input = 3;
    if (choice == 1) {
        cout << "Input a student's ID to edit them: ";
        cin >> ID;
        sMapItr = sMap.find(ID);
        if (sMapItr != sMap.end()) {
            cout << "Editing student: " << sMapItr->first;
            cout << "\n(1) Change ID\n(2) Change Email\n(3) Cancel\n";
            cout << "Enter Choice: ";
            cin >> input;
            while (input > 3 || input < 1) {
                cout << "Invalid Choice, Re-enter: ";
                cin >> input;
            }
            if (input == 1) {
                cout << "Enter new ID: ";
                cin >> ID;
                if (sMap.find(ID) != sMap.end()) {
                    cout << "ID is in use.\n";
                } else {
                    email = sMapItr->second;
                    sMap.erase(sMapItr->first);
                    sMap.insert(pair<unsigned int, string>(ID, email));
                    cout << "ID replaced.\n";
                }
            } if (input == 2) {
                cout << "Enter new email: ";
                cin >> email;
                ID = sMapItr->first;
                sMap.erase(sMapItr->first);
                sMap.insert(pair<unsigned int, string>(ID, email));
                cout << "Email replaced.\n";
            }
        } else cout << "This is an invalid student.\n";
    } else if (choice == 2) {
        cout << "Input a student's ID to delete them: ";
        cin >> ID;
        sMapItr = sMap.find(ID);
        if (sMapItr != sMap.end()) {
            cout << "Deleting student: " << sMapItr->first;
            cout << "\n(1) Confirm\n(2) Cancel\n";
            cout << "Enter Choice: ";
            cin >> input;
            while (input > 2 || input < 1) {
                cout << "Invalid Choice, Re-enter: ";
                cin >> input;
            }
            if (input == 1) {
                sMap.erase(sMapItr->first);
                cout << "Instructor deleted.\n";
            } 
        } else cout << "This is an invalid student.\n";
    } else if (choice == 3) {
        cout << "Input a student's ID to add them: ";
        cin >> ID;
        sMapItr = sMap.find(ID);
        if (sMapItr == sMap.end()) {
            cout << "Enter an email: ";
            cin >> email;
            sMap.insert(pair<unsigned int, string>(ID, email));
            cout << "Student added: " << ID << " " << email << endl;
        } else cout << "This ID is in use.\n";
    }
}
void User::modInstructors(int choice) {
    string email;
    string pswrd;
    unsigned int encPswrd;
    int input = 3;
    if (choice == 1) {
        cout << "Input an instructor's email to edit them: ";
        cin >> email;
        iMapItr = iMap.find(email);
        if (iMapItr != iMap.end()) {
            cout << "Editing instructor: " << iMapItr->first;
            cout << "\n(1) Change Email\n(2) Change Password\n(3) Cancel\n";
            cout << "Enter Choice: ";
            cin >> input;
            while (input > 3 || input < 1) {
                cout << "Invalid Choice, Re-enter: ";
                cin >> input;
            }
            if (input == 1) {
                cout << "Enter new email: ";
                cin >> email;
                if (iMap.find(email) != iMap.end()) {
                    cout << "Email is in use.\n";
                } else {
                    encPswrd = iMapItr->second;
                    iMap.erase(iMapItr->first);
                    iMap.insert(pair<string, unsigned int>(email, encPswrd));
                    cout << "Email replaced.\n";
                }
            } if (input == 2) {
                cout << "Enter new password: ";
                cin >> pswrd;
                encPswrd = this->PswrdCnvrt(pswrd);
                pswrd = "\0";
                email = iMapItr->first;
                iMap.erase(iMapItr->first);
                iMap.insert(pair<string, unsigned int>(email, encPswrd));
                cout << "Password replaced.\n";
            }
        } else cout << "This is an invalid instructor.\n";
    } else if (choice == 2) {
        cout << "Input an instructor's email to delete them: ";
        cin >> email;
        iMapItr = iMap.find(email);
        if (iMapItr != iMap.end()) {
            cout << "Deleting instructor: " << iMapItr->first;
            cout << "\n(1) Confirm\n(2) Cancel\n";
            cout << "Enter Choice: ";
            cin >> input;
            while (input > 2 || input < 1) {
                cout << "Invalid Choice, Re-enter: ";
                cin >> input;
            }
            if (input == 1) {
                iMap.erase(iMapItr->first);
                cout << "Instructor deleted.\n";
            } 
        } else cout << "This is an invalid instructor.\n";
    } else if (choice == 3) {
        cout << "Input an instructor's email to add them: ";
        cin >> email;
        iMapItr = iMap.find(email);
        if (iMapItr == iMap.end()) {
            cout << "Enter a password: ";
            cin >> pswrd;
            encPswrd = this->PswrdCnvrt(pswrd);
            pswrd = "\0";
            iMap.insert(pair<string, unsigned int>(email, encPswrd));
            cout << "Instructor added: " << email << endl;
        } else cout << "This email is in use.\n";
    }
}
bool User::findStudent(unsigned int ID) {
    sMapItr = sMap.find(ID);
    if (sMapItr != sMap.end()) return true;
    else return false;
}
bool User::findInstructor(string email) {
    iMapItr = iMap.find(email);
    if (iMapItr != iMap.end()) return true;
    else return false;
}
void User::userPushToF() {
    ofstream userF;
    ofstream instrF;
    int count = 0;
    userF.open("StudentIdMap.dat");
    instrF.open("InstructorIdMap.dat");
    for(sMapItr = sMap.begin(); sMapItr != sMap.end(); ++sMapItr) {
        if(count!=0) userF << endl;
        userF << sMapItr->first << " " << sMapItr->second;
        count++;
    }
    count = 0;
    for(iMapItr = iMap.begin(); iMapItr != iMap.end(); ++iMapItr) {
        if(count!=0) instrF << endl;
        instrF << iMapItr->first << " " << iMapItr->second << endl;
        count++;
    }
    userF.close();
    instrF.close();
}