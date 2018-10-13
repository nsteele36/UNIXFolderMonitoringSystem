//PROGRAM5-LOGGING FUNCTIONS FILE
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CS3377.501
#include "program5.h"

//creates the log file
void createLog()
{	
    ofstream log;
    log.open(myMap[LFILE].c_str());	
    
    if(!log.is_open())
    {
        cout << "ERROR OPENING LOG FILE" << endl;
    }
    if(myMap[VMODE] == "true")
    {
        log << "DAEMON CREATED: STARTING LOG" << endl;
    }
	log.close();
}

//adds a closing message and closes the log
void closeLog()
{
    ofstream log;
    log.open(myMap[LFILE].c_str(), ios::app);

    if(myMap[VMODE] == "true")
    {
        log << "DAEMON CLOSED: CLOSING LOG" << endl;
    }
    log.close();
}

//logs when a file or directory is created in the watch directory
void logCreation(struct inotify_event* e)
{
    //open log file
    ofstream log;
    log.open(myMap[LFILE].c_str(), ios::app);
    
    //if the event was a directory print the appropriate message
    if(e->mask & IN_ISDIR)
    {
        //if its in daemon mode log it to the file 
        if(myMap[DMODE] == "true")
        {       
            log << "Directory created named " << e->name << " in " << myMap[W_DIR] << endl;
        }
        //if its in console mode print it to screen
        else
        {
            cout << "Directory created named " << e->name << " in " << myMap[W_DIR] << endl;
        } 
     }
    //if its a file print the appropriate message
    else
    {
        if(myMap[DMODE] == "true")
        {
           log << "FILE created named " << e->name << " in " << myMap[W_DIR] << endl;
        }
        else
        {
           cout << "File created named " << e->name << " in " << myMap[W_DIR] << endl;
        }           
    }
    log.close();
}

//logs when a file or directory is modified in the watch directory
void logModified(struct inotify_event* e)
{
    //open log file
    ofstream log;
    log.open(myMap[LFILE].c_str(), ios::app);
    
    //if the even was a directory print the appropriate message
    if(e->mask & IN_ISDIR)
    {
        //if its in daemon mode log it to the file
        if(myMap[DMODE] == "true")
        {       
            log << "Directory modified named " << e->name << " in " << myMap[W_DIR] << endl;
        }
        //if its in console mode print it to the screen
        else
        {
            cout << "Directory modified named " << e->name << " in " << myMap[W_DIR] << endl;
        } 
    }

    //if its a file print the appropriate message
    else
    {
        if(myMap[DMODE] == "true")
        {
           log << "FILE modified named " << e->name << " in " << myMap[W_DIR] << endl;
        }
        else
        {
           cout << "File modified named " << e->name << " in " << myMap[W_DIR] << endl;
        }           
     }

    //create variables to store the result of the date linux command
    char buffer[20];
    string cmd1 = "date +\"%Y.%m.%d-%T\"";
    FILE *date =  popen(cmd1.c_str(), "r");

    //exit if the command cannot be run
    if(!date)
    {
        if(myMap[DMODE] == "true")
        {
            log << "INOTIFY ERROR: could not run the date command" << endl;
        }
        else
        {
            cout << "INOTIFY ERROR: could not run the date command" << endl;
        }   
        log.close();
        return;
    } 
    
    //read the result into the buffer
    fread(buffer, sizeof(char), sizeof(char) * sizeof(buffer), date);
    
    //find the buffer length and change the last character to the null terminator
    int bufferlen = sizeof(buffer) / sizeof(buffer[0]);
    buffer[bufferlen-1] = '\0';
    
    //form the strings for the file to copy and the copy path
    string filetocp = myMap[W_DIR] + "/" + e->name;
    string copypath = " " + myMap[W_DIR] + "/.versions/" + e->name + "." + buffer;
    string cmd = "cp " + filetocp + copypath;
    
    //run the copy command to back up file to .versions
    const int cp_err = system(cmd.c_str()); 

    //if the copy failed tell the user and exit
    if(cp_err == -1)
    {
        log << "INOTIFY ERROR: cp command did not work!" << endl;
        log.close();
        return;
    }
    
    //verbose messaging for the user
    if(myMap[VMODE] == "true")
    { 
        if(myMap[DMODE] == "true")
        {
            string header = "INOTIFY: ";
            string msg = header + e->name + " was copied to .versions under the name " + e->name + "." + buffer;
            log << msg << endl;
        }
        else
        {
            string header = "INOTIFY: ";
            string msg = header + e->name + " was copied to .versions under the name " + e->name + "." + buffer;
            cout << msg << endl;
        }   
    }   
    log.close();
}

//function to log the deleted file or directory 
void logDeleted(struct inotify_event* e)
{
    //open log file
    ofstream log;
    log.open(myMap[LFILE].c_str(), ios::app);
    
    //log or print a message to the user
    if(e->mask & IN_ISDIR)
    {
        if(myMap[DMODE] == "true")
        {       
            log << "Directory deleted named " << e->name << " in " << myMap[W_DIR] << endl;
        }
        else
        {
            cout << "Directory deleted named " << e->name << " in " << myMap[W_DIR] << endl;
        } 
     }
     else
     {
         if(myMap[DMODE] == "true")
         {
            log << "FILE deleted named " << e->name << " in " << myMap[W_DIR] << endl;
         }
         else
         {
            cout << "File deleted named " << e->name << " in " << myMap[W_DIR] << endl;
         }           
     }
    log.close();
}

//function to log password changes
void logPasswdChange()
{
    ofstream log;
    log.open(myMap[LFILE].c_str(), ios::app);	
    
    if(!log.is_open())
    {
        cout << "ERROR OPENING LOG FILE" << endl;
    }
    if(myMap[VMODE] == "true")
    {
        log << "PARSE CONFIG ERROR: password was changed! Exiting..." << endl;
    }
    log.close();
}
