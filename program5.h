//PROGRAM5-HEADER FILE
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CS3377.501

#ifndef PROGRAM_5_H
#define PROGRAM_5_H

//libraries 
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <signal.h>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <csignal>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>

using namespace std;

//parsing prototypes
void parsecmdline(int, char*[]);
int parseconfigfile();

//inotify prototype
void inotifyStart();

//process control prototypes
int processControl();
void killDaemon(int);
void reconfigure(int);
void signalHandling();
void removePID();

//logging prototypes
void createLog();
void logCreation(struct inotify_event* e);
void logModified(struct inotify_event* e);
void logDeleted(struct inotify_event* e);
void logPasswdChange();
void closeLog();

//map to hold important values between functions
extern map<int, string> myMap;

//global enumeratio values
enum {CONF, DMODE, VMODE, LFILE, W_DIR, PWORD, NUMV};

#endif // PROGRAM_5_H
