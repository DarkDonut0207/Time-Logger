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
    unsigned int ID;
    int claCount;
    int logCount;
    string classNme;
    unsigned int tmIn;
    unsigned int tmOut;
    string instUser;
    int stuCount;
    stuDat.open("StudentData.dat");
    claDat.open("ClassData.dat");
    while(!stuDat.eof()) {
        StuStruc tStuStr;
        map<string, Log> tLogList;
        stuDat >> ID;
        stuDat >> claCount;
        for (int i=0; i<claCount; i++) { // Read the logs
            map<unsigned int, unsigned int> intList; // Interior list for logs
            Log logVar;
            stuDat >> classNme;
            stuDat >> logCount;
            for (int j=0; j<logCount; j++) {
                stuDat >> tmIn;
                stuDat >> tmOut;
                intList.insert(pair<unsigned int, unsigned int>(tmIn, tmOut));
            }
            logVar.logCount = logCount;
            logVar.intList = intList;
            tLogList.insert(pair<string, Log>(classNme, logVar));
        }
        tStuStr.claCount = claCount;
        tStuStr.logList = tLogList;
        StDatLst.insert(pair<unsigned int, StuStruc>(ID, tStuStr));
    }
    while(!claDat.eof()) {
        ClaStruc tClaStr;
        set<unsigned int, greater<unsigned int>> stuSet;
        claDat >> classNme;
        claDat >> instUser;
        claDat >> stuCount;
        for (int i=0; i<stuCount; i++) { // Read the student ids
            claDat >> ID;
            stuSet.insert(ID);
        }
        tClaStr.instUser = instUser;
        tClaStr.stuCount = stuCount;
        tClaStr.stuSet = stuSet;
        ClassLst.insert(pair<string, ClaStruc>(classNme, tClaStr));
    }
    stuDat.close();
    claDat.close();
}

Logger::~Logger() {
}


