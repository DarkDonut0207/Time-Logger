/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.h
 * Author: Drake
 *
 * Created on March 21, 2021, 10:24 PM
 */

#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>  
#include <map>
#include <fstream>
#include <iterator>
#include <set>
#include "User.h"
using namespace std;

struct Log {
    int logCount;
    map<unsigned int, unsigned int> intList;
};


struct StuStruc {
    int claCount;
    map<string, Log> logList;
};
struct ClaStruc {
    string instUser; // Instructor username
    int stuCount;
    set<unsigned int, greater<unsigned int>> stuSet;
};
class Logger : public User {
private:
    map<string, ClaStruc> ClassLst; // Class Data
    map<string, ClaStruc>::iterator ClassItr; // Class Data Iterator
    map<unsigned int, StuStruc> StDatLst;// Student Data
    map<unsigned int, StuStruc>::iterator StDatItr;// Student Data Iterator
public:
    Logger();
    //Logger(const Logger& orig);
    ~Logger();
    void calcTime(string, short, short);
    void runLog(unsigned int);
    void dispStudentLog(unsigned int);
    void dispClasses();
    void logPushToF();
    void eraseLog(unsigned int, string, int);
};

#endif /* LOGGER_H */

