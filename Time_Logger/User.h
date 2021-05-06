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
    map<unsigned int, string> uMap; // A map holding the user id and name
    map<unsigned int, string>::iterator uMapItr; // Iterator for user map
    map<unsigned int, string> iMap; // A map holding the instructor id and name
    map<unsigned int, string>::iterator iMapItr; // Iterator for instructor map
    map<string, unsigned int> aMap; // A map holding the admin name and passcode
    map<string, unsigned int>::iterator aMapItr; // Iterator for admin map
    
public:
    User();
    User(const User& orig);
    virtual ~User();
    unsigned int PswrdCnvrt(const string&);
    void dispStudents();
    void dispInstructors();
    bool adminLogin();
    unsigned int studentLogin();
   
};

#endif /* USER_H */

