/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Overlay.h
 * Author: Drake
 *
 * Created on March 21, 2021, 10:24 PM
 */

#ifndef OVERLAY_H
#define OVERLAY_H
#include "Logger.h"
#include "User.h"
#include <iostream>
#include <string>
using namespace std;
class Overlay : public User, public Logger {
private:
    string gClass;
    short signIn;
    unsigned int ID;
    short month;
    short day;
    short year;
    short hour;
    short min;
public:
    Overlay();
    //Overlay(const Overlay& orig);
    ~Overlay();
    void login();
    void menu();
    int adminLoginMenu();
    int adminMenu();
    unsigned int userLoginMenu();
};

#endif /* OVERLAY_H */

