/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.cpp
 * Author: Drake
 * 
 * Created on March 21, 2021, 10:24 PM
 */

#include "Logger.h"

Logger::Logger() {
    ifstream stuDat;
    ifstream claDat;
    stuDat.open("StudentData.dat");
    claDat.open("ClassData.dat");
    
}

//Logger::Logger(const Logger& orig) {
//}

Logger::~Logger() {
}

void Logger::pushList(string ID, short month, short day,
                      short year, short hour, short min) {
    info Input;
    Input.ID = ID;
    Input.month = month;
    Input.day = day;
    Input.year = year;
    Input.hrIn = hour;
    Input.minIn = min;
    Input.time = 0;
    //list.push_back(Input);
}

void Logger::calcTime(string sID, short hrOut, short minOut) {
    // Need to write own function for this
}
void Logger::runLog(unsigned int ID) {
    int choice;
    unsigned int rawElapse;
    string gClass;
    cout << "Input a class to record: ";
    cin >> gClass;
    auto start = chrono::system_clock::now(); // Initialize start time
    time_t start_time = chrono::system_clock::to_time_t(start);
    do {
        cout << "(1) See current time elapsed in session\n";
        cout << "(2) End session\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            auto current = chrono::system_clock::now();
            time_t cur_time = chrono::system_clock::to_time_t(current);
            rawElapse = cur_time-start_time;
            cout << "Session started at: " << ctime(&start_time);
            cout << "Elapsed: " << rawElapse/3600 << "h, ";
            cout << (rawElapse%3600)/60 << "m, " << rawElapse%60 << "s\n";
        }
    } while (choice!=2);
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    rawElapse = end_time-start_time;
    cout << "Session started at: " << ctime(&start_time);
    cout << "Session ended at: " << ctime(&end_time);
    cout << "Elapsed: " << rawElapse/3600 << "h, ";
    cout << (rawElapse%3600)/60 << "m, " << rawElapse%60 << "s\n";
}
void dispClasses() {
    
}