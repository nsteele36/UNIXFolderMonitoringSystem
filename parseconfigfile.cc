//PROGRAM5-HEADER FILE
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CSS3377.501
#include "program5.h"
#include <rude/config.h>

//uses rudeconfig to parse a given configuration file
int parseconfigfile()
{
    //create rude config object
	rude::Config config;

    //load the file given by the user
	if(config.load(myMap[CONF].c_str()))
	{
        //create a parameters section
		config.setSection("Parameters", false);
		string sec;
		if(sec.c_str() == NULL)
			sec = "";
		//if the parameter section is not in the configuration file then report the error
		else if(config.getSectionNameAt(1) == NULL)
		{
			cout << "RUDE CONFIG ERROR: could not find Parameter section" << endl;
			return 1;
		}
		else
			sec = config.getSectionNameAt(1);

       	 //if the section exists read the information into the map 
	if( sec != "" && sec == "Parameters")
	{
            //check if the rules exist and save them to the map
            //Otherwise print an error message and exit
            if(config.exists("Verbose"))
                myMap[VMODE] = config.getStringValue("Verbose");	
            else
            {
                cout << "CONFIGURATION PARSE ERROR: could not find the Verbose rule" << endl;
                return 1;
            }   
            
            if(config.exists("WatchDir"))  
                myMap[W_DIR] = config.getStringValue("WatchDir");
           
            else
            {
                cout << "CONFIGURATION PARSE ERROR: could not find the WatchDir rule" << endl;
                return 1;
            }
            
            if(config.exists("Password"))
	    {
		//check if the password has been changed
	    	if(myMap[PWORD].empty())
		     myMap[PWORD] = config.getStringValue("Password");
		else
		{
		     string s = config.getStringValue("Password");
		     //if the passwords are different then print an error to the user and exit
		     if(s.compare(myMap[PWORD]))
		     {
		          if(myMap[DMODE] == "true")
		          {
		    	       logPasswdChange();
			       closeLog();
			       exit(1);
			  }
			  else
			     	cout << "CONFIGURATION PARSE ERROR: password changed! Exiting..." << endl;
			  return 1;
	             }
		}
            }
	    else
            {
                cout << "CONFIGURATION PARSE ERROR: could not find the Password rule" << endl;
                return 1;
            }
            if(config.exists("NumVersions"))
            {
                myMap[NUMV] = config.getStringValue("NumVersions");
            } 
            else
            {
                cout << "CONFIGURATION PARSE ERROR: could not find the NumVersions rule" << endl;
                return 1;
            }
	    if(config.exists("LogFile"))
                myMap[LFILE] = config.getStringValue("LogFile");     
            else
            {
                cout << "CONFIGURATION PARSE ERROR: could not foind the Logfile rule" << endl;
               return 1;
            }
	}
    }
    return 0;
}
