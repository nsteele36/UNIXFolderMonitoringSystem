//PROGRAM5- PROCESS CONTROL FILE
//PROGRAMMED BY: NICHOLAS STEELE
//CS3377.501
#include "program5.h"

//main function for running the program in daemon mode
int processControl()
{
    string cmd = "mkdir ";
    string ver = "/.versions";
    string fullpath = myMap[W_DIR] + ver;
    string fullCMD = cmd + fullpath;
    struct stat info; 
    
    //check if the folder has the .versions file 
    //if it doesn't try to create the file
    if(stat(fullpath.c_str(), &info) != 0)
    {
        if(myMap[VMODE] == "true")
        {
            cout << "PROCESS CONTROL WARNING: .versions folder cannot be found. Attempting to create it..." << endl;
        }
        const int dir_error = system(fullCMD.c_str());
	    if(dir_error == -1)
        {
            cerr << "DAEMON ERROR: Cannot create .versions folder" << endl; 
            return 1;
        }
    }
    //if the folder is found tell the user
    else if(info.st_mode & S_IFDIR)
    {
        if(myMap[VMODE] == "true") 
        {
            cout << ".versions file found!" << endl;
        }
    }
    //if .versions exists but isnt a directory tell the user and exit
    else
    {
        if(myMap[VMODE] == "true")
        {
            cerr << "PROCESS CONTROL ERROR: .versions is not a directory!" << endl;
        }
        return 1;
    }

    if(myMap[VMODE] == "true")
    {
        cout << "Starting program in daemon mode..." << endl;
    }   
    
    //Fork the daemon process from the main program
    pid_t forkvalue;
	forkvalue = fork();
   
    //if there are errors forking tell the user
	if(forkvalue == -1)  /* Error... no child created */
	{
		cerr << "PROCESS CONTROL ERROR: There was an error in the fork.  No child was created.";
		return 1;
	}	
    //run the daemon functions
    else if(forkvalue == 0)   /* I am the child */
    {
        //create file containing the daemons pid number
		ofstream oFile ("cs3377dirmond.pid");
		oFile << getpid() << endl;
		oFile.close();
        
        //call functions to create logs and handle signals
        createLog();
        signalHandling();
        
        //start watching directory
        while(1)
        {   
            inotifyStart();
        }
    }
    return 0;
}

//delete pid file
void removePID()
{
    remove("cs3377dirmond.pid");
    return;
}
