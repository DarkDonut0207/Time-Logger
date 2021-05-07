/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: Drake
 *
 * Created on May 5, 2021, 3:58 PM
 */

#ifndef USER_H
#define USER_H
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
class User {
private:
    map<unsigned int, string> sMap; // A map holding the user id and name
    map<unsigned int, string>::iterator sMapItr; // Iterator for user map
    map<string, unsigned int> iMap; // A map holding the instructor name and passcode
    map<string, unsigned int>::iterator iMapItr; // Iterator for instructor map
    map<string, unsigned int> aMap; // A map holding the admin name and passcode
    map<string, unsigned int>::iterator aMapItr; // Iterator for admin map
    
public:
    User();
    User(const User& orig);
    virtual ~User();
    unsigned int PswrdCnvrt(const string&);
    void dispStudents();
    void dispInstructors();
    void modStudents(int);
    void modInstructors(int);
    bool findStudent(unsigned int);
    bool findInstructor(string);
    bool adminLogin();
    unsigned int studentLogin();
    string instructLogin();
    string getStuName(unsigned int);
    void userPushToF();
};

#endif /* USER_H */

