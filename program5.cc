//PROGRAM5-MAIN FILE
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CS3377.501
#include "program5.h"

//declare global map object
map <int, string> myMap;

//calls major functions in program
int main(int argc, char* argv[])
{
    //parse command line for user options
    parsecmdline(argc, argv); 	
    //parse config file for user configurations
    int parse_err = parseconfigfile();
    if(parse_err == 1)
    {
        return 0;
    }
    //tell the user that they are in verbose mode    
    if(myMap[VMODE] == "true")
    {
        cout << "Starting program in verbose mode..." << endl;
    }
   
    //create struct to look evaluate system files
    struct stat info;

    //check if the watch directory exists
    //if it doesnt exist tell the user and exit
    if(stat(myMap[W_DIR].c_str(), &info) != 0)
    {
        if(myMap[VMODE] == "true")
        {
            cout << "MAIN ERROR: Watch directory could not be found!" << endl;
        }
        return 1;
    }
    //if it exists tell the user
    else if(info.st_mode & S_IFDIR)
    {
        if(myMap[VMODE] == "true")
        {
            cout << "Watch directory found!" << endl        
                 << "Watch directory is " << myMap[W_DIR] << endl;
        }
    }
    //if it exists but isnt a directory tell the use rand exit
    else
    {
        if(myMap[VMODE] == "true")
        {
            cout << "MAIN ERROR: Path given is not a directory!" << endl;
        }
        return 1;
    }

    //if user chose to run in daemon mode start process control
    if(myMap[DMODE] == "true")
    {
		processControl();
        return 0;
    }
    
    //run in standard mode
    else
    {
        if(myMap[VMODE] == "true")
        {
            cout << "Starting program in regular mode..." << endl;
            cout << "Starting inotify..." << endl;
        }

        while(1)
        {
            inotifyStart();
        }
    } 
    return 0;
}
