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
}


//Overlay::Overlay(const Overlay& orig) {
//}

Overlay::~Overlay() {
}
void Overlay::login() {
    bool cont = true;
    bool isAdmin = false;
    int choice;
    cout << "(1) Login as Student\n(2) Login as Instructor\n(3)" <<
            " Login as Admininstrator\nInput Choice: ";
    cin >> choice;
    while (choice > 3 || choice < 1) {
        cout << "Invalid choice, re-input: ";
        cin >> choice;
    }
    if (choice == 1) {
        do { // Launch user login
            ID = this->userLoginMenu();
            if (ID!=0) {
                this->runLog(ID);
            } else cont = false;
        } while (cont);

    } else if (choice == 2) {
        // Launch instructor login
    } else if (choice == 3) { // Launch admin login
        do {
            if (!isAdmin) {
                choice = this->adminLoginMenu();
                if (choice == 1) {
                    isAdmin = this->adminLogin();
                } if (choice == 2) {
                    cont = false;
                }   
            } else {
                choice = this->adminMenu();
                if (choice == 1) {
                    // View/Edit Students
                } else if (choice == 2) {
                    // View/Edit Instructors
                } else if (choice == 3) {
                    // View/Edit Classes
                } else if (choice == 4) {
                   isAdmin = false; // Logout
                } else if (choice == 5) {
                    cont = false; // Exit program
                }
            }
        } while (cont);
        
    }
}
/*
void Overlay::menu() {
    // Prompt on whether to sign in or sign out
    cout << "Sign In (1) or Out (2)?";
    cin >> signIn;
    while (signIn>2||signIn<1)
        cin >> signIn;
    // Prompt for id
    cout << "Please enter your student ID: ";
    cin >> ID;
    // Prompt for date
    cout << "Log in, input today's month, day, year separated by spaces (3 21 2021):\n";
    cin >> month >> day >> year;
    // Prompt for time
    cout << "Input time hour and minutes separated by space (for PM add 12 to hour):\n";
    cin >> hour >> min;   
    // Add onto logger list
    //log.pushList(ID, month, day, year, hour, min);
    //log.calcTime("288", 12, 8);
}  
  */

int Overlay::adminLoginMenu() {
    int choice;
    cout << "\n***Admin Login Menu***\n" << endl;
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
    int choice;
    cout << "\n***Administrator Menu***\n";
    cout << "(1): View/Edit Students\n";
    cout << "(2): View/Edit Instructors\n";
    cout << "(3): View/Edit Classes\n";
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
unsigned int Overlay::userLoginMenu() {
    unsigned int ID = this->studentLogin();
    return ID;
}