void Logger::calcTime(string sID, short hrOut, short minOut) {
    // Need to write own function for this
}
void Logger::runLog(unsigned int ID) {
    int choice;
    int logCount;
    unsigned int rawElapse;
    unsigned int tIn;
    unsigned int tOut;
    string gClass;
    cout << "Input a class to record\n";
    cout << "(Must be class followed by course number ex: CIS-1A-11111\n : ";
    cin >> gClass;
    ClassItr = ClassLst.find(gClass);
    while ((ClassItr == ClassLst.end() || 
            ClassItr->second.stuSet.find(ID) == ClassItr->second.stuSet.end()) 
            && gClass!="0") {
        cout << "Class was not found, re-enter or enter 0 to cancel: ";
        cin >> gClass;
        ClassItr = ClassLst.find(gClass);
    }
    if (gClass!="0") {
        auto start = chrono::system_clock::now(); // Initialize start time
        time_t start_time = chrono::system_clock::to_time_t(start);
        do {
            cout << "(1) See current time elapsed in session\n";
            cout << "(2) See log time summary\n";
            cout << "(3) End session\n";
            cout << "Enter choice: ";
            cin >> choice;
            if (choice == 1) {
                auto current = chrono::system_clock::now();
                time_t cur_time = chrono::system_clock::to_time_t(current);
                rawElapse = cur_time-start_time;
                cout << "Session started at: " << ctime(&start_time);
                cout << "Elapsed: " << rawElapse/3600 << "h, ";
                cout << (rawElapse%3600)/60 << "m, " << rawElapse%60 << "s\n";
            } if (choice == 2) {
                this->dispStudentLog(ID);
            }
        } while (choice!=3);
        auto end = chrono::system_clock::now();
        time_t end_time = chrono::system_clock::to_time_t(end);
        rawElapse = end_time-start_time;
        cout << "Session started at: " << ctime(&start_time);
        cout << "Session ended at: " << ctime(&end_time);
        cout << "Elapsed: " << rawElapse/3600 << "h, ";
        cout << (rawElapse%3600)/60 << "m, " << rawElapse%60 << "s\n";
        tIn = (unsigned int)start_time;
        tOut = (unsigned int)end_time;
        StDatItr = StDatLst.find(ID);
        if (StDatItr != StDatLst.end()) {
            StuStruc tStruct;
            Log tLog;
            tStruct.claCount = StDatItr->second.claCount;
            map<string, Log> tLogList;
            tLogList = StDatItr->second.logList;
            auto logItr = StDatItr->second.logList.find(gClass);
            tLog.logCount = logItr->second.logCount + 1;
            map<unsigned int, unsigned int> nIntList;
            nIntList = logItr->second.intList;
            nIntList.insert(pair<unsigned int, unsigned int>(tIn, tOut));
            tLog.intList = nIntList;
            tLogList.erase(gClass);
            tLogList.insert(pair<string, Log>(gClass, tLog));
            tStruct.logList = tLogList;
            StDatLst.erase(ID);
            StDatLst.insert(pair<unsigned int, StuStruc>(ID, tStruct));
        } else cout << "Failed to push";
    }
}
void Logger::dispStudentLog(unsigned int ID) {
    map<string, Log>::iterator logItr;
    StDatItr = StDatLst.find(ID);
    logItr = StDatItr->second.logList.begin();
    if (StDatItr != StDatLst.end()) {
        if (this->findStudent(ID)) { // Skip if student was deleted
            map<string, Log>::iterator logItr;
            cout << "\nStudent ID: " << StDatItr->first; // ID
            cout << "\nClasses: "; // Class count
            for (logItr = StDatItr->second.logList.begin(); logItr != StDatItr->second.logList.end(); ++logItr) {
                cout << endl << logItr->first; // Class name
                map<unsigned int, unsigned int>::iterator intItr;
                for (intItr = logItr->second.intList.begin(); intItr != logItr->second.intList.end(); ++intItr) {
                    time_t timeIn = intItr->first;
                    time_t timeOut = intItr->second;
                    cout << "\nTime In : " << ctime(&timeIn);
                    cout << "Time Out: " << ctime(&timeOut);
                }
            }
        } else cout << "\nStudent not found\n";
    } else cout << "\nStudent not found\n";
    cout << endl;
}
void Logger::dispClasses() {
    unsigned int ID;
    char answ;
    string classNme;
    int inp;
    for (ClassItr = ClassLst.begin(); ClassItr != ClassLst.end(); ++ClassItr) {
        set<unsigned int, greater<unsigned int>>::iterator stuItr; // Iterator for student set
        cout << endl << "Class: " << ClassItr->first; // Class name
        cout << endl << "Instructor: " << ClassItr->second.instUser; // Instructor email
        cout << endl << "Student count: " << ClassItr->second.stuCount; // Number of students
        cout << endl << "Student ID" << " - Email";
        for (stuItr = ClassItr->second.stuSet.begin(); stuItr != ClassItr->second.stuSet.end(); stuItr++) {
            cout << "\n" << setw(10) << *stuItr << " - "; // Student ID
            cout << getStuName(*stuItr);
        }
    }
    cout << "\nEnter the ID of a student to view their logged time, or 0 to return: ";
    cin >> ID;
    if (ID!=0) {
        this->dispStudentLog(ID);
        cout << "Delete log? (y/n): ";
        cin >> answ;
        if (answ == 'y') {
            cout << "Which class's logs for this student will be modified: ";
            cin >> classNme;
            cout << "Input the log# to be removed: ";
            cin >> inp;
            this->eraseLog(ID, classNme, inp);
        }
    }
    
}
void Logger::logPushToF() {
    int count = 0;
    ofstream stuDat;
    ofstream claDat;
    stuDat.open ("StudentData.dat", ofstream::trunc);
    claDat.open ("ClassData.dat", ofstream::trunc);
    // Load in student data
    for (StDatItr = StDatLst.begin(); StDatItr != StDatLst.end(); ++StDatItr) {
        if (this->findStudent(StDatItr->first)) { // Skip if student was deleted
            if (count != 0) stuDat << endl;
            map<string, Log>::iterator logItr;
            stuDat << StDatItr->first; // ID
            stuDat << endl <<  StDatItr->second.claCount; // Class count
            for (logItr = StDatItr->second.logList.begin(); logItr != StDatItr->second.logList.end(); ++logItr) {
                stuDat << endl << logItr->first << " " << logItr->second.logCount; // Class name
                map<unsigned int, unsigned int>::iterator intItr;
                for (intItr = logItr->second.intList.begin(); intItr != logItr->second.intList.end(); ++intItr) {
                    stuDat << endl << intItr->first; // time in
                    stuDat << endl << intItr->second; // time out
                }
            }
            count++;
        }
    }
    // Load in class data
    count = 0;
    for (ClassItr = ClassLst.begin(); ClassItr != ClassLst.end(); ++ClassItr) {
        if (this->findInstructor(ClassItr->second.instUser)) { // Skip if the instructor was deleted
            set<unsigned int, greater<unsigned int>>::iterator stuItr; // Iterator for student set
            if (count != 0) claDat << endl;
            claDat << ClassItr->first; // Class name
            claDat << endl << ClassItr->second.instUser; // Instructor email
            claDat << " " << ClassItr->second.stuCount; // Number of students
            for (stuItr = ClassItr->second.stuSet.begin(); stuItr != ClassItr->second.stuSet.end(); stuItr++) {
                if (this->findStudent(*stuItr)) // Skip if the student was deleted
                    claDat << endl << *stuItr; // Student ID
            }
            count++;
        }
    }
    stuDat.close();
    claDat.close();
}
void Logger::eraseLog(unsigned int ID, string classNme, int logNum) {
    StDatItr = StDatLst.find(ID);
    if (StDatItr!=StDatLst.end()) {
        auto logItr = StDatItr->second.logList.find(classNme);
        if (logItr!=StDatItr->second.logList.end()) {
            if (logNum<1 || logNum > logItr->second.logCount) {
                cout << "\nLog is out of bounds.";
            } else {
                auto intItr = logItr->second.intList.begin();
                for (int i=0; i<logNum-1; i++) {
                    intItr++;
                }
                unsigned int logTime = intItr->first;
                logItr->second.intList.erase(logTime);
                logItr->second.logCount--;
            } 
        } else cout << "\nClass not found.";
    } else cout << "\nStudent not found.";
}