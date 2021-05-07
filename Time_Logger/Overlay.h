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
class Overlay : public Logger {
private:
    unsigned int ID;
    string user;
public:
    Overlay();
    //Overlay(const Overlay& orig);
    ~Overlay();
    void mainMenu();
    int loginMenu();
    int adminMenu();
    void modStuMenu();
    void modInstMenu();
};

#endif /* OVERLAY_H */

