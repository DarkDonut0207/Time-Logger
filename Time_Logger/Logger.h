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
using namespace std;

struct Log {
    unsigned int timeIn;
    unsigned int timeOut;
};
struct StuStruc {
    unsigned int ID;
    string sName;
    int logCount;
    map<string, Log> logList;
};
struct ClaStruc {
    unsigned int instID; // Instructor ID
    int stuCount;
    vector<string> stuList;
};
class Logger {
private:
    struct info {
        string ID;
        short month;
        short day;
        short year;
        short hrIn;
        short minIn;
        short time; // Time in minutes
        //short hrOut;
        //short minOut;
    };
    map<string, Log> ClassLst;
    vector<int> claData; // Class Data
    vector<int> sLogData; // Student log data
public:
    Logger();
    //Logger(const Logger& orig);
    ~Logger();
    void pushList(string, short, short, short, short, short);
    void calcTime(string, short, short);
    void runLog(unsigned int);
    void dispClasses();
};

#endif /* LOGGER_H */

