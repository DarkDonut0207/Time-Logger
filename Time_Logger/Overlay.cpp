/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Overlay.cpp
 * Author: Drake
 * 
 * Created on March 21, 2021, 10:24 PM
 */

#include "Overlay.h"
#include "User.h"

Overlay::Overlay() {
    ID = 0;
    user = "\0";
}


//Overlay::Overlay(const Overlay& orig) {
//}

Overlay::~Overlay() {
}
void Overlay::mainMenu() {
    bool cont = true;
    bool isAdmin = false;
    int choice;
    cout << "***Time Logger Main Menu***\n";
    cout << "(1) Login as Student\n(2) Login as Instructor\n(3)" <<
            " Login as Admininstrator\nInput Choice: ";
    cin >> choice;
    while (choice > 3 || choice < 1) {
        cout << "Invalid choice, re-input: ";
        cin >> choice;
    }
    if (choice == 1) {
        do { // Launch student login
            if (ID==0) {
                cout << "\n***Student Login Menu***\n" << endl;
                choice = this->loginMenu();
                if (choice == 1) {
                    ID = this->studentLogin();
                } if (choice == 2) {
                    cont = false;
                }
            } else if (ID!=0) {
                this->runLog(ID);
                cout << "Logging out\n";
                ID = 0;
                cont = false;
            }
        } while (cont);
    } else if (choice == 2) {
        do { // Launch instructor login
            if (user=="\0") {
                cout << "\n***Instructor Login Menu***\n" << endl;
                choice = this->loginMenu();
                if (choice == 1) {
                    user = this->instructLogin();
                } if (choice == 2) {
                    cont = false;
                }
            } else if (user!="\0") {
                
            }
        } while (cont);
    } else if (choice == 3) { // Launch admin login
        do {
            if (!isAdmin) {
                cout << "\n***Admin Login Menu***\n" << endl;
                choice = this->loginMenu();
                if (choice == 1) {
                    isAdmin = this->adminLogin();
                } if (choice == 2) {
                    cont = false;
                }   
            } else {
                choice = this->adminMenu();
                if (choice == 1) {
                    // View/Edit Students
                    this->modStuMenu();
                } else if (choice == 2) {
                    // View/Edit Instructors
                    this->modInstMenu();
                } else if (choice == 3) {
                    // View/Edit Classes
                    this->dispClasses();
                } else if (choice == 4) {
                   isAdmin = false; // Logout
                } else if (choice == 5) {
                    cont = false; // Exit program
                }
            }
        } while (cont);
        
    }
    this->logPushToF();
    this->userPushToF();
}

int Overlay::loginMenu() {
    int choice = 2;
    cout << "(1): Login\n";
    cout << "(2): Exit program\n";
    cout << "Enter choice: ";
    cin >> choice;
    while (choice <1 || choice > 2) {
    cout << "This is an invalid choice, re-enter choice: ";
    cin >> choice;
    }
    return choice;
}
int Overlay::adminMenu() {
    int choice = 5;
    cout << "\n***Administrator Menu***\n";
    cout << "(1): View/Edit/Add Students\n";
    cout << "(2): View/Edit/Add Instructors\n";
    cout << "(3): View/Edit/Add Classes\n";
    cout << "(4): Logout\n";
    cout << "(5): Exit program\n";
    cout << "Enter choice: ";
    cin >> choice;
    while (choice < 1 || choice > 5) {
        cout << "This is an invalid choice, re-enter choice: ";
        cin >> choice;
    }
    return choice;
}
void Overlay::modStuMenu() {
    int choice = 3;
    do {
        this->dispStudents();
        cout << "\n***Modify Student List Menu***\n";
        cout << "(1): Edit a student\n";
        cout << "(2): Delete a student\n";
        cout << "(3): Add a student\n";
        cout << "(4): Return to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "This is an invalid choice, re-enter choice: ";
            cin >> choice;
        }
        if (choice != 4) this->modStudents(choice);
    } while (choice != 4);
}
void Overlay::modInstMenu() {
    int choice = 3;
    do {
        this->dispInstructors();
        cout << "\n***Modify Instructor List Menu***\n";
        cout << "(1): Edit an instructor\n";
        cout << "(2): Delete an instructor\n";
        cout << "(3): Add an instructor\n";
        cout << "(4): Return to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "This is an invalid choice, re-enter choice: ";
            cin >> choice;
        }
        if (choice != 4) this->modInstructors(choice);
    } while (choice != 4);
